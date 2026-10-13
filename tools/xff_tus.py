"""Infer the original source files (translation units) in an XFF module.

    python tools/xff_tus.py iso/GAMECORE.XFF            # summary
    python tools/xff_tus.py iso/GAMECORE.XFF --list     # every inferred group

Evidence, from the original relocations in .text:
- A reference the original assembler made section-relative stays inside one
  source file (statics always are; a global only when it's defined in the
  same file). ld -r keeps each file's code contiguous, so every function
  between the caller and the target belongs to that same file.
- A reference made by name to a global defined in this module crosses files:
  there must be a file boundary somewhere between the two.

Groups are lower bounds: one original file may span several adjacent groups
when nothing ties them together. Groups that reference a string that looks
like a source file name (an assert's __FILE__) get that name.
"""

from __future__ import annotations

import argparse
import bisect
import io
import re
import sys
from dataclasses import dataclass, field
from pathlib import Path

from elftools.elf.elffile import ELFFile

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from tools.xff2 import parse, to_elf  # noqa: E402
from tools.xff_split import read_relocs  # noqa: E402

SOURCE_NAME_RE = re.compile(rb"[A-Za-z0-9_./\\-]+\.(?:c|cc|cpp|cxx)\b")


@dataclass
class Group:
    first: int  # function index
    last: int
    names: set[str] = field(default_factory=set)


@dataclass
class Result:
    functions: list[tuple[int, str]]  # (address, name), sorted
    groups: list[Group]
    same_file_links: int
    cross_file_links: int
    conflicts: list[tuple[str, str]]


def source_names(rodata: bytes) -> dict[int, str]:
    """rodata offset of a string -> source file name it mentions (e.g. in an
    assert message). Keyed by the containing string's start, since that's what
    code references."""
    names = {}
    for m in SOURCE_NAME_RE.finditer(rodata):
        start = rodata.rfind(b"\0", 0, m.start()) + 1
        names[start] = m.group(0).decode("latin-1").replace("\\", "/").split("/")[-1]
    return names


def infer(elf: ELFFile) -> Result:
    text_index = elf.get_section_index(".text")
    symbols = list(elf.get_section_by_name(".symtab").iter_symbols())
    functions = sorted(
        (s["st_value"], s.name)
        for s in symbols
        if s["st_info"]["type"] == "STT_FUNC" and s["st_shndx"] == text_index
    )
    addresses = [a for a, _ in functions]
    globals_in_text = {
        s.name: s["st_value"]
        for s in symbols
        if s["st_info"]["bind"] == "STB_GLOBAL" and s["st_shndx"] == text_index and s.name
    }

    def owner(offset: int) -> int | None:
        i = bisect.bisect_right(addresses, offset) - 1
        return i if i >= 0 else None

    rodata = elf.get_section_by_name(".rodata")
    file_strings = source_names(rodata.data()) if rodata is not None else {}

    reach = list(range(len(functions)))  # furthest function index tied to each
    cross: list[tuple[int, int]] = []
    names_by_function: dict[int, set[str]] = {}
    same = 0

    def tie(a: int, b: int) -> None:
        lo, hi = min(a, b), max(a, b)
        reach[lo] = max(reach[lo], hi)

    for offset, reloc in read_relocs(elf, ".text").items():
        f = owner(offset)
        if f is None:
            continue
        if reloc.section_relative and reloc.addend is not None:
            if reloc.target == ".text":
                g = owner(reloc.addend)
                if g is not None:
                    tie(f, g)
                    same += 1
            elif reloc.target == ".rodata" and reloc.addend in file_strings:
                names_by_function.setdefault(f, set()).add(file_strings[reloc.addend])
        elif not reloc.section_relative and reloc.target in globals_in_text:
            g = owner(globals_in_text[reloc.target])
            if g is not None and g != f:
                cross.append((f, g))

    groups: list[Group] = []
    i = 0
    while i < len(functions):
        end, j = reach[i], i
        while j <= end:
            end = max(end, reach[j])
            j += 1
        group = Group(i, end)
        for k in range(i, end + 1):
            group.names |= names_by_function.get(k, set())
        groups.append(group)
        i = end + 1

    group_of = {}
    for n, g in enumerate(groups):
        for k in range(g.first, g.last + 1):
            group_of[k] = n
    conflicts = [(functions[a][1], functions[b][1]) for a, b in cross if group_of[a] == group_of[b]]
    return Result(functions, groups, same, len(cross), conflicts)


def summarize(name: str, r: Result) -> list[str]:
    multi = [g for g in r.groups if g.last > g.first]
    named = [g for g in r.groups if g.names]
    tied = sum(g.last - g.first + 1 for g in multi)
    lines = [
        f"{name}: {len(r.functions)} functions -> {len(r.groups)} groups "
        f"({len(multi)} with 2+ functions covering {tied}; {len(named)} named)",
        f"  evidence: {r.same_file_links} same-file references, "
        f"{r.cross_file_links} cross-file references, {len(r.conflicts)} conflicts",
    ]
    if r.conflicts:
        lines.append(f"  conflicts e.g. {r.conflicts[:3]}")
    return lines


def listing(r: Result) -> list[str]:
    lines = []
    for g in r.groups:
        start = r.functions[g.first]
        end = r.functions[g.last]
        label = ", ".join(sorted(g.names)) or "-"
        count = g.last - g.first + 1
        lines.append(
            f"  {start[0]:#08x}-{end[0]:#08x} {count:4} fn  {label:24} {start[1]} .. {end[1]}"
        )
    return lines


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument("xff", type=Path, nargs="+")
    parser.add_argument("--list", action="store_true", help="print every group")
    args = parser.parse_args(argv)
    for xff in args.xff:
        elf = ELFFile(io.BytesIO(to_elf(parse(xff.read_bytes()))))
        result = infer(elf)
        print("\n".join(summarize(xff.stem.upper(), result)))
        if args.list:
            print("\n".join(listing(result)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
