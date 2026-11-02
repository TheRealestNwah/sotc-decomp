"""Splice compiled C functions into the Loader's assembly, verifying they match.

    python tools/loader_splice.py build/src/loader/foo.o ... --out build/loader/000000.s

The Loader is a linked executable, so its splat assembly carries no
relocations: references are symbolic operands (`jal func_00102608`,
`%hi(D_0013B348)`, `%gp_rel(D_0013A180 + 0x4)`). Each C function is placed at
its address from config/loader_functions.csv, by Original name or Placeholder
name, and compared word by word with the instruction words splat printed:

- an unrelocated word must be identical, and becomes a `.word` from C;
- a relocated word must have the same relocation type as the operand in the
  original line, the same bits outside the field, and the same target address
  (symbol plus addend). The original line is kept, since it already assembles
  to the Original's bytes.

Anything else is an error, so a C function that doesn't match fails the build.
`ninja check` then compares the linked image with the Original as usual.
C data sections (strings, jump tables, statics) aren't supported yet.
"""

from __future__ import annotations

import argparse
import csv
import io
import json
import re
import sys
from dataclasses import dataclass
from pathlib import Path

from elftools.elf.elffile import ELFFile

ROOT = Path(__file__).resolve().parent.parent
ASM = ROOT / "asm/cod/000000.s"
LIST = ROOT / "config/loader_functions.csv"
SYMBOL_ADDRS = ROOT / "symbol_addrs.txt"

R_MIPS_26, R_MIPS_HI16, R_MIPS_LO16, R_MIPS_GPREL16 = 4, 5, 6, 7
RELOC_NAMES = {
    R_MIPS_26: "R_MIPS_26",
    R_MIPS_HI16: "%hi",
    R_MIPS_LO16: "%lo",
    R_MIPS_GPREL16: "%gp_rel",
}
FIELD_MASKS = {
    R_MIPS_26: 0x03FFFFFF,
    R_MIPS_HI16: 0xFFFF,
    R_MIPS_LO16: 0xFFFF,
    R_MIPS_GPREL16: 0xFFFF,
}
OPERATORS = {"hi": R_MIPS_HI16, "lo": R_MIPS_LO16, "gp_rel": R_MIPS_GPREL16}

# "/* <offset> <address> <word> */  <instruction>"; words are printed little-endian.
LINE_RE = re.compile(r"^\s*/\* [0-9A-F]+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/\s*(.*)$")
OPERAND_RE = re.compile(r"%(hi|lo|gp_rel)\(([^)]*)\)")
JUMP_RE = re.compile(r"^(?:jal|j)\s+(\S+)$")
TARGET_RE = re.compile(r"^\s*([A-Za-z_.$][\w.$]*)\s*(?:([+-])\s*(0x[0-9A-Fa-f]+|\d+))?\s*$")
# Placeholder names spell out their address.
PLACEHOLDER_RE = re.compile(r"^(?:func|D|B|R|jtbl)_([0-9A-F]+)$")
SYMBOL_ADDRS_RE = re.compile(r"^\s*(\S+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;")


class SpliceError(Exception):
    pass


@dataclass
class Reloc:
    type: int
    symbol: str  # a symbol name, or "" for a section-relative one
    section: str  # the section of a section-relative one


@dataclass
class CompiledFunction:
    name: str
    source: str
    start: int  # offset in the C object's .text
    words: list[int]
    relocs: dict[int, Reloc]  # word index -> relocation


@dataclass
class CompiledObject:
    source: str
    functions: list[CompiledFunction]
    data_sections: list[str]


