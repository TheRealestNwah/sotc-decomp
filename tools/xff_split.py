"""Disassemble an XFF module into assembly that reassembles to the original.

    python tools/xff_split.py iso/KERNEL.XFF            # writes asm/xff/KERNEL/
    python tools/xff_split.py iso/KERNEL.XFF --check    # also reassemble and compare

Steps:
1. Convert the XFF to an ELF relocatable object (tools/xff2.py).
2. Disassemble it with spimdisasm's elfObjDisasm.
3. Post-process the assembly, using the original relocations as ground truth:
   - words spimdisasm turned into symbol references, but that have no
     relocation in the original, go back to plain values;
   - references the original makes section-relative (a global defined in the
     same original source file, or a local) use local twin labels, so the
     assembler emits section+offset like the original did;
   - every section-relative reference is checked against the address the
     original relocation implies. Where spimdisasm got it wrong, the line keeps
     its original bytes and gets an explicit `.reloc`;
   - branches to addresses spimdisasm referenced without a label get one;
   - an unaligned tail at the end of a section is emitted as .byte.
4. Write asm/xff/<MODULE>/<MODULE>.s, which includes the section files and
   marks the original global symbols .globl.

Nothing is edited by hand: everything is derived from the original object,
and re-running the tool regenerates it.
"""

from __future__ import annotations

import argparse
import re
import shutil
import subprocess
import sys
import tempfile
from dataclasses import dataclass, field
from pathlib import Path

from elftools.elf.elffile import ELFFile

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from tools.xff2 import parse, to_elf  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
LINE_RE = re.compile(r"^(\s*/\* ([0-9A-F]+) ([0-9A-F]+) ([0-9A-F]+) \*/\s+)(\S+)(.*)$")
BSS_LINE_RE = re.compile(r"^\s*/\* ([0-9A-F]+) \*/")
LABEL_RE = re.compile(
    r"^\s*(?:glabel|dlabel|alabel|jlabel|ehlabel)\s+(\S+)|^\s*([A-Za-z_][\w.$]*):\s*$"
)
SECTION_RE = re.compile(r"^\.section\s+([^\s,]+)")
SYMBOL_RE = re.compile(r"[A-Za-z_.$][A-Za-z0-9_.$]*")
NUMBER_RE = re.compile(r"(?<![\w.$])-?0x[0-9A-Fa-f]+|%(?:hi|lo|gp_rel)|\$\w+")
ADDRESS_NAME_RE = re.compile(r"[A-Za-z]+_([0-9A-F]{8})")
OFFSET_RE = r"(?<![\w.$]){name}(?![\w.$])(?:\s*([+-])\s*(0x[0-9A-Fa-f]+|\d+))?"
RELOC_NAMES = {
    2: "R_MIPS_32",
    4: "R_MIPS_26",
    5: "R_MIPS_HI16",
    6: "R_MIPS_LO16",
    7: "R_MIPS_GPREL16",
}
R_MIPS_32, R_MIPS_26, R_MIPS_HI16, R_MIPS_LO16 = 2, 4, 5, 6
DEFAULT_AS = "mips64r5900el-ps2-elf-as"
ASFLAGS = ["-EL", "-march=r5900", "-mabi=eabi", "-G", "0", "-no-pad-sections"]


@dataclass(frozen=True)
class Reloc:
    type: int
    target: str  # symbol name, or section name for section-relative relocations
    section_relative: bool
    addend: int | None = None  # implied addend for section-relative ones


def label_name(line: str) -> str | None:
    m = LABEL_RE.match(line)
    return (m.group(1) or m.group(2)) if m else None


def twin(name: str) -> str:
    return f".Lxff.{name}"


def section_start(section: str) -> str:
    return f".Lxff.start{section}"


def sext16(value: int) -> int:
    value &= 0xFFFF
    return value - 0x10000 if value & 0x8000 else value


