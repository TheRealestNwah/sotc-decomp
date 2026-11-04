"""Functions as words and relocations, read from an EE object, and the rule
for whether two of them match.

The object is either an Original Game module (converted from its XFF) or
compiled C. Every tool that asks "does this C match the Original" goes
through `compare`, so MATCH means the same thing in try_compilers, the
permuter and the splice step.

    elf = open_module("GAMECORE")
    target = function(elf, "nico_swordstart")
    mismatches = compare(target, built)                # targets by name only
    mismatches = compare(target, built, resolver.place)  # also section-relative

A relocation in the Original is either by name (the target is defined in
another Original source file) or section-relative (same file). A by-name
target can be checked from the two objects alone. A section-relative one
can't: it depends on where the C file's own statics and data land in the
Original, which only the splice step works out. Without `place`, such a
word is reported as `unverified`, never as a match.
"""

from __future__ import annotations

import bisect
import io
import re
import sys
import weakref
from collections.abc import Callable
from dataclasses import dataclass
from functools import cache
from pathlib import Path
from typing import Protocol

from elftools.elf.elffile import ELFFile

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT))
from tools.xff2 import parse, to_elf  # noqa: E402

R_MIPS_32, R_MIPS_26, R_MIPS_HI16, R_MIPS_LO16, R_MIPS_GPREL16 = 2, 4, 5, 6, 7
RELOC_NAMES = {
    R_MIPS_32: "R_MIPS_32",
    R_MIPS_26: "R_MIPS_26",
    R_MIPS_HI16: "R_MIPS_HI16",
    R_MIPS_LO16: "R_MIPS_LO16",
    R_MIPS_GPREL16: "R_MIPS_GPREL16",
}
# Bits of the word each relocation type fills in.
FIELD_MASKS = {
    R_MIPS_32: 0xFFFFFFFF,
    R_MIPS_26: 0x03FFFFFF,
    R_MIPS_HI16: 0x0000FFFF,
    R_MIPS_LO16: 0x0000FFFF,
    R_MIPS_GPREL16: 0x0000FFFF,
}
# A Placeholder name: an asm label named after its address (func_000C5468).
ADDRESS_NAME_RE = re.compile(r"[A-Za-z]+_([0-9A-F]{8})")


@dataclass(frozen=True)
class Reloc:
    type: int
    target: str  # symbol name, or section name for section-relative relocations
    section_relative: bool
    addend: int | None = None  # implied addend for section-relative ones


@dataclass
class Function:
    words: list[int]
    relocs: dict[int, Reloc]  # word index -> relocation


@dataclass(frozen=True)
class Mismatch:
    index: int  # word index
    kind: str  # one of KINDS
    detail: str

    @property
    def verified(self) -> bool:
        return self.kind != "unverified"


KINDS = ("length", "instruction", "relocation", "target", "unverified")


class Place(Protocol):
    section: str
    offset: int


Placer = Callable[[Reloc], "Place | None"]


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


@cache
def open_module(module: str, iso_dir: Path = ROOT / "iso") -> ELFFile:
    """An Original Game module (`iso_dir/<MODULE>.XFF`) as an ELF, read once
    per process. Doesn't depend on anything in build/."""
    xff = Path(iso_dir) / f"{module.upper()}.XFF"
    return ELFFile(io.BytesIO(to_elf(parse(xff.read_bytes()))))


def _text_functions(elf: ELFFile) -> list[tuple[int, int, str]]:
    """(start, size, name) of each named function in .text, in address order.
    A symbol without a size runs up to the next one (or the section end)."""
    text_index = elf.get_section_index(".text")
    size_of_text = elf.get_section_by_name(".text")["sh_size"]
    symbols = sorted(
        (s["st_value"], s["st_size"], s.name)
        for s in elf.get_section_by_name(".symtab").iter_symbols()
        if s["st_info"]["type"] == "STT_FUNC" and s["st_shndx"] == text_index and s.name
    )
    out = []
    for i, (start, size, name) in enumerate(symbols):
        if size == 0:
            size = (symbols[i + 1][0] if i + 1 < len(symbols) else size_of_text) - start
        out.append((start, size, name))
    return out


_TEXT: weakref.WeakKeyDictionary = weakref.WeakKeyDictionary()


def _text(elf: ELFFile) -> tuple[bytes, list[tuple[int, Reloc]]]:
    """The object's .text bytes and relocations sorted by offset, read once
    per object (a Game module has tens of thousands of relocations)."""
    if elf not in _TEXT:
        data = elf.get_section_by_name(".text").data()
        _TEXT[elf] = (data, sorted(read_relocs(elf, ".text").items()))
    return _TEXT[elf]