def load_object(obj: Path) -> CompiledObject:
    elf = ELFFile(io.BytesIO(obj.read_bytes()))
    text_index = elf.get_section_index(".text")
    text = elf.get_section_by_name(".text").data()
    relocs: dict[int, Reloc] = {}
    rel = elf.get_section_by_name(".rel.text")
    if rel is not None:
        symtab = elf.get_section(rel["sh_link"])
        for r in rel.iter_relocations():
            sym = symtab.get_symbol(r["r_info_sym"])
            if sym["st_info"]["type"] == "STT_SECTION":
                reloc = Reloc(r["r_info_type"], "", elf.get_section(sym["st_shndx"]).name)
            else:
                reloc = Reloc(r["r_info_type"], sym.name, "")
            relocs[r["r_offset"]] = reloc
    functions = []
    for s in elf.get_section_by_name(".symtab").iter_symbols():
        if s["st_info"]["type"] != "STT_FUNC" or s["st_shndx"] != text_index:
            continue
        start, size = s["st_value"], s["st_size"]
        words = [int.from_bytes(text[o : o + 4], "little") for o in range(start, start + size, 4)]
        own = {(o - start) // 4: r for o, r in relocs.items() if start <= o < start + size}
        functions.append(CompiledFunction(s.name, obj.stem, start, words, own))
    data = [
        sec.name
        for sec in elf.iter_sections()
        if sec["sh_flags"] & 2 and sec["sh_size"] and sec.name not in (".text", ".reginfo")
    ]
    return CompiledObject(obj.stem, sorted(functions, key=lambda f: f.start), data)


def sign16(value: int) -> int:
    value &= 0xFFFF
    return value - 0x10000 if value & 0x8000 else value


def hi_part(address: int) -> int:
    return ((address + 0x8000) >> 16) & 0xFFFF


@dataclass
class Names:
    """Symbol name -> address, for the names the Loader's asm and C use."""

    addresses: dict[str, int]

    @classmethod
    def load(cls, functions_csv: str, symbol_addrs: str = "") -> Names:
        addresses = {}
        for line in symbol_addrs.splitlines():
            m = SYMBOL_ADDRS_RE.match(line)
            if m:
                addresses[m.group(1)] = int(m.group(2), 16)
        for row in csv.DictReader(io.StringIO(functions_csv)):
            addresses[row["name"]] = int(row["address"], 16)
        return cls(addresses)

    def address(self, name: str) -> int | None:
        if name in self.addresses:
            return self.addresses[name]
        m = PLACEHOLDER_RE.match(name)
        return int(m.group(1), 16) if m else None


def original_target(line: str) -> tuple[int, str, int] | None:
    """(relocation type, symbol, addend) of an original line's symbolic
    operand, or None when the line has none."""
    m = OPERAND_RE.search(line)
    if m:
        rtype, expression = OPERATORS[m.group(1)], m.group(2)
    else:
        jump = JUMP_RE.match(line.strip())
        if not jump or jump.group(1).startswith((".", "0x")):
            return None  # a local label or a literal: no relocation in the Original
        rtype, expression = R_MIPS_26, jump.group(1)
    t = TARGET_RE.match(expression)
    if not t:
        raise SpliceError(f"can't read the operand of: {line.strip()}")
    addend = int(t.group(3), 0) if t.group(3) else 0
    return rtype, t.group(1), -addend if t.group(2) == "-" else addend


@dataclass
class Placement:
    """Where the C object's functions go: C .text offset -> Loader address."""

    starts: list[tuple[int, int, int]]  # (C offset, size, address)

    def address(self, offset: int) -> int | None:
        for start, size, address in self.starts:
            if start <= offset < start + size:
                return address + offset - start
        return None


def c_target(
    fn: CompiledFunction, index: int, reloc: Reloc, names: Names, placement: Placement
) -> tuple[str, int | None, int]:
    """The C relocation's symbol, its address if known, and the addend held
    in the instruction (REL relocations)."""
    word = fn.words[index]
    if reloc.type == R_MIPS_26:
        addend = (word & 0x3FFFFFF) << 2
    elif reloc.type == R_MIPS_HI16:
        # The full addend is the HI16's field joined with its paired LO16's.
        lo = next(
            (
                fn.words[i]
                for i in sorted(fn.relocs)
                if i > index
                and fn.relocs[i].type == R_MIPS_LO16
                and (fn.relocs[i].symbol, fn.relocs[i].section) == (reloc.symbol, reloc.section)
            ),
            0,
        )
        addend = ((word & 0xFFFF) << 16) + sign16(lo)
    else:
        addend = sign16(word)
    if reloc.section:
        if reloc.section != ".text":
            raise SpliceError(
                f"{fn.name}: references C data in {reloc.section}, which the Loader splice"
                " doesn't support yet"
            )
        return ".text", placement.address(addend), 0
    return reloc.symbol, names.address(reloc.symbol), addend


def same_target(rtype: int, mine: int, theirs: int) -> bool:
    """Whether two targets give the same field. A LO16 or GPREL16 only holds
    the low half (GPREL16 subtracts the same _gp from both)."""
    if rtype == R_MIPS_HI16:
        return hi_part(mine) == hi_part(theirs)
    if rtype == R_MIPS_26:
        return (mine & 0x0FFFFFFC) == (theirs & 0x0FFFFFFC)
    return (mine - theirs) & 0xFFFF == 0


def generate(
    fn: CompiledFunction,
    address: int,
    original: dict[int, tuple[int, str]],
    names: Names,
    placement: Placement,
) -> dict[int, str]:
    """Replacement instruction text for each address of the function, after
    checking the C output matches the original."""

    def mismatch(i: int, why: str) -> SpliceError:
        return SpliceError(f"{fn.name}: word {i} (+{4 * i:#x}) differs: {why}")

    out = {}
    for i, word in enumerate(fn.words):
        at = address + 4 * i
        if at not in original:
            raise mismatch(i, f"the Loader's asm has no instruction at {at:#x}")
        orig, text = original[at]
        mine, theirs = fn.relocs.get(i), original_target(text)
        if mine is None:
            if theirs is not None:
                raise mismatch(i, f"the original references {theirs[1]}, the C nothing")
            if word != orig:
                raise mismatch(i, f"instruction (C {word:08X}, original {orig:08X})")
            out[at] = f".word 0x{word:08X}"
            continue
        if theirs is None:
            raise mismatch(
                i, f"the C references {mine.symbol or mine.section}, the original nothing"
            )
        rtype, symbol, addend = theirs
        if mine.type != rtype:
            raise mismatch(
                i,
                f"relocation {RELOC_NAMES.get(mine.type, mine.type)},"
                f" original {RELOC_NAMES[rtype]}",
            )
        if (word ^ orig) & ~FIELD_MASKS[rtype] & 0xFFFFFFFF:
            raise mismatch(i, f"instruction (C {word:08X}, original {orig:08X})")
        name, base, c_addend = c_target(fn, i, mine, names, placement)
        orig_base = names.address(symbol)
        if base is None or orig_base is None:
            # Names without a known address (e.g. _gp) must agree by name.
            if name != symbol or not same_target(rtype, c_addend, addend):
                raise mismatch(i, f"target {name}+{c_addend:#x}, original {symbol}+{addend:#x}")
        elif not same_target(rtype, base + c_addend, orig_base + addend):
            raise mismatch(
                i,
                f"target {name} ({base + c_addend:#x}),"
                f" original {symbol} ({orig_base + addend:#x})",
            )
        out[at] = text
    return out


def original_lines(asm: str) -> dict[int, tuple[int, str]]:
    """address -> (word, instruction text) for every instruction line."""
    out = {}
    for line in asm.splitlines():
        m = LINE_RE.match(line)
        if m:
            word = int.from_bytes(bytes.fromhex(m.group(2)), "little")
            out[int(m.group(1), 16)] = (word, m.group(3))
    return out


def splice(asm: str, objects: list[CompiledObject], names: Names, sizes: dict[str, int]) -> str:
    original = original_lines(asm)
    replaced: dict[int, tuple[str, str]] = {}  # address -> (text, source)
    placed: dict[int, str] = {}
    for obj in objects:
        if obj.data_sections:
            raise SpliceError(
                f"{obj.source}.c: has data ({', '.join(obj.data_sections)}), which the Loader"
                " splice doesn't support yet"
            )
        starts = []
        for fn in obj.functions:
            address = names.addresses.get(fn.name)
            if address is None:
                raise SpliceError(f"{fn.name}: not in config/loader_functions.csv")
            if address in placed:
                raise SpliceError(f"{fn.name}: {placed[address]} is already placed at {address:#x}")
            if fn.name in sizes and sizes[fn.name] != 4 * len(fn.words):
                raise SpliceError(
                    f"{fn.name}: C is {4 * len(fn.words):#x} bytes,"
                    f" the Original {sizes[fn.name]:#x}"
                )
            placed[address] = fn.name
            starts.append((fn.start, 4 * len(fn.words), address))
        placement = Placement(starts)
        for fn, (_, _, address) in zip(obj.functions, starts, strict=True):
            for at, text in generate(fn, address, original, names, placement).items():
                replaced[at] = (text, obj.source)

    lines = []
    for line in asm.splitlines():
        m = LINE_RE.match(line)
        if m and int(m.group(1), 16) in replaced:
            text, source = replaced[int(m.group(1), 16)]
            line = f"    /* {m.group(1)} from C ({source}.c) */  {text}"
        lines.append(line)
    return "\n".join(lines) + "\n"


def original_sizes(functions_csv: str) -> dict[str, int]:
    """Sizes of the functions with Original names (placeholders' sizes run
    to the next function and include padding)."""
    return {
        row["name"]: int(row["size"], 16)
        for row in csv.DictReader(io.StringIO(functions_csv))
        if row["evidence"].startswith("Original")
    }


def read_object_list(path: Path) -> list[Path]:
    """Ninja's JSON response file (paths may hold spaces)."""
    objects = json.loads(path.read_text(encoding="utf-8"))
    if not isinstance(objects, list) or any(not isinstance(o, str) or not o for o in objects):
        raise SpliceError(f"{path}: expected a JSON list of object paths")
    return [Path(o) for o in objects]


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument("objects", nargs="*", type=Path)
    parser.add_argument("--objects-file", type=Path, help="JSON list of objects")
    parser.add_argument("--asm", type=Path, default=ASM)
    parser.add_argument("--out", type=Path, required=True)
    args = parser.parse_args(argv)
    functions_csv = LIST.read_text(encoding="utf-8")
    names = Names.load(functions_csv, SYMBOL_ADDRS.read_text(encoding="utf-8"))
    try:
        objects = list(args.objects)
        if args.objects_file:
            objects += read_object_list(args.objects_file)
        text = splice(
            args.asm.read_text(encoding="latin-1"),
            [load_object(o) for o in objects],
            names,
            original_sizes(functions_csv),
        )
    except SpliceError as e:
        print(f"error: {e}", file=sys.stderr)
        return 1
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(text, encoding="latin-1", newline="\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