def read_relocs(elf: ELFFile, section_name: str) -> dict[int, Reloc]:
    """Relocations for a section, keyed by offset. Section-relative ones get
    the addend implied by the instruction bits (pairing HI16/LO16)."""
    rel = elf.get_section_by_name(".rel" + section_name)
    target_section = elf.get_section_by_name(section_name)
    if rel is None or target_section is None:
        return {}
    data = target_section.data()
    symtab = elf.get_section(rel["sh_link"])
    entries = []
    for r in rel.iter_relocations():
        sym = symtab.get_symbol(r["r_info_sym"])
        if sym["st_info"]["type"] == "STT_SECTION":
            target, section_relative = elf.get_section(sym["st_shndx"]).name, True
        else:
            target, section_relative = sym.name, False
        word = int.from_bytes(data[r["r_offset"] : r["r_offset"] + 4], "little")
        entries.append((r["r_offset"], r["r_info_type"], target, section_relative, word))

    relocs: dict[int, Reloc] = {}
    last_hi: dict[str, int] = {}
    for i, (offset, rtype, target, section_relative, word) in enumerate(entries):
        addend = None
        if rtype == R_MIPS_32:
            addend = word
        elif rtype == R_MIPS_26:
            addend = (word & 0x3FFFFFF) << 2
        elif rtype == R_MIPS_HI16:
            last_hi[target] = word
            lo = next(
                (e[4] for e in entries[i + 1 :] if e[1] == R_MIPS_LO16 and e[2] == target), None
            )
            if lo is not None:
                addend = ((word & 0xFFFF) << 16) + sext16(lo)
        elif rtype == R_MIPS_LO16:
            hi = last_hi.get(target)
            addend = ((hi & 0xFFFF) << 16 if hi is not None else 0) + sext16(word)
        relocs[offset] = Reloc(rtype, target, section_relative, addend)
    return relocs


def symbols_by(elf: ELFFile, predicate) -> list:
    return [s for s in elf.get_section_by_name(".symtab").iter_symbols() if s.name and predicate(s)]


@dataclass
class Fixups:
    plain_words: int = 0
    twins: int = 0
    explicit_relocs: int = 0
    tail_bytes: int = 0
    unresolved: int = 0


@dataclass
class SectionAsm:
    name: str  # ".text", ".vutext", ...
    lines: list[str]
    base: int = 0  # spimdisasm address of the section start (its ELF file offset)
    size: int = 0
    data: bytes = b""
    relocs: dict[int, Reloc] = field(default_factory=dict)


def label_addresses(sections: list[SectionAsm]) -> dict[str, tuple[str, int]]:
    """Every label spimdisasm defined: name -> (section, address)."""
    labels: dict[str, tuple[str, int]] = {}
    for sec in sections:
        pending: list[str] = []
        for line in sec.lines:
            if name := label_name(line):
                pending.append(name)
                continue
            m = LINE_RE.match(line) or BSS_LINE_RE.match(line)
            if m and pending:
                for name in pending:
                    labels[name] = (
                        sec.name,
                        int(m.group(2) if m.re is LINE_RE else m.group(1), 16),
                    )
                pending = []
        for name in pending:
            labels[name] = (sec.name, sec.base + sec.size)
    return labels


def referenced_address(name: str, operands: str, labels: dict[str, tuple[str, int]]) -> int | None:
    if name in labels:
        address = labels[name][1]
    elif m := ADDRESS_NAME_RE.fullmatch(name):
        address = int(m.group(1), 16)
    else:
        return None
    m = re.search(OFFSET_RE.format(name=re.escape(name)), operands)
    if m and m.group(1):
        delta = int(m.group(2), 0)
        address += delta if m.group(1) == "+" else -delta
    return address


def replace_name(operands: str, name: str, new: str) -> str:
    return re.sub(rf"(?<![\w.$]){re.escape(name)}(?![\w.$])", new, operands)


