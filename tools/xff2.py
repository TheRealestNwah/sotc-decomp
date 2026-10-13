"""Read, write and convert Team Ico's `xff2` relocatable modules.

The game code lives in KERNEL.XFF, MANAGER.XFF and GAMECORE.XFF. Each is a
lightly repackaged ELF relocatable object (see docs/xff2.md):

    python tools/xff2.py info iso/GAMECORE.XFF
    python tools/xff2.py to-elf iso/GAMECORE.XFF build/xff/GAMECORE.o
    python tools/xff2.py from-elf build/xff/GAMECORE.o build/xff/GAMECORE.XFF

Converting XFF -> ELF -> XFF reproduces the original file byte for byte.
"""

from __future__ import annotations

import argparse
import struct
import sys
from dataclasses import dataclass, field
from pathlib import Path

MAGIC = b"xff2"
HEADER_SIZE = 0x70
SHDR_SIZE = 0x20
RELTAB_SIZE = 0x1C
SYM_SIZE = 16
REL_SIZE = 8
POINTER_BASE = 0x40010000  # header/section "pointers" are file offset + this

SHT_PROGBITS = 1
SHT_SYMTAB = 2
SHT_STRTAB = 3
SHT_RELA = 4
SHT_NOBITS = 8
SHT_REL = 9
SHT_MIPS_REGINFO = 0x70000006
SHT_DVP_OVERLAY_TABLE = 0x7FFFF420
SHT_DVP_OVERLAY = 0x7FFFF421

# Sections whose contents are stored in the XFF's section area.
STORED_TYPES = {SHT_PROGBITS, SHT_SYMTAB, SHT_DVP_OVERLAY_TABLE}

# Extra ELF section holding the second word of each import relocation, which
# isn't derivable from anything else.
RELINFO_SECTION = ".xff.relinfo"


@dataclass
class Section:
    name_offset: int  # into shstrtab
    type: int
    size: int
    align: int
    data: bytes | None = None  # None when the XFF doesn't store the contents


@dataclass
class RelTable:
    """Relocations for one section, split into imports (against undefined
    symbols) and locals. Each entry is (r_offset, r_info, saved_word, extra)."""

    target: int
    is_import: bool
    entries: list[tuple[int, int, int, int]] = field(default_factory=list)


@dataclass
class Module:
    sections: list[Section]
    shstrtab: bytes
    strtab: bytes
    symbols: bytes  # raw Elf32_Sym array
    reltables: list[RelTable]
    imports: list[int]  # symbol indices of undefined symbols
    entry: int  # offset of the entry function in .text
    num_locals: int  # local symbols, excluding the null symbol

    @property
    def num_symbols(self) -> int:
        return len(self.symbols) // SYM_SIZE

    def symbol(self, index: int) -> tuple[int, int, int, int, int, int]:
        return struct.unpack_from("<IIIBBH", self.symbols, index * SYM_SIZE)

    def section_name(self, index: int) -> str:
        return cstring(self.shstrtab, self.sections[index].name_offset)

    def symbol_name(self, index: int) -> str:
        return cstring(self.strtab, self.symbol(index)[0])

    def index_of(self, name: str) -> int:
        for i in range(len(self.sections)):
            if self.section_name(i) == name:
                return i
        raise KeyError(name)


def cstring(table: bytes, offset: int) -> str:
    end = table.index(b"\0", offset)
    return table[offset:end].decode("latin-1")


def align_up(value: int, alignment: int) -> int:
    return (value + alignment - 1) // alignment * alignment


# --- XFF reading ---------------------------------------------------------------


