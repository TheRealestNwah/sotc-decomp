"""Replace functions in an XFF module's assembly with compiled C.

    python tools/xff_splice.py GAMECORE build/src/xff/GAMECORE/*.o
    python tools/xff_splice.py GAMECORE --objects-file objects.json

The object list is a JSON array of paths, in splice order. Ninja uses this
response-file form to avoid Windows process command-line length limits.

Reads asm/xff/<MODULE>/ (from tools/xff_split.py) and writes a copy to
build/xff/<MODULE>/spliced/ where every function defined in the given C
objects, and the data those objects own, is replaced by the compiler's output:

- Every word must match the original exactly. Instructions are compared
  directly; relocated fields are compared by target. A mismatch is an error
  naming the function and the first differing word, so a non-matching C
  function can never slip into the build.
- Plain words are emitted as-is. Relocated words get an explicit `.reloc`
  and their field is recomputed by the assembler from labels:
  - by name, when the original references the symbol by name (it lives in
    another source file);
  - section-relative, when the original does (same source file). Which form
    applies is a property of the original file layout, which the C files
    don't mirror yet (see docs/findings.md); it's taken from the original
    object's relocation at the same place. The value goes through the local
    label at the target where there is one.
- Labels inside the function stay at their offsets.

Data owned by the C object (string literals, jump tables, constants, statics
in .rodata/.data/.bss):
- Each C data section is placed where the original references it: every
  spliced instruction that points into the C section is paired with the
  original relocation at the same place, and named C data symbols with the
  original symbol of the same name. All of them must agree on one location.
- Its bytes must equal the original's there. Relocations must sit at the same
  offsets, with the same type and target (C text maps to the spliced
  functions' original addresses).
- The matching lines in rodata.s/data.s are regenerated from the C output.
  .bss has no contents, so it's only placed and range-checked.
"""

from __future__ import annotations

import argparse
import io
import json
import re
import shutil
import sys
from dataclasses import dataclass, field
from pathlib import Path

from elftools.elf.elffile import ELFFile

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from tools.xff2 import parse, to_elf  # noqa: E402
from tools.xff_split import (  # noqa: E402
    ADDRESS_NAME_RE,
    LINE_RE,
    RELOC_NAMES,
    SECTION_RE,
    Reloc,
    file_stem,
    label_name,
    read_relocs,
    section_start,
    twin,
)

ROOT = Path(__file__).resolve().parent.parent
R_MIPS_32, R_MIPS_26, R_MIPS_HI16, R_MIPS_LO16 = 2, 4, 5, 6
FIELD_MASKS = {
    R_MIPS_32: 0xFFFFFFFF,
    R_MIPS_26: 0x03FFFFFF,
    R_MIPS_HI16: 0xFFFF,
    R_MIPS_LO16: 0xFFFF,
}
# Any addressed line: "/* <offset> <address> [<bytes>] */". Strings have no bytes column.
ADDRESS_RE = re.compile(r"^\s*/\* ([0-9A-F]+) ([0-9A-F]+)(?: [0-9A-F]+)? \*/")
TWIN_DEF_RE = re.compile(r"^(\.Lxff\.[^\s:]+):\s*$")
SKIPPED_SECTIONS = {".text", ".reginfo"}


class SpliceError(Exception):
    pass


@dataclass
class CompiledFunction:
    name: str
    source: str
    words: list[int]
    relocs: dict[int, Reloc]  # word index -> relocation (addend = implied addend)
    start: int = 0  # offset in the C object's .text
    local: bool = False  # static in C


@dataclass
class DataSection:
    name: str
    size: int
    data: bytes  # empty for NOBITS
    nobits: bool
    relocs: dict[int, Reloc]
    symbols: dict[str, int]  # named symbols defined in it -> offset


@dataclass
class CompiledObject:
    source: str
    functions: list[CompiledFunction]
    data: dict[str, DataSection]


@dataclass
class Symbol:
    value: int
    section: str | None  # None for undefined/absolute


@dataclass(frozen=True)
class Place:
    section: str
    offset: int

    def __str__(self) -> str:
        return f"{self.section}+{self.offset:#x}"