def postprocess(
    sec: SectionAsm,
    labels: dict[str, tuple[str, int]],
    bases: dict[str, int],
    fixups: Fixups,
) -> tuple[list[str], set[str], dict[str, tuple[str, int]]]:
    """Rewrite one section. Returns new lines, labels that need a local twin,
    and unlabeled addresses (name -> (section, address)) that need defining."""
    out: list[str] = []
    needs_twin: set[str] = set()
    unlabeled: dict[str, tuple[str, int]] = {}
    covered = 0

    def explicit(prefix: str, offset: int, reloc: Reloc, original: str) -> None:
        value = int.from_bytes(sec.data[offset : offset + 4], "little")
        target = section_start(reloc.target) if reloc.section_relative else f'"{reloc.target}"'
        out.append(f"    .reloc ., {RELOC_NAMES[reloc.type]}, {target}")
        text = re.sub(r"/\*.*?\*/", "", original).strip()
        out.append(
            f"{prefix}.word 0x{value:08X} /* {text} */" if text else f"{prefix}.word 0x{value:08X}"
        )
        fixups.explicit_relocs += 1

    for line in sec.lines:
        m = LINE_RE.match(line)
        if not m:
            out.append(line)
            continue
        prefix, rom, _vram, raw, mnemonic, operands = m.groups()
        offset = int(rom, 16) - sec.base
        covered = max(covered, offset + len(raw) // 2)
        reloc = sec.relocs.get(offset)
        names = SYMBOL_RE.findall(NUMBER_RE.sub(" ", operands))

        if reloc is None:
            if mnemonic == ".word" and names:
                value = int.from_bytes(sec.data[offset : offset + 4], "little")
                out.append(f"{prefix}.word 0x{value:08X}")
                fixups.plain_words += 1
                continue
            if "%" in operands or mnemonic in ("jal", "j"):
                fixups.unresolved += 1
            for name in names:  # branches: resolve locally, like the original
                if name in labels:
                    needs_twin.add(name)
                elif m_addr := ADDRESS_NAME_RE.fullmatch(name):
                    unlabeled[name] = (sec.name, int(m_addr.group(1), 16))
                else:
                    continue
                operands = replace_name(operands, name, twin(name))
                fixups.twins += 1
            out.append(f"{prefix}{mnemonic}{operands}")
            continue

        if reloc.type not in RELOC_NAMES:
            raise ValueError(f"unsupported relocation type {reloc.type} at {sec.name}+{offset:#x}")
        if not names:
            # spimdisasm emitted a relocated word as a plain value (usually code
            # it decoded as data). The bytes are right; re-attach the relocation.
            explicit(prefix, offset, reloc, line)
            continue
        if not reloc.section_relative:
            # Against a named symbol: spimdisasm must use that symbol, with the
            # same addend (it drops addends on imported symbols).
            m_off = re.search(OFFSET_RE.format(name=re.escape(reloc.target)), operands)
            written = 0
            if m_off and m_off.group(1):
                written = int(m_off.group(2), 0) * (1 if m_off.group(1) == "+" else -1)
            addend = reloc.addend
            if reloc.type in (R_MIPS_32, R_MIPS_HI16, R_MIPS_LO16) and addend is not None:
                addend = ((addend + 0x80000000) & 0xFFFFFFFF) - 0x80000000
            if m_off is None or (addend is not None and written != addend):
                explicit(prefix, offset, reloc, line)
                continue
            out.append(f"{prefix}{mnemonic}{operands}")
            continue

        # Section-relative: the reference must land where the original points.
        expected = None if reloc.addend is None else bases[reloc.target] + reloc.addend
        name = names[0]
        if len(names) != 1 or expected is None:
            explicit(prefix, offset, reloc, line)
            continue
        actual = referenced_address(name, operands, labels)
        in_target = labels[name][0] == reloc.target if name in labels else True
        if actual != expected or not in_target:
            explicit(prefix, offset, reloc, line)
            continue
        if name in labels:
            needs_twin.add(name)
        else:
            unlabeled[name] = (reloc.target, int(ADDRESS_NAME_RE.fullmatch(name).group(1), 16))
        out.append(f"{prefix}{mnemonic}{replace_name(operands, name, twin(name))}")
        fixups.twins += 1

    if sec.data and covered < len(sec.data) and len(sec.data) - covered < 4:
        tail = sec.data[covered:]
        out.append("    .byte " + ", ".join(f"0x{b:02X}" for b in tail))
        fixups.tail_bytes += len(tail)
    return out, needs_twin, unlabeled


def add_twins(lines: list[str], names: set[str]) -> list[str]:
    out = []
    for line in lines:
        out.append(line)
        name = label_name(line)
        if name in names:
            out.append(f"{twin(name)}:")
        elif m := SECTION_RE.match(line):
            out.append(f"{section_start(m.group(1))}:")
    return out


def file_stem(section: str) -> str:
    return section.lstrip(".").replace(".", "_")


def global_aliases(
    exports: list[tuple[str, str, int, str]], sections: list[SectionAsm], defined: set[str]
) -> dict[str, list[str]]:
    """Bind exports omitted by disassembly to offsets in emitted sections."""
    sizes = {sec.name: sec.size for sec in sections}
    aliases = {}
    for name, section, offset, kind in exports:
        if name in defined or section not in sizes:
            continue
        if not 0 <= offset <= sizes[section]:
            raise ValueError(f"{name}: offset {offset:#x} is outside {section}")
        lines = [f'.set "{name}", {section_start(section)} + 0x{offset:X}']
        if kind in ("STT_FUNC", "STT_OBJECT"):
            lines.append(f'.type "{name}", @{"function" if kind == "STT_FUNC" else "object"}')
        aliases[name] = lines
    return aliases


def split(xff: Path, out_dir: Path, obj_dir: Path) -> tuple[Path, Fixups, list[str]]:
    module_name = xff.stem.upper()
    obj_dir.mkdir(parents=True, exist_ok=True)
    obj = obj_dir / f"{module_name}.o"
    obj.write_bytes(to_elf(parse(xff.read_bytes())))

    with tempfile.TemporaryDirectory() as tmp:
        subprocess.run(
            [sys.executable, "-m", "spimdisasm", "elfObjDisasm", str(obj), tmp,
             "--instr-category", "r5900", "--no-string-guesser"],
            check=True, capture_output=True,
        )  # fmt: skip
        sections = []
        for path in sorted(Path(tmp).glob("*.s")):
            lines = path.read_text(encoding="latin-1").splitlines()
            name = next(m.group(1) for line in lines if (m := SECTION_RE.match(line)))
            sections.append(SectionAsm(name, lines))

    with obj.open("rb") as f:
        elf = ELFFile(f)
        bases = {s.name: s["sh_offset"] for s in elf.iter_sections() if s.name}
        for sec in sections:
            section = elf.get_section_by_name(sec.name)
            sec.base, sec.size = section["sh_offset"], section["sh_size"]
            sec.data = section.data() if section["sh_type"] != "SHT_NOBITS" else b""
            sec.relocs = read_relocs(elf, sec.name)
        globals_ = [s.name for s in symbols_by(elf, lambda s: s["st_info"]["bind"] == "STB_GLOBAL"
                                               and s["st_shndx"] != "SHN_UNDEF")]  # fmt: skip
        absolutes = {
            s.name: s["st_value"] for s in symbols_by(elf, lambda s: s["st_shndx"] == "SHN_ABS")
        }
        exports = [
            (s.name, elf.get_section(s["st_shndx"]).name, s["st_value"], s["st_info"]["type"])
            for s in symbols_by(
                elf,
                lambda s: s["st_info"]["bind"] == "STB_GLOBAL" and isinstance(s["st_shndx"], int),
            )
        ]

    order = {".text": 0, ".vutext": 1, ".data": 2, ".vudata": 3, ".rodata": 4, ".bss": 5}
    sections.sort(key=lambda s: order.get(s.name, 9))
    labels = label_addresses(sections)
    fixups = Fixups()
    twins: set[str] = set()
    unlabeled: dict[str, tuple[str, int]] = {}
    processed = {}
    for sec in sections:
        lines, need, missing = postprocess(sec, labels, bases, fixups)
        processed[sec.name] = lines
        twins |= need
        unlabeled |= missing

    if out_dir.exists():
        shutil.rmtree(out_dir)
    out_dir.mkdir(parents=True)
    for name, lines in processed.items():
        lines = [line for line in add_twins(lines, twins) if not line.startswith(".include")]
        (out_dir / f"{file_stem(name)}.s").write_text("\n".join(lines) + "\n", encoding="latin-1")

    sets = []
    for name, (section, address) in sorted(unlabeled.items()):
        delta = address - bases[section]
        sign = "+" if delta >= 0 else "-"
        sets.append(f".set {twin(name)}, {section_start(section)} {sign} 0x{abs(delta):X}")

    defined = {n for lines in processed.values() for line in lines if (n := label_name(line))}
    aliases = global_aliases(exports, sections, defined)
    defined.update(aliases)
    main_file = out_dir / f"{module_name}.s"
    main_file.write_text(
        "\n".join(
            [f"/* {module_name}: generated by tools/xff_split.py */", '.include "xff_macro.inc"']
            + [f'.include "{file_stem(name)}.s"' for name in processed]
            + sets
            + [line for lines in aliases.values() for line in lines]
            + [f'.set "{name}", 0x{value:X}' for name, value in absolutes.items()]
            + [f'.globl "{g}"' for g in globals_ if g in defined or g in absolutes]
        )
        + "\n",
        encoding="latin-1",
    )
    missing_globals = [g for g in globals_ if g not in defined and g not in absolutes]
    return main_file, fixups, missing_globals


def compare(original: Path, rebuilt: Path) -> bool:
    ok = True
    with original.open("rb") as fa, rebuilt.open("rb") as fb:
        a, b = ELFFile(fa), ELFFile(fb)
        for sa in a.iter_sections():
            if not sa["sh_flags"] & 2 or sa["sh_type"] not in ("SHT_PROGBITS", "SHT_NOBITS"):
                continue
            name = sa.name
            sb = b.get_section_by_name(name)
            if sb is None:
                if sa["sh_size"]:
                    print(f"  {name}: missing")
                    ok = False
                continue
            if sa["sh_type"] == "SHT_NOBITS":
                same = sa["sh_size"] == sb["sh_size"]
                print(f"  {name}: size {'OK' if same else 'DIFF'}")
                ok &= same
                continue
            da, db = sa.data(), sb.data()
            ra, rb = read_relocs(a, name), read_relocs(b, name)
            key = lambda r: (r.type, r.target, r.section_relative)  # noqa: E731
            bad = sorted(
                {k for k in ra if k not in rb or key(rb[k]) != key(ra[k])} | (rb.keys() - ra.keys())
            )
            words = sum(
                1 for i in range(0, max(len(da), len(db)), 4) if da[i : i + 4] != db[i : i + 4]
            )
            same = da == db and not bad
            ok &= same
            print(
                f"  {name}: {'OK' if same else 'DIFF'} "
                f"(bytes {'match' if da == db else f'{words} words differ'}, "
                f"{len(ra)} relocations{'' if not bad else f', {len(bad)} differ'})"
            )
            for k in bad[:3]:
                print(f"      at {k:#x}: original {ra.get(k)}, rebuilt {rb.get(k)}")
    return ok


def assemble(source: Path, output: Path, assembler: str) -> None:
    output.parent.mkdir(parents=True, exist_ok=True)
    result = subprocess.run(
        [assembler, *ASFLAGS, "-I", str(ROOT / "include"), "-I", str(source.parent),
         "-o", str(output), str(source)],
        capture_output=True, text=True,
    )  # fmt: skip
    if result.returncode != 0:
        raise RuntimeError(result.stderr[-2000:])


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument("xff", type=Path, nargs="*")
    parser.add_argument("--check", action="store_true", help="reassemble and compare")
    parser.add_argument("--as", dest="assembler", default=DEFAULT_AS)
    parser.add_argument(
        "--compare", nargs=2, type=Path, metavar=("ORIGINAL", "REBUILT"),
        help="only compare two objects (used by `ninja check`)",
    )  # fmt: skip
    args = parser.parse_args(argv)

    if args.compare:
        original, rebuilt = args.compare
        print(f"{rebuilt}:")
        return 0 if compare(original, rebuilt) else 1
    if not args.xff:
        parser.error("give at least one XFF file, or --compare")
    ok = True
    for xff in args.xff:
        name = xff.stem.upper()
        main_file, f, missing = split(xff, ROOT / "asm" / "xff" / name, ROOT / "build" / "xff")
        print(
            f"{name}: wrote {main_file.relative_to(ROOT)} ({f.twins} local refs, "
            f"{f.explicit_relocs} explicit relocs, {f.plain_words} plain words, "
            f"{f.tail_bytes} tail bytes, {f.unresolved} unrelocated symbol refs)"
        )
        if missing:
            print(f"  note: {len(missing)} global symbols have no label, e.g. {missing[:3]}")
        if args.check:
            rebuilt = ROOT / "build" / "xff" / name / f"{name}.o"
            assemble(main_file, rebuilt, args.assembler)
            ok &= compare(ROOT / "build" / "xff" / f"{name}.o", rebuilt)
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