def parse(data: bytes) -> Module:
    if data[:4] != MAGIC:
        raise ValueError("not an xff2 file")
    h = struct.unpack_from("<28I", data, 0)
    if h[5] != len(data):
        raise ValueError(f"header says {h[5]:#x} bytes, file is {len(data):#x}")

    num_imports, num_symbols, num_reltables, num_sections = h[7], h[9], h[14], h[16]
    (imports_off, symtab_off, strtab_off, shdrs_off, _symaddr_off, reltabs_off, names_off,
     shstrtab_off) = h[20:28]  # fmt: skip

    name_offsets = struct.unpack_from(f"<{num_sections}I", data, names_off)
    sections = []
    for i in range(num_sections):
        _, _, size, align, sh_type, _, _, offset = struct.unpack_from(
            "<8I", data, shdrs_off + SHDR_SIZE * i
        )
        contents = bytes(data[offset : offset + size]) if offset else None
        sections.append(Section(name_offsets[i], sh_type, size, align, contents))

    module = Module(
        sections=sections,
        shstrtab=b"",
        strtab=b"",
        symbols=bytes(data[symtab_off : symtab_off + num_symbols * SYM_SIZE]),
        reltables=[],
        imports=list(struct.unpack_from(f"<{num_imports}I", data, imports_off)),
        entry=h[19],
        num_locals=h[3],
    )
    shstrtab_size = sections[_find_by_name(data, shstrtab_off, name_offsets, ".shstrtab")].size
    module.shstrtab = bytes(data[shstrtab_off : shstrtab_off + shstrtab_size])
    strtab_size = sections[module.index_of(".strtab")].size
    module.strtab = bytes(data[strtab_off : strtab_off + strtab_size])

    undefined = set(module.imports)
    for t in range(num_reltables):
        _, count, target, _, _, off_a, off_b = struct.unpack_from(
            "<7I", data, reltabs_off + RELTAB_SIZE * t
        )
        table = RelTable(target, is_import=t < num_reltables // 2)
        for i in range(count):
            r_offset, r_info = struct.unpack_from("<II", data, off_a + REL_SIZE * i)
            saved, extra = struct.unpack_from("<II", data, off_b + REL_SIZE * i)
            if (r_info >> 8 in undefined) != table.is_import:
                raise ValueError(f"relocation table {t} mixes imports and locals")
            table.entries.append((r_offset, r_info, saved, extra))
        module.reltables.append(table)
    return module


def _find_by_name(data: bytes, table_off: int, name_offsets: tuple[int, ...], name: str) -> int:
    for i, off in enumerate(name_offsets):
        if cstring(data[table_off:], off) == name:
            return i
    raise KeyError(name)


# --- XFF writing ---------------------------------------------------------------


def write(module: Module) -> bytes:
    num_sections = len(module.sections)
    num_symbols = module.num_symbols
    out = bytearray(HEADER_SIZE)

    def place(blob: bytes, alignment: int = 1) -> int:
        out.extend(bytes(align_up(len(out), alignment) - len(out)))
        offset = len(out)
        out.extend(blob)
        return offset

    names_off = place(b"".join(struct.pack("<I", s.name_offset) for s in module.sections))
    shdrs_off = place(bytes(SHDR_SIZE * num_sections))
    symaddr_off = place(
        b"".join(struct.pack("<I", module.symbol(i)[1]) for i in range(num_symbols))
    )
    reltabs_off = place(bytes(RELTAB_SIZE * len(module.reltables)))
    imports_off = place(b"".join(struct.pack("<I", i) for i in module.imports))
    shstrtab_off = place(module.shstrtab)

    section_offsets = [0] * num_sections
    symtab_index = module.index_of(".symtab")
    for i, section in enumerate(module.sections):
        if section.data is None:
            continue
        section_offsets[i] = place(section.data, max(section.align, 4))
        if i == symtab_index:
            strtab_off = place(module.strtab)

    # Relocation arrays: imports store B then A, locals store A then B.
    out.extend(bytes(align_up(len(out), 4) - len(out)))
    positions: list[tuple[int, int]] = []
    imports = [t for t in module.reltables if t.is_import]
    locals_ = [t for t in module.reltables if not t.is_import]
    b_cursor = len(out)
    for table in imports:
        out.extend(b"".join(struct.pack("<II", e[2], e[3]) for e in table.entries))
    a_cursor = len(out)
    for table in imports:
        positions.append((a_cursor, b_cursor))
        out.extend(b"".join(struct.pack("<II", e[0], e[1]) for e in table.entries))
        a_cursor = len(out)
        b_cursor += REL_SIZE * len(table.entries)
    b_cursor = len(out) + sum(REL_SIZE * len(t.entries) for t in locals_)
    for table in locals_:
        positions.append((len(out), b_cursor))
        out.extend(b"".join(struct.pack("<II", e[0], e[1]) for e in table.entries))
        b_cursor += REL_SIZE * len(table.entries)
    for table in locals_:
        out.extend(b"".join(struct.pack("<II", e[2], e[3]) for e in table.entries))

    for i, section in enumerate(module.sections):
        offset = section_offsets[i]
        struct.pack_into(
            "<8I", out, shdrs_off + SHDR_SIZE * i,
            0, _ptr(offset) if offset else 0, section.size, section.align, section.type,
            1 if section.type == SHT_NOBITS else 0, 0, offset,
        )  # fmt: skip
    for t, (table, (off_a, off_b)) in enumerate(zip(module.reltables, positions, strict=True)):
        struct.pack_into(
            "<7I", out, reltabs_off + RELTAB_SIZE * t,
            SHT_REL, len(table.entries), table.target, _ptr(off_a), _ptr(off_b), off_a, off_b,
        )  # fmt: skip

    offsets =(imports_off, section_offsets[symtab_index], strtab_off, shdrs_off, symaddr_off,
               reltabs_off, names_off, shstrtab_off)  # fmt: skip
    header = [0] * 28
    header[0] = struct.unpack("<I", MAGIC)[0]
    header[3] = module.num_locals
    header[5] = len(out)
    header[7] = len(module.imports)
    header[9] = num_symbols
    header[14] = len(module.reltables)
    header[16] = num_sections
    header[19] = module.entry
    pointer_slots = (8, 10, 11, 12, 13, 15, 17, 18)
    for slot, offset in zip(pointer_slots, offsets, strict=True):
        header[slot] = _ptr(offset)
    header[20:28] = offsets
    struct.pack_into("<28I", out, 0, *header)
    return bytes(out)


def _ptr(offset: int) -> int:
    return POINTER_BASE + offset


# --- ELF conversion ------------------------------------------------------------

ELF_HEADER_SIZE = 52
ELF_SHDR_SIZE = 40
EF_MIPS_EE_EABI64 = 0x20924001  # same e_flags as the loader ELF
SHF_WRITE, SHF_ALLOC, SHF_EXECINSTR = 1, 2, 4


def _elf_flags(name: str, sh_type: int) -> int:
    if sh_type == SHT_NOBITS:
        return SHF_WRITE | SHF_ALLOC
    if name in (".text", ".vutext"):
        return SHF_ALLOC | SHF_EXECINSTR
    if name.startswith((".data", ".vudata", ".sdata")):
        return SHF_WRITE | SHF_ALLOC
    if name.startswith((".rodata", ".lit")):
        return SHF_ALLOC
    if sh_type == SHT_MIPS_REGINFO:
        return SHF_ALLOC
    return 0


def to_elf(module: Module) -> bytes:
    """Build an ELF32 ET_REL object. Sections keep their XFF indices, so symbol
    section indices stay valid. Contents the XFF doesn't store are zero-filled."""
    num_sections = len(module.sections)
    symtab_index = module.index_of(".symtab")
    strtab_index = module.index_of(".strtab")
    shstrtab_index = module.index_of(".shstrtab")
    rel_by_target: dict[int, list[RelTable]] = {}
    for table in module.reltables:
        rel_by_target.setdefault(table.target, []).append(table)
    rel_sections = {
        module.index_of(".rel" + module.section_name(target)): target for target in rel_by_target
    }

    relinfo = b"".join(
        struct.pack("<I", e[3]) for t in module.reltables if t.is_import for e in t.entries
    )
    shstrtab = module.shstrtab + RELINFO_SECTION.encode() + b"\0"
    relinfo_name = len(module.shstrtab)

    contents: list[bytes] = []
    for i, section in enumerate(module.sections):
        if i == shstrtab_index:
            contents.append(shstrtab)
        elif i == strtab_index:
            contents.append(module.strtab)
        elif i == symtab_index:
            contents.append(module.symbols)
        elif i in rel_sections:
            entries = [e for t in rel_by_target[rel_sections[i]] for e in t.entries]
            contents.append(b"".join(struct.pack("<II", e[0], e[1]) for e in entries))
        elif section.type == SHT_NOBITS:
            contents.append(b"")
        elif section.data is not None:
            contents.append(section.data)
        else:
            contents.append(bytes(section.size))
    contents.append(relinfo)

    out = bytearray(ELF_HEADER_SIZE)
    offsets = []
    for i, blob in enumerate(contents):
        alignment = module.sections[i].align if i < num_sections else 4
        out.extend(bytes(align_up(len(out), max(alignment, 1)) - len(out)))
        offsets.append(len(out))
        out.extend(blob)
    out.extend(bytes(align_up(len(out), 4) - len(out)))
    shoff = len(out)

    out.extend(bytes(ELF_SHDR_SIZE))  # SHN_UNDEF is section 0 in both formats
    for i, section in enumerate(module.sections):
        if i == 0:
            continue
        name = module.section_name(i)
        link = info = entsize = 0
        size = len(contents[i]) if section.type != SHT_NOBITS else section.size
        if i in rel_sections:
            link, info, entsize = symtab_index, rel_sections[i], REL_SIZE
        elif i == symtab_index:
            link, info, entsize = strtab_index, module.num_locals + 1, SYM_SIZE
        elif section.type == SHT_RELA:
            link, info, entsize = symtab_index, module.index_of(name[len(".rela") :]), 12
        out.extend(
            struct.pack(
                "<10I",
                section.name_offset,
                section.type,
                _elf_flags(name, section.type),
                0,
                offsets[i],
                size,
                link,
                info,
                section.align,
                entsize,
            )  # fmt: skip
        )
    out.extend(
        struct.pack(
            "<10I", relinfo_name, SHT_PROGBITS, 0, 0, offsets[-1], len(relinfo), 0, 0, 4, 4
        )  # fmt: skip
    )

    ident = b"\x7fELF\x01\x01\x01" + bytes(9)
    header = ident + struct.pack(
        "<HHIIIIIHHHHHH", 1, 8, 1, module.entry, 0, shoff, EF_MIPS_EE_EABI64,
        ELF_HEADER_SIZE, 0, 0, ELF_SHDR_SIZE, num_sections + 1, shstrtab_index,
    )  # fmt: skip
    out[:ELF_HEADER_SIZE] = header
    return bytes(out)


def from_elf(data: bytes) -> Module:
    """Inverse of to_elf (also accepts any ET_REL object with the same layout)."""
    if data[:4] != b"\x7fELF":
        raise ValueError("not an ELF file")
    (_, _, _, entry, _, shoff, _, _, _, _, shentsize, shnum, shstrndx) = struct.unpack_from(
        "<HHIIIIIHHHHHH", data, 16
    )
    headers = [struct.unpack_from("<10I", data, shoff + shentsize * i) for i in range(shnum)]

    def blob(i: int) -> bytes:
        h = headers[i]
        return b"" if h[1] == SHT_NOBITS else bytes(data[h[4] : h[4] + h[5]])

    shstrtab = blob(shstrndx)
    names = [cstring(shstrtab, h[0]) for h in headers]
    relinfo: list[int] = []
    if RELINFO_SECTION in names:
        r = blob(names.index(RELINFO_SECTION))
        relinfo = list(struct.unpack(f"<{len(r) // 4}I", r))
        shstrtab = shstrtab[: headers[names.index(RELINFO_SECTION)][0]]
        headers = headers[: names.index(RELINFO_SECTION)]
        names = names[: len(headers)]

    symtab_index = names.index(".symtab")
    symbols = blob(symtab_index)
    undefined = [
        i for i in range(1, len(symbols) // SYM_SIZE)
        if struct.unpack_from("<H", symbols, i * SYM_SIZE + 14)[0] == 0
    ]  # fmt: skip
    undefined_set = set(undefined)

    sections = []
    for i, h in enumerate(headers):
        sh_type, size, align = h[1], h[5], h[8]
        if i == shstrndx:
            size = len(shstrtab)  # without the appended .xff.relinfo name
        stored = sh_type in STORED_TYPES and i != 0
        sections.append(Section(h[0], sh_type, size, align, blob(i) if stored else None))
    if headers:
        sections[0] = Section(0, 0, 0, 0, None)

    reltables_import, reltables_local = [], []
    relinfo_iter = iter(relinfo)
    for i, h in enumerate(headers):
        if h[1] != SHT_REL:
            continue
        target, rel = h[7], blob(i)
        target_data = sections[target].data or b""
        imports, locals_ = RelTable(target, True), RelTable(target, False)
        for k in range(len(rel) // REL_SIZE):
            r_offset, r_info = struct.unpack_from("<II", rel, k * REL_SIZE)
            saved = struct.unpack_from("<I", target_data, r_offset)[0]
            if r_info >> 8 in undefined_set:
                imports.entries.append((r_offset, r_info, saved, next(relinfo_iter, r_info)))
            else:
                locals_.entries.append((r_offset, r_info, saved, 0))
        reltables_import.append(imports)
        reltables_local.append(locals_)

    return Module(
        sections=sections,
        shstrtab=shstrtab,
        strtab=blob(names.index(".strtab")),
        symbols=symbols,
        reltables=reltables_import + reltables_local,
        imports=undefined,
        entry=entry,
        num_locals=headers[symtab_index][7] - 1,
    )


# --- CLI -----------------------------------------------------------------------


def info(module: Module) -> str:
    lines = [
        f"{len(module.sections)} sections, {module.num_symbols} symbols "
        f"({module.num_locals} local, {len(module.imports)} imported), "
        f"entry .text+{module.entry:#x}",
    ]
    for i, s in enumerate(module.sections):
        stored = "stored" if s.data is not None else ""
        lines.append(
            f"  [{i:2}] {module.section_name(i)[:40]:40} type={s.type:#010x} "
            f"size={s.size:#9x} align={s.align:#x} {stored}"
        )
    for t in module.reltables:
        kind = "imports" if t.is_import else "locals"
        lines.append(f"  rel {module.section_name(t.target)} {kind}: {len(t.entries)}")
    return "\n".join(lines)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    sub = parser.add_subparsers(dest="command", required=True)
    p = sub.add_parser("info")
    p.add_argument("xff", type=Path)
    for name in ("to-elf", "from-elf", "roundtrip"):
        p = sub.add_parser(name)
        p.add_argument("input", type=Path)
        if name != "roundtrip":
            p.add_argument("output", type=Path)
    args = parser.parse_args(argv)

    if args.command == "info":
        print(info(parse(args.xff.read_bytes())))
        return 0
    if args.command == "roundtrip":
        original = args.input.read_bytes()
        rebuilt = write(from_elf(to_elf(parse(original))))
        same = rebuilt == original
        print(f"{args.input}: {'OK' if same else 'MISMATCH'} (XFF -> ELF -> XFF)")
        return 0 if same else 1

    data = args.input.read_bytes()
    result = to_elf(parse(data)) if args.command == "to-elf" else write(from_elf(data))
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_bytes(result)
    return 0


if __name__ == "__main__":
    sys.exit(main())
