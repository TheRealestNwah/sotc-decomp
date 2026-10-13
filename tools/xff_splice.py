"""Replace functions in an XFF module's assembly with compiled C.

    python tools/xff_splice.py GAMECORE build/src/xff/GAMECORE/*.o

Reads asm/xff/<MODULE>/ (from tools/xff_split.py) and writes a copy to
build/xff/<MODULE>/spliced/ where every function defined in the given C
objects is replaced by the compiler's output:

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
    object's relocation at the same place.
- Labels inside the function stay at their offsets.

Functions that need their own data (string literals, jump tables, float
constants in .rodata) aren't supported yet and are reported as errors.
"""

from __future__ import annotations

import argparse
import io
import re
import shutil
import sys
from dataclasses import dataclass
from pathlib import Path

from elftools.elf.elffile import ELFFile

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from tools.xff2 import parse, to_elf  # noqa: E402
from tools.xff_split import (  # noqa: E402
    LINE_RE,
    RELOC_NAMES,
    Reloc,
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


class SpliceError(Exception):
    pass


@dataclass
class CompiledFunction:
    name: str
    source: str
    words: list[int]
    relocs: dict[int, Reloc]  # word index -> relocation (addend = implied addend)


@dataclass
class Symbol:
    value: int
    section: str | None  # None for undefined/absolute


def symbol_table(elf: ELFFile) -> dict[str, Symbol]:
    table = {}
    for s in elf.get_section_by_name(".symtab").iter_symbols():
        if not s.name:
            continue
        shndx = s["st_shndx"]
        section = elf.get_section(shndx).name if isinstance(shndx, int) else None
        table[s.name] = Symbol(s["st_value"], section)
    return table


def compiled_functions(obj: Path) -> list[CompiledFunction]:
    with obj.open("rb") as f:
        elf = ELFFile(io.BytesIO(f.read()))
    text_index = elf.get_section_index(".text")
    text = elf.get_section_by_name(".text").data()
    relocs = read_relocs(elf, ".text")
    for offset, reloc in relocs.items():
        if reloc.section_relative:
            raise SpliceError(
                f"{obj.name}: relocation at .text+{offset:#x} targets {reloc.target} of the C "
                "object itself (string literals, jump tables or constants aren't supported yet)"
            )
    out = []
    for s in elf.get_section_by_name(".symtab").iter_symbols():
        if s["st_info"]["type"] != "STT_FUNC" or s["st_shndx"] != text_index or not s.name:
            continue
        start, size = s["st_value"], s["st_size"]
        words = [int.from_bytes(text[o : o + 4], "little") for o in range(start, start + size, 4)]
        own = {(o - start) // 4: r for o, r in relocs.items() if start <= o < start + size}
        out.append(CompiledFunction(s.name, obj.stem, words, own))
    return out


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


def generate(
    fn: CompiledFunction,
    original_words: list[int],
    original_relocs: dict[int, Reloc],
    symbols: dict[str, Symbol],
    section_bases: dict[str, int],
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
                raise mismatch(f"C has a relocation against {mine.target}, the original none")
            if word != orig:
                raise mismatch("instruction")
            lines.append([f"    .word 0x{word:08X}"])
            continue
        if mine is None or mine.type != theirs.type:
            raise mismatch(f"relocation {mine and mine.type} vs original {theirs.type}")
        mask = FIELD_MASKS[theirs.type]
        if (word ^ orig) & ~mask & 0xFFFFFFFF:
            raise mismatch("instruction")
        name = RELOC_NAMES[theirs.type]
        if not theirs.section_relative:
            if mine.target != theirs.target or word != orig:
                raise mismatch(f"target {mine.target} vs original {theirs.target}")
            lines.append([f'    .reloc ., {name}, "{theirs.target}"', f"    .word 0x{word:08X}"])
            continue
        # Same source file in the original: reference the symbol section-relative.
        symbol = symbols.get(mine.target)
        if symbol is None or symbol.section != theirs.target:
            raise mismatch(f"{mine.target} isn't defined in {theirs.target}")
        addend = mine.addend or 0
        if theirs.addend is not None and symbol.value + addend != theirs.addend:
            raise mismatch(f"points at {mine.target}+{addend:#x}, original elsewhere")
        value = f"{twin(mine.target)} - {section_start(theirs.target)} + {addend:#x}"
        needs_twin.add(mine.target)
        lines.append(
            [
                f"    .reloc ., {name}, {section_start(theirs.target)}",
                f"    .word {field_expression(word, theirs.type, value)}",
            ]
        )
    return lines, needs_twin


def replace_function(
    lines: list[str], name: str, base: int, start: int, generated: list[list[str]], source: str
) -> list[str]:
    try:
        first = next(i for i, line in enumerate(lines) if label_name(line) == name)
        last = next(
            i
            for i in range(first, len(lines))
            if re.match(rf"\s*endlabel\s+{re.escape(name)}\b", lines[i])
        )
    except StopIteration:
        raise SpliceError(f"{name}: not found in the module's text.s") from None
    out, used = [], 0
    for line in lines[first : last + 1]:
        if line.strip().startswith(".reloc "):
            continue  # regenerated below
        m = LINE_RE.match(line)
        if not m:
            out.append(line)
            continue
        index = (int(m.group(2), 16) - base - start) // 4
        out.append(f"    /* {index * 4:04X} from C ({source}.c) */")
        out.extend(generated[index])
        used += 1
    if used != len(generated):
        raise SpliceError(f"{name}: replaced {used} of {len(generated)} words")
    return lines[:first] + out + lines[last + 1 :]


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


def splice(module: str, objects: list[Path], asm_dir: Path, out_dir: Path, original: Path) -> int:
    with original.open("rb") as f:
        elf = ELFFile(io.BytesIO(f.read()))
    symbols = symbol_table(elf)
    text = elf.get_section_by_name(".text")
    base = text["sh_offset"]
    text_data = text.data()
    section_bases = {s.name: s["sh_offset"] for s in elf.iter_sections() if s.name}
    relocs = read_relocs(elf, ".text")

    files = {p.name: p.read_text(encoding="latin-1").splitlines() for p in asm_dir.glob("*.s")}
    if "text.s" not in files:
        raise SpliceError(f"{asm_dir} has no text.s; run tools/xff_split.py first")
    twins: set[str] = set()
    count = 0
    for obj in objects:
        for fn in compiled_functions(obj):
            symbol = symbols.get(fn.name)
            if symbol is None or symbol.section != ".text":
                raise SpliceError(f"{fn.name} ({obj.name}): no such function in {module}")
            start = symbol.value
            size = 4 * len(fn.words)
            original_words = [
                int.from_bytes(text_data[o : o + 4], "little")
                for o in range(start, start + size, 4)
            ]
            original_relocs = {
                (o - start) // 4: r for o, r in relocs.items() if start <= o < start + size
            }
            generated, need = generate(fn, original_words, original_relocs, symbols, section_bases)
            files["text.s"] = replace_function(
                files["text.s"], fn.name, base, start, generated, fn.source
            )
            twins |= need
            count += 1
    add_missing_twins(files, twins)

    if out_dir.exists():
        shutil.rmtree(out_dir)
    out_dir.mkdir(parents=True)
    for name, lines in files.items():
        (out_dir / name).write_text("\n".join(lines) + "\n", encoding="latin-1")
    return count


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument("module")
    parser.add_argument("objects", type=Path, nargs="*")
    parser.add_argument("--out", type=Path, help="default build/xff/<MODULE>/spliced")
    args = parser.parse_args(argv)
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