def _cut(elf: ELFFile, start: int, size: int) -> Function:
    data, relocs = _text(elf)
    words = [int.from_bytes(data[o : o + 4], "little") for o in range(start, start + size, 4)]
    lo = bisect.bisect_left(relocs, start, key=lambda item: item[0])
    own = {}
    for offset, reloc in relocs[lo:]:
        if offset >= start + size:
            break
        own[(offset - start) // 4] = reloc
    return Function(words, own)


def functions(elf: ELFFile) -> dict[str, Function]:
    """Every named function in the object's .text."""
    return {name: _cut(elf, start, size) for start, size, name in _text_functions(elf)}


def function(elf: ELFFile, name: str, size: int | None = None) -> Function:
    """One function, by symbol name or by Placeholder name. A Placeholder-named
    static has no symbol: it starts at its asm label's address (a file offset)
    and is `size` bytes long, which the caller takes from the C it compiled.
    Raises KeyError when there's no such function."""
    for start, sym_size, sym_name in _text_functions(elf):
        if sym_name == name:
            return _cut(elf, start, sym_size)
    m = ADDRESS_NAME_RE.fullmatch(name)
    if not m:
        raise KeyError(f"{name}: no such function, and not named after an address")
    if size is None:
        raise KeyError(f"{name}: no symbol for it, so its size has to be given")
    text = elf.get_section_by_name(".text")
    start = int(m.group(1), 16) - text["sh_offset"]  # asm addresses are file offsets
    if not 0 <= start < text["sh_size"]:
        raise KeyError(f"{name}: address outside .text")
    return _cut(elf, start, size)


def describe(reloc: Reloc | None) -> str:
    if reloc is None:
        return "nothing"
    if reloc.section_relative:
        return f"C {reloc.target}+{reloc.addend or 0:#x}"
    return reloc.target


def same_offset(reloc_type: int, mine: int, theirs: int) -> bool:
    """Whether a C target offset agrees with the original's implied addend.
    Only the low 16 bits of a LO16's addend reach its field, and an original
    LO16 without a HI16 of its own (one repeated in a branch delay slot) gets
    its high half from an unrelated HI16, so LO16s compare modulo 0x10000."""
    if reloc_type == R_MIPS_LO16:
        return (mine - theirs) & 0xFFFF == 0
    return mine == theirs


def _compare_word(
    index: int, word: int, orig: int, mine: Reloc | None, theirs: Reloc | None, place
) -> Mismatch | None:
    def miss(kind: str, detail: str) -> Mismatch:
        return Mismatch(index, kind, detail)

    if theirs is None:
        if mine is not None:
            return miss(
                "relocation", f"C has a relocation against {describe(mine)}, the original none"
            )
        return miss("instruction", "instruction") if word != orig else None
    if mine is None or mine.type != theirs.type:
        return miss("relocation", f"relocation {mine and mine.type} vs original {theirs.type}")
    if (word ^ orig) & ~FIELD_MASKS.get(theirs.type, 0) & 0xFFFFFFFF:
        return miss("instruction", "instruction")
    if not theirs.section_relative:
        if mine.section_relative or mine.target != theirs.target or word != orig:
            return miss("target", f"target {describe(mine)} vs original {theirs.target}")
        return None
    # Same Original source file: the target depends on where the C lands.
    if place is None:
        return miss(
            "unverified", f"{describe(mine)}: not checked against the original {theirs.target}"
        )
    at = place(mine)
    if at is None or at.section != theirs.target:
        return miss("target", f"{describe(mine)} isn't in the original {theirs.target}")
    if theirs.addend is not None and not same_offset(theirs.type, at.offset, theirs.addend):
        return miss(
            "target",
            f"points at {at.section}+{at.offset:#x}, "
            f"original at {theirs.target}+{theirs.addend:#x}",
        )
    return None


def _padding(fn: Function, start: int) -> bool:
    """Whether everything from `start` on is alignment padding."""
    return all(fn.words[i] == 0 and i not in fn.relocs for i in range(start, len(fn.words)))


def compare(target: Function, built: Function, place: Placer | None = None) -> list[Mismatch]:
    """Every word where `built` (compiled C) differs from `target` (the
    Original), at most one per word. Empty means a match.

    - Plain words must be equal.
    - A relocated word must have a relocation of the same type, the same
      bits outside the relocated field, and the same target: by name for a
      by-name original, or the same place (via `place`) for a section-relative
      one. LO16 offsets compare modulo 0x10000.
    - Without `place`, section-relative targets come back as `unverified`.
    - Trailing zero words without relocations on the longer side are
      alignment padding and don't count; any other length difference is a
      `length` mismatch at the first word past the shorter one."""
    n = min(len(target.words), len(built.words))
    out = []
    for i in range(n):
        m = _compare_word(
            i, built.words[i], target.words[i], built.relocs.get(i), target.relocs.get(i), place
        )
        if m is not None:
            out.append(m)
    longer = target if len(target.words) > len(built.words) else built
    if not _padding(longer, n):
        out.append(
            Mismatch(
                n,
                "length",
                f"C is {len(built.words)} words, original is {len(target.words)}",
            )
        )
    return out