@dataclass
class OriginalSection:
    name: str
    base: int  # file offset; the asm's addresses are file offsets
    size: int
    data: bytes
    nobits: bool
    relocs: dict[int, Reloc]


def symbol_table(elf: ELFFile) -> dict[str, Symbol]:
    table = {}
    for s in elf.get_section_by_name(".symtab").iter_symbols():
        if not s.name:
            continue
        shndx = s["st_shndx"]
        section = elf.get_section(shndx).name if isinstance(shndx, int) else None
        table[s.name] = Symbol(s["st_value"], section)
    return table


def load_object(obj: Path) -> CompiledObject:
    with obj.open("rb") as f:
        elf = ELFFile(io.BytesIO(f.read()))
    text_index = elf.get_section_index(".text")
    text = elf.get_section_by_name(".text").data()
    relocs = read_relocs(elf, ".text")
    functions, data = [], {}
    symbols = [s for s in elf.get_section_by_name(".symtab").iter_symbols() if s.name]
    for s in symbols:
        if s["st_info"]["type"] != "STT_FUNC" or s["st_shndx"] != text_index:
            continue
        start, size = s["st_value"], s["st_size"]
        words = [int.from_bytes(text[o : o + 4], "little") for o in range(start, start + size, 4)]
        own = {(o - start) // 4: r for o, r in relocs.items() if start <= o < start + size}
        local = s["st_info"]["bind"] == "STB_LOCAL"
        functions.append(CompiledFunction(s.name, obj.stem, words, own, start, local))
    for index, sec in enumerate(elf.iter_sections()):
        if not sec["sh_flags"] & 2 or sec.name in SKIPPED_SECTIONS or not sec["sh_size"]:
            continue  # not allocated, or empty
        nobits = sec["sh_type"] == "SHT_NOBITS"
        data[sec.name] = DataSection(
            sec.name,
            sec["sh_size"],
            b"" if nobits else sec.data(),
            nobits,
            read_relocs(elf, sec.name),
            {s.name: s["st_value"] for s in symbols if s["st_shndx"] == index},
        )
    return CompiledObject(obj.stem, functions, data)


def field_expression(word: int, reloc_type: int, value_expr: str) -> str:
    keep = word & ~FIELD_MASKS[reloc_type] & 0xFFFFFFFF
    if reloc_type == R_MIPS_32:
        return f"({value_expr})"
    if reloc_type == R_MIPS_26:
        field = f"((({value_expr}) >> 2) & 0x3FFFFFF)"
    elif reloc_type == R_MIPS_HI16:
        field = f"((({value_expr}) + 0x8000) >> 16 & 0xFFFF)"
    else:
        field = f"(({value_expr}) & 0xFFFF)"
    return f"0x{keep:08X} | {field}"


@dataclass
class Resolver:
    """Maps the C object's relocation targets to places in the original module,
    and names those places in assembly."""

    symbols: dict[str, Symbol]
    sections: dict[str, tuple[int, int]] = field(default_factory=dict)  # name -> (base, size)
    text: list[tuple[int, int, int]] = field(default_factory=list)  # C start, end, original
    data: dict[str, Place] = field(default_factory=dict)  # C section -> original place
    labels: dict[Place, str] = field(default_factory=dict)  # local labels in the asm

    def place(self, reloc: Reloc) -> Place | None:
        addend = reloc.addend or 0
        if not reloc.section_relative:
            symbol = self.symbols.get(reloc.target)
            if symbol is not None:
                return Place(symbol.section, symbol.value + addend) if symbol.section else None
            return self.unnamed(reloc.target, addend)
        if reloc.target == ".text":
            for start, end, original in self.text:
                if start <= addend < end:
                    return Place(".text", original + addend - start)
            return None
        base = self.data.get(reloc.target)
        return Place(base.section, base.offset + addend) if base else None

    def unnamed(self, name: str, addend: int) -> Place | None:
        """Something the original has no symbol for, named after its asm label
        (func_000C3BA0, D_0017B0EC): C can refer to it before it's decompiled."""
        m = ADDRESS_NAME_RE.fullmatch(name)
        if not m:
            return None
        address = int(m.group(1), 16)
        for section, (base, size) in self.sections.items():
            if base <= address < base + size:
                return Place(section, address - base + addend)
        return None

    def relative(self, place: Place) -> str:
        """Expression for a place's offset from its section start."""
        label = self.labels.get(place)
        if label:
            return f"{label} - {section_start(place.section)}"
        return f"{place.offset:#x}"

    def check(self, mine: Reloc | None, theirs: Reloc, word: int, orig: int) -> tuple[str, str]:
        """Checks that a C relocation hits the same target as the original one.
        Returns (reloc directive, word expression), or raises with the reason."""
        if mine is None or mine.type != theirs.type:
            raise SpliceError(f"relocation {mine and mine.type} vs original {theirs.type}")
        if (word ^ orig) & ~FIELD_MASKS[theirs.type] & 0xFFFFFFFF:
            raise SpliceError("instruction")
        name = RELOC_NAMES[theirs.type]
        if not theirs.section_relative:
            if mine.section_relative or mine.target != theirs.target or word != orig:
                raise SpliceError(f"target {describe(mine)} vs original {theirs.target}")
            return f'.reloc ., {name}, "{theirs.target}"', f"0x{word:08X}"
        # Same source file in the original: reference the target section-relative.
        place = self.place(mine)
        if place is None or place.section != theirs.target:
            raise SpliceError(f"{describe(mine)} isn't in the original {theirs.target}")
        if theirs.addend is not None and place.offset != theirs.addend:
            raise SpliceError(f"points at {place}, original at {theirs.target}+{theirs.addend:#x}")
        if mine.section_relative or mine.target not in self.symbols:
            value = self.relative(place)
        else:
            value = f"{twin(mine.target)} - {section_start(place.section)} + {mine.addend or 0:#x}"
        return (
            f".reloc ., {name}, {section_start(place.section)}",
            field_expression(word, theirs.type, value),
        )

    def twins_needed(self, mine: Reloc | None, theirs: Reloc | None) -> set[str]:
        if (
            mine
            and theirs
            and theirs.section_relative
            and not mine.section_relative
            and mine.target in self.symbols
        ):
            return {mine.target}
        return set()


def describe(reloc: Reloc | None) -> str:
    if reloc is None:
        return "nothing"
    if reloc.section_relative:
        return f"C {reloc.target}+{reloc.addend or 0:#x}"
    return reloc.target


def generate(
    fn: CompiledFunction,
    original_words: list[int],
    original_relocs: dict[int, Reloc],
    resolver: Resolver,
) -> tuple[list[list[str]], set[str]]:
    """Per-word replacement lines, after checking the C output matches the
    original. Also returns the labels that need a local twin."""
    if len(fn.words) != len(original_words):
        raise SpliceError(
            f"{fn.name}: C is {len(fn.words)} words, original is {len(original_words)}"
        )
    needs_twin: set[str] = set()
    lines = []
    for i, (word, orig) in enumerate(zip(fn.words, original_words, strict=True)):
        mine, theirs = fn.relocs.get(i), original_relocs.get(i)

        def mismatch(why: str, i=i, word=word, orig=orig) -> SpliceError:
            return SpliceError(
                f"{fn.name}: word {i} (+{4 * i:#x}) differs: {why} "
                f"(C {word:08X}, original {orig:08X})"
            )

        if theirs is None:
            if mine is not None:
                raise mismatch(f"C has a relocation against {describe(mine)}, the original none")
            if word != orig:
                raise mismatch("instruction")
            lines.append([f"    .word 0x{word:08X}"])
            continue
        try:
            directive, expr = resolver.check(mine, theirs, word, orig)
        except SpliceError as e:
            raise mismatch(str(e)) from None
        needs_twin |= resolver.twins_needed(mine, theirs)
        lines.append([f"    {directive}", f"    .word {expr}"])
    return lines, needs_twin


def place_functions(
    obj: CompiledObject,
    symbols: dict[str, Symbol],
    text_relocs: dict[int, Reloc],
    text_base: int = 0,
) -> dict[str, int]:
    """Original .text offset of each C function. Functions are found by name.
    A static the original has no name for is found by its asm label's name
    (func_000C5468) or placed by the references other spliced functions make
    to it."""
    starts: dict[str, int] = {}
    for fn in obj.functions:
        symbol = symbols.get(fn.name)
        address = ADDRESS_NAME_RE.fullmatch(fn.name)
        if symbol is not None and symbol.section == ".text":
            starts[fn.name] = symbol.value
        elif symbol is None and fn.local and address:
            starts[fn.name] = int(address.group(1), 16) - text_base
        elif not fn.local:
            raise SpliceError(f"{fn.name} ({obj.source}.c): no such function in the module")
    pending = [fn for fn in obj.functions if fn.name not in starts]
    while pending:
        placed = False
        for fn in list(pending):
            end = fn.start + 4 * len(fn.words)
            found = set()
            for other in obj.functions:
                if other.name not in starts:
                    continue
                for i, mine in other.relocs.items():
                    addend = mine.addend or 0
                    if not (mine.section_relative and mine.target == ".text"):
                        continue
                    if not fn.start <= addend < end:
                        continue
                    theirs = text_relocs.get(starts[other.name] + 4 * i)
                    if theirs is None or theirs.target != ".text" or theirs.addend is None:
                        raise SpliceError(
                            f"{other.name}: word {i} (+{4 * i:#x}) references static {fn.name}, "
                            f"the original {describe(theirs)}"
                        )
                    found.add(theirs.addend - (addend - fn.start))
            if len(found) > 1:
                where = ", ".join(f".text+{o:#x}" for o in sorted(found))
                raise SpliceError(f"{fn.name}: references place it at several addresses ({where})")
            if found:
                starts[fn.name] = found.pop()
                pending.remove(fn)
                placed = True
        if not placed:
            names = ", ".join(fn.name for fn in pending)
            raise SpliceError(
                f"{obj.source}.c: static {names} has no name in the original and nothing spliced "
                "references it, so it can't be placed"
            )
    return starts


def function_names(lines: list[str], base: int) -> dict[int, str]:
    """Original .text offset -> the function label the asm uses there
    (glabel, or alabel for code spimdisasm didn't see as a function)."""
    names, pending = {}, None
    for line in lines:
        if re.match(r"\s*[ga]label\s", line):
            pending = label_name(line)
        elif pending and (m := ADDRESS_RE.match(line)):
            names.setdefault(int(m.group(1), 16) - base, pending)
            pending = None
    return names


def place_data(
    obj: CompiledObject,
    starts: dict[str, int],
    text_relocs: dict[int, Reloc],
    symbols: dict[str, Symbol],
) -> dict[str, Place]:
    """Where each of the C object's data sections lands in the original."""
    anchors: dict[str, dict[Place, str]] = {}  # C section -> start -> first evidence
    for fn in obj.functions:
        for i, mine in fn.relocs.items():
            if not mine.section_relative or mine.target not in obj.data:
                continue
            theirs = text_relocs.get(starts[fn.name] + 4 * i)
            if theirs is None or not theirs.section_relative or theirs.addend is None:
                raise SpliceError(
                    f"{fn.name}: word {i} (+{4 * i:#x}) references {describe(mine)}, "
                    f"the original {describe(theirs)}"
                )
            offset = theirs.addend - (mine.addend or 0)
            anchors.setdefault(mine.target, {}).setdefault(
                Place(theirs.target, offset), f"{fn.name} word {i}"
            )
    for sec in obj.data.values():
        for name, value in sec.symbols.items():
            symbol = symbols.get(name)
            if symbol is not None and symbol.section is not None:
                anchors.setdefault(sec.name, {}).setdefault(
                    Place(symbol.section, symbol.value - value), f"symbol {name}"
                )
    placed = {}
    for sec in obj.data.values():
        found = anchors.get(sec.name, {})
        if not found:
            raise SpliceError(
                f"{obj.source}.c: its {sec.name} ({sec.size:#x} bytes) isn't referenced by "
                "anything the original also references, so it can't be placed"
            )
        if len(found) > 1:
            where = ", ".join(f"{p} per {why}" for p, why in sorted(found.items(), key=str))
            raise SpliceError(
                f"{obj.source}.c: its {sec.name} would have to start at several places in the "
                f"original ({where}); either a function doesn't match yet or the C data isn't "
                "laid out like the original's"
            )
        placed[sec.name] = next(iter(found))
    return placed


def generate_data(
    source: str, sec: DataSection, at: Place, original: OriginalSection, resolver: Resolver
) -> tuple[dict[int, list[str]], set[str]]:
    """Checks a C data section against the original at `at`. Returns
    replacement lines for its relocated words (keyed by original offset) and
    the labels that need a local twin."""
    where = f"{source}.c {sec.name}"
    if at.offset < 0 or at.offset + sec.size > original.size:
        raise SpliceError(f"{where}: {sec.size:#x} bytes at {at} run outside the original section")
    if sec.nobits != original.nobits:
        kind = "zero-initialized (.bss)" if sec.nobits else "initialized"
        raise SpliceError(f"{where}: C data is {kind}, the original {at.section} isn't")
    if sec.nobits:
        return {}, set()
    base = at.offset
    theirs_all = {o - base: r for o, r in original.relocs.items() if base <= o < base + sec.size}
    for o in sorted(theirs_all.keys() ^ sec.relocs.keys()):
        raise SpliceError(
            f"{where}+{o:#x} ({at.section}+{base + o:#x}): relocation against "
            f"{describe(sec.relocs.get(o))} in C, {describe(theirs_all.get(o))} in the original"
        )
    reloc_bytes = {o + k for o in sec.relocs for k in range(4)}
    for o in range(sec.size):
        if o not in reloc_bytes and sec.data[o] != original.data[base + o]:
            raise SpliceError(
                f"{where}+{o:#x} ({at.section}+{base + o:#x}) differs: "
                f"C {sec.data[o]:02X}, original {original.data[base + o]:02X}"
            )
    lines: dict[int, list[str]] = {}
    needs_twin: set[str] = set()
    for o, mine in sorted(sec.relocs.items()):
        theirs = theirs_all[o]
        if theirs.type != R_MIPS_32:
            raise SpliceError(f"{where}+{o:#x}: unsupported relocation type {theirs.type}")
        word = int.from_bytes(sec.data[o : o + 4], "little")
        orig = int.from_bytes(original.data[base + o : base + o + 4], "little")
        try:
            directive, expr = resolver.check(mine, theirs, word, orig)
        except SpliceError as e:
            raise SpliceError(f"{where}+{o:#x} ({at.section}+{base + o:#x}) differs: {e}") from None
        needs_twin |= resolver.twins_needed(mine, theirs)
        lines[base + o] = [f"    {directive}", f"    .word {expr}"]
    return lines, needs_twin


def byte_lines(data: bytes, offset: int) -> list[str]:
    """Plain data as .word where aligned, .byte elsewhere."""
    out, i = [], 0
    while i < len(data):
        if (offset + i) % 4 == 0 and i + 4 <= len(data):
            out.append(f"    .word 0x{int.from_bytes(data[i : i + 4], 'little'):08X}")
            i += 4
        else:
            j = i + 1
            while j < len(data) and (offset + j) % 4:
                j += 1
            out.append("    .byte " + ", ".join(f"0x{b:02X}" for b in data[i:j]))
            i = j
    return out


def replace_data(
    lines: list[str],
    original: OriginalSection,
    lo: int,
    hi: int,
    data: bytes,
    reloc_lines: dict[int, list[str]],
    source: str,
) -> list[str]:
    """Regenerates the addressed lines covering original offsets [lo, hi) from
    `data` (the C bytes for that range) and the relocated words' lines.
    Labels and other lines stay where they are."""
    addressed = [
        (i, int(m.group(1), 16) - original.base)
        for i, line in enumerate(lines)
        if (m := ADDRESS_RE.match(line))
    ]
    spans = {
        i: (start, addressed[k + 1][1] if k + 1 < len(addressed) else original.size)
        for k, (i, start) in enumerate(addressed)
    }
    affected = {i for i, (start, end) in spans.items() if start < hi and end > lo}
    if not affected:
        raise SpliceError(f"{source}.c: no lines for {original.name}+{lo:#x} in the asm")
    out: list[str] = []
    pending: list[str] = []  # .reloc lines apply to the next addressed line
    for i, line in enumerate(lines):
        if line.strip().startswith(".reloc "):
            pending.append(line)
            continue
        if i not in spans:
            out.extend(pending)
            out.append(line)
            pending = []
            continue
        if i not in affected:
            out.extend(pending)
            out.append(line)
            pending = []
            continue
        pending = []  # regenerated below
        start, end = spans[i]
        out.append(f"    /* {original.base + start:06X} from C ({source}.c) */")
        o = start
        while o < end:
            if o in reloc_lines:
                out.extend(reloc_lines[o])
                o += 4
                continue
            stop = min([end] + [r for r in reloc_lines if o < r < end])
            chunk = bytearray()
            for p in range(o, stop):
                if lo <= p < hi:
                    chunk.append(data[p - lo])
                else:
                    if any(r <= p < r + 4 for r in original.relocs):
                        raise SpliceError(
                            f"{source}.c: {original.name}+{p:#x} shares a line with the C data "
                            "but is relocated"
                        )
                    chunk.append(original.data[p])
            out.extend(byte_lines(bytes(chunk), o))
            o = stop
    out.extend(pending)
    return out


def replace_function(
    lines: list[str], name: str, base: int, start: int, generated: list[list[str]], source: str
) -> list[str]:
    """Replaces the function's words, starting at its label. A function
    spimdisasm split in two (it ends a function at a tail call) carries on
    through the next labels until every word is replaced."""
    first = next((i for i, line in enumerate(lines) if label_name(line) == name), None)
    if first is None:
        raise SpliceError(f"{name}: not found in the module's text.s")
    out, used, i = [], 0, first
    while i < len(lines):
        line = lines[i]
        i += 1
        if used == len(generated):
            if re.match(r"\s*endlabel\s", line):
                out.append(line)
                break
            if LINE_RE.match(line) or label_name(line) is not None:
                i -= 1  # spimdisasm put no endlabel here; keep the next thing
                break
            out.append(line)
            continue
        if line.strip().startswith(".reloc "):
            continue  # regenerated below
        m = LINE_RE.match(line)
        if not m:
            out.append(line)
            continue
        index = (int(m.group(2), 16) - base - start) // 4
        if index != used:
            raise SpliceError(f"{name}: word {used} isn't where expected in text.s")
        out.append(f"    /* {index * 4:04X} from C ({source}.c) */")
        out.extend(generated[index])
        used += 1
    if used != len(generated):
        raise SpliceError(f"{name}: replaced {used} of {len(generated)} words")
    return lines[:first] + out + lines[i:]


def add_missing_twins(files: dict[str, list[str]], names: set[str]) -> None:
    existing = {
        line[:-1] for lines in files.values() for line in lines if line.startswith(".Lxff.")
    }
    wanted = {n for n in names if twin(n) not in existing}
    for key, lines in files.items():
        out = []
        for line in lines:
            out.append(line)
            n = label_name(line)
            if n in wanted:
                out.append(f"{twin(n)}:")
        files[key] = out


def local_labels(files: dict[str, list[str]], sections: dict[str, OriginalSection]) -> dict:
    """Place -> the local (.Lxff.) label defined there, from the original asm."""
    labels: dict[Place, str] = {}
    for lines in files.values():
        section, pending = None, []
        for line in lines:
            if m := SECTION_RE.match(line):
                section, pending = sections.get(m.group(1)), []
            elif m := TWIN_DEF_RE.match(line):
                if not m.group(1).startswith(".Lxff.start"):
                    pending.append(m.group(1))
            elif section is not None and (m := ADDRESS_RE.match(line) or BSS_RE.match(line)):
                for label in pending:
                    labels[Place(section.name, int(m.group(1), 16) - section.base)] = label
                pending = []
    return labels


BSS_RE = re.compile(r"^\s*/\* ([0-9A-F]+) \*/\s*\.space")


def original_sections(elf: ELFFile) -> dict[str, OriginalSection]:
    out = {}
    for s in elf.iter_sections():
        if not s.name or not s["sh_flags"] & 2:
            continue
        nobits = s["sh_type"] == "SHT_NOBITS"
        out[s.name] = OriginalSection(
            s.name,
            s["sh_offset"],
            s["sh_size"],
            b"" if nobits else s.data(),
            nobits,
            read_relocs(elf, s.name),
        )
    return out


def splice(module: str, objects: list[Path], asm_dir: Path, out_dir: Path, original: Path) -> int:
    with original.open("rb") as f:
        elf = ELFFile(io.BytesIO(f.read()))
    symbols = symbol_table(elf)
    sections = original_sections(elf)
    text = sections[".text"]

    files = {p.name: p.read_text(encoding="latin-1").splitlines() for p in asm_dir.glob("*.s")}
    if "text.s" not in files:
        raise SpliceError(f"{asm_dir} has no text.s; run tools/xff_split.py first")
    labels = local_labels(files, sections)
    names = function_names(files["text.s"], text.base)
    twins: set[str] = set()
    count = 0
    for path in objects:
        obj = load_object(path)
        starts = place_functions(obj, symbols, text.relocs, text.base)
        resolver = Resolver(
            symbols,
            {n: (sec.base, sec.size) for n, sec in sections.items()},
            [(fn.start, fn.start + 4 * len(fn.words), starts[fn.name]) for fn in obj.functions],
            place_data(obj, starts, text.relocs, symbols),
            labels,
        )
        for fn in obj.functions:
            start = starts[fn.name]
            size = 4 * len(fn.words)
            original_words = [
                int.from_bytes(text.data[o : o + 4], "little")
                for o in range(start, start + size, 4)
            ]
            original_relocs = {
                (o - start) // 4: r for o, r in text.relocs.items() if start <= o < start + size
            }
            generated, need = generate(fn, original_words, original_relocs, resolver)
            asm_name = names.get(start)
            if asm_name is None:
                raise SpliceError(f"{fn.name}: no function starts at .text+{start:#x} in text.s")
            files["text.s"] = replace_function(
                files["text.s"], asm_name, text.base, start, generated, fn.source
            )
            twins |= need
            count += 1
        for name, at in resolver.data.items():
            sec, target = obj.data[name], sections.get(resolver.data[name].section)
            if target is None:
                raise SpliceError(f"{obj.source}.c: {at.section} isn't in {module}")
            reloc_lines, need = generate_data(obj.source, sec, at, target, resolver)
            twins |= need
            if sec.nobits:
                continue
            key = f"{file_stem(at.section)}.s"
            files[key] = replace_data(
                files[key], target, at.offset, at.offset + sec.size, sec.data, reloc_lines,
                obj.source,
            )  # fmt: skip
    add_missing_twins(files, twins)

    if out_dir.exists():
        shutil.rmtree(out_dir)
    out_dir.mkdir(parents=True)
    for name, lines in files.items():
        (out_dir / name).write_text("\n".join(lines) + "\n", encoding="latin-1")
    return count


def read_object_list(path: Path) -> list[Path]:
    """Read Ninja's JSON response file without shell path quoting or length limits."""
    try:
        objects = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError) as e:
        raise SpliceError(f"{path}: cannot read object list: {e}") from e
    if not isinstance(objects, list) or any(not isinstance(p, str) or not p for p in objects):
        raise SpliceError(f"{path}: expected a JSON list of nonempty object paths")
    return [Path(p) for p in objects]


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument("module")
    parser.add_argument("objects", type=Path, nargs="*")
    parser.add_argument("--objects-file", type=Path, help="JSON response file listing object paths")
    parser.add_argument("--out", type=Path, help="default build/xff/<MODULE>/spliced")
    args = parser.parse_args(argv)
    if args.objects_file:
        try:
            args.objects.extend(read_object_list(args.objects_file))
        except SpliceError as e:
            parser.error(str(e))
    module = args.module.upper()
    out = args.out or ROOT / f"build/xff/{module}/spliced"
    original = ROOT / f"build/xff/{module}.o"
    if not original.exists():
        original.parent.mkdir(parents=True, exist_ok=True)
        original.write_bytes(to_elf(parse((ROOT / f"iso/{module}.XFF").read_bytes())))
    try:
        count = splice(module, args.objects, ROOT / f"asm/xff/{module}", out, original)
    except SpliceError as e:
        print(f"error: {e}", file=sys.stderr)
        return 1
    print(f"{module}: {count} function(s) from C")
    return 0


if __name__ == "__main__":
    sys.exit(main())
