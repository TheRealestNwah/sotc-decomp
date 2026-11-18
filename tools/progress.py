"""Refresh the progress table and bars in README.md from the matching C source.

Counts each Game module's functions and the Matched functions among them, then
rewrites the block between the progress markers in README.md. Needs the
generated asm/ (run configure.py first) and the Original Game modules in iso/,
whose symbol tables and relocations define what a function is:

- every function in the module's symbol table (`STT_FUNC` in .text; KERNEL's
  absolute `STT_FUNC` symbols are Loader functions it imports, not its own);
- every Placeholder-named label (`func_XXXXXXXX`, `T_XXXXXXXX`) at an address
  the Original references through a relocation (a call, a function pointer or an
  address load). Labels spimdisasm made where it split a function at a tail
  call aren't referenced, so they don't count;
- any other static the matching C defines, such as a renamed static or one at an
  address spimdisasm left without a function label. The C proves it's a function.

A Matched function is one of those defined in C outside NONMATCHING blocks. SDK
routines listed in config/sdk_routines.txt are identified by signature rather
than decompiled, so they're reported on their own and left out of the Game code
totals, and so is Handwritten asm listed in config/handwritten_asm.txt.

The Loader's Game code functions are the `game` rows of
config/loader_functions.csv, and its Matched functions are those the C in
src/loader/ defines.

Don't run it in a PR that changes src/xff. Every such PR would rewrite the same
README lines, so concurrent PRs conflict and auto-merge stalls. Instead, refresh
the table on an up-to-date main every so often, as its own small PR.

Usage: python tools/progress.py
"""

from __future__ import annotations

import argparse
import bisect
import csv
import re
import sys
from dataclasses import dataclass
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))

README = REPO / "README.md"
SDK_ROUTINES = REPO / "config" / "sdk_routines.txt"
HANDWRITTEN_ASM = REPO / "config" / "handwritten_asm.txt"
START = "<!-- progress:start -->"
END = "<!-- progress:end -->"

MODULES = ("KERNEL", "MANAGER", "GAMECORE")
LOADER_FUNCTIONS_CSV = REPO / "config" / "loader_functions.csv"

STT_FUNC = 2
LABEL_RE = re.compile(r"^\s*(?:glabel|alabel)\s+(\S+)")
ADDRESS_RE = re.compile(r"^\s*/\* [0-9A-F]+ ([0-9A-F]+) [0-9A-F]+ \*/")
PLACEHOLDER_RE = re.compile(r"(?:func|T)_([0-9A-F]{8})")
DEFINITION_RE = re.compile(r"^[^\s#/*}][^;{}()]*?\b([A-Za-z_]\w*)\s*\([^;{}]*\)\s*\{", re.MULTILINE)
STATIC_DEFINITION_RE = re.compile(
    r"^static\s+(?!inline\b)[^;{}()]*?\b([A-Za-z_]\w*)\s*\([^;{}]*\)\s*\{",
    re.MULTILINE,
)
NONMATCHING_BRANCH = {"nonmatching": "matching", "matching": "nonmatching", "other": "other"}


@dataclass(frozen=True)
class Progress:
    """One Game module's counts. Game code excludes the listed SDK routines and
    Handwritten asm."""

    matched: int  # Matched functions in Game code
    total: int  # Game code functions
    sdk: int  # SDK routines identified by signature
    handwritten: int = 0  # Handwritten asm, classified (ADR 0017)


def strip_nonmatching(source: str) -> str:
    """Drop the code that only builds under NONMATCHING (parked attempts)."""
    kept = []
    stack: list[str] = []  # one entry per open #if; "nonmatching" when its branch is parked
    for line in source.splitlines():
        directive = line.strip()
        if directive.startswith("#ifdef NONMATCHING"):
            stack.append("nonmatching")
        elif directive.startswith("#ifndef NONMATCHING"):
            stack.append("matching")
        elif directive.startswith("#if"):
            stack.append("other")
        elif directive.startswith("#else") and stack:
            stack[-1] = NONMATCHING_BRANCH[stack[-1]]
        elif directive.startswith("#endif") and stack:
            stack.pop()
        elif "nonmatching" not in stack and not directive.startswith("#"):
            kept.append(line)
    return "\n".join(kept)


def c_functions(src_dir: Path) -> tuple[set[str], set[str]]:
    """Functions defined in matching C: (all definitions, the static ones)."""
    defined: set[str] = set()
    statics: set[str] = set()
    for c_file in src_dir.glob("*.c"):
        source = strip_nonmatching(c_file.read_text(encoding="latin-1"))
        defined.update(DEFINITION_RE.findall(source))
        # ee-gcc 2.96 emits non-inline static definitions even when unused, so
        # every one is a function the build splices in.
        statics.update(STATIC_DEFINITION_RE.findall(source))
    return defined, statics


def parked_functions(src_dir: Path) -> set[str]:
    """Functions with a Parked attempt: defined only in NONMATCHING code."""
    parked: set[str] = set()
    for c_file in src_dir.glob("*.c"):
        source = c_file.read_text(encoding="latin-1")
        everywhere = set(DEFINITION_RE.findall(source))
        parked |= everywhere - set(DEFINITION_RE.findall(strip_nonmatching(source)))
    return parked


def label_addresses(asm_text: str) -> dict[str, int]:
    """Function labels (glabel and alabel) in a Game module's text.s and their
    asm addresses."""
    labels: dict[str, int] = {}
    pending: list[str] = []
    for line in asm_text.splitlines():
        if m := LABEL_RE.match(line):
            pending.append(m.group(1))
        elif pending and (m := ADDRESS_RE.match(line)):
            for name in pending:
                labels.setdefault(name, int(m.group(1), 16))
            pending = []
    return labels


def text_base(named: dict[str, int], labels: dict[str, int]) -> int:
    """The fixed difference between asm addresses and .text offsets, found from
    the named symbols' labels."""
    bases = {labels[name] - value for name, value in named.items() if name in labels}
    if len(bases) > 1:
        raise ValueError(f"named symbols disagree on the asm .text base: {sorted(bases)}")
    return bases.pop() if bases else 0


def module_functions(named: dict[str, int], labels: dict[str, int], targets: set[int]) -> set[str]:
    """A Game module's functions: its named symbols, plus the Placeholder-named
    labels at addresses the Original references.

    `named` maps symbol names to .text offsets, `labels` asm labels to asm
    addresses and `targets` holds the .text offsets of section-relative
    relocations. Asm addresses are .text offsets plus a fixed base, found from
    the named symbols' labels."""
    base = text_base(named, labels)
    functions = set(named)
    for name, address in labels.items():
        if name not in named and PLACEHOLDER_RE.fullmatch(name) and address - base in targets:
            functions.add(name)
    return functions


def count(
    functions: set[str],
    defined: set[str],
    statics: set[str],
    sdk: set[str],
    handwritten: set[str] = frozenset(),
) -> Progress:
    """Matched and total Game code functions, with SDK routines and Handwritten
    asm counted apart. Statics the C defines that the module scan didn't find
    count as functions too."""
    everything = functions | statics
    matched = (defined & functions) | statics
    game = everything - sdk - handwritten
    return Progress(
        matched=len(matched & game),
        total=len(game),
        sdk=len(everything & sdk),
        handwritten=len(everything & handwritten),
    )


def read_sdk_routines(path: Path) -> dict[str, set[str]]:
    """Module name -> function names, from config/sdk_routines.txt or any list
    in its layout (module and name first), such as config/handwritten_asm.txt."""
    routines: dict[str, set[str]] = {}
    if not path.exists():
        return routines
    for line in path.read_text(encoding="utf-8").splitlines():
        line = line.split("#", 1)[0].strip()
        if line:
            module, name = line.split()[:2]
            routines.setdefault(module, set()).add(name)
    return routines


def loader_game_functions(path: Path) -> set[str]:
    """Names of the Loader's Game code functions, from config/loader_functions.csv."""
    with path.open(encoding="utf-8", newline="") as f:
        return {row["name"] for row in csv.DictReader(f) if row["class"] == "game"}


def loader_progress(path: Path, src_dir: Path, handwritten: set[str] = frozenset()) -> Progress:
    """Matched and total Game code functions in the Loader. Its SDK routines
    aren't in the Game code list, so none are counted; Handwritten asm is
    taken out of it."""
    listed = loader_game_functions(path)
    functions = listed - handwritten
    defined, _ = c_functions(src_dir)
    return Progress(
        matched=len(defined & functions),
        total=len(functions),
        sdk=0,
        handwritten=len(listed & handwritten),
    )


def read_module(xff: Path) -> tuple[dict[str, int], set[int]]:
    """A Game module's named .text functions (name -> offset) and the .text
    offsets its section-relative relocations point at."""
    from tools.functions import open_module, read_relocs
    from tools.xff2 import parse

    module = parse(xff.read_bytes())
    text = module.index_of(".text")
    named = {}
    for i in range(1, module.num_symbols):
        _, value, _, info, _, shndx = module.symbol(i)
        if info & 0xF == STT_FUNC and shndx == text:
            named[module.symbol_name(i)] = value
    elf = open_module(xff.stem, xff.parent)
    targets = set()
    for section in elf.iter_sections():
        if section.name.startswith(".rel.") or section.name.startswith(".rela."):
            continue
        for reloc in read_relocs(elf, section.name).values():
            if reloc.section_relative and reloc.target == ".text" and reloc.addend is not None:
                targets.add(reloc.addend)
    return named, targets


def render_table(progress: dict[str, Progress], loader: Progress) -> str:
    """Markdown progress table of Game code in the Loader and each Game module."""

    def row(stage: str, done: str, total: str, percent: int) -> str:
        return f"| {stage} | {done} | {total} | {percent}% |"

    def percent(done: int, total: int) -> int:
        return round(100 * done / total) if total else 0

    lines = [
        "| Stage | Done | Total | Progress |",
        "| --- | ---: | ---: | ---: |",
        row("Rebuild byte-for-byte from assembly", "4", "4 files", 100),
        row(
            "Loader `SCUS_974.72` Game code as matching C",
            f"{loader.matched:,}",
            f"{loader.total:,} functions",
            percent(loader.matched, loader.total),
        ),
    ]
    for module, p in progress.items():
        lines.append(
            row(
                f"`{module}.XFF` Game code as matching C",
                f"{p.matched:,}",
                f"{p.total:,} functions",
                percent(p.matched, p.total),
            )
        )
    done = sum(p.matched for p in progress.values())
    total = sum(p.total for p in progress.values())
    lines.append(
        row(
            "All three Game modules' Game code as matching C",
            f"{done:,}",
            f"{total:,} functions",
            percent(done, total),
        )
    )
    lines.append(row("Native PC port", "not started", "-", 0))
    return "\n".join(lines)


def render_sdk(progress: dict[str, Progress], loader: Progress | None = None) -> str:
    """One line on the SDK routines (and Handwritten asm) left out of the table."""
    parts = ", ".join(f"{module} {p.sdk:,}" for module, p in progress.items())
    text = f"SDK routines identified by signature and left out of the totals: {parts}."
    handwritten = {m: p.handwritten for m, p in progress.items()}
    if loader is not None:
        handwritten = {"Loader": loader.handwritten, **handwritten}
    if any(handwritten.values()):
        listed = ", ".join(f"{m} {n:,}" for m, n in handwritten.items() if n)
        text += f" Handwritten asm, classified and left out too: {listed}."
    return text


def render_bars(progress: dict[str, Progress], loader: Progress) -> str:
    """Text progress bars using the same function totals as the status table."""
    done = sum(p.matched for p in progress.values())
    total = sum(p.total for p in progress.values())
    module_percent = round(100 * done / total) if total else 0
    loader_percent = round(100 * loader.matched / loader.total) if loader.total else 0

    def row(label: str, percent: int, note: str = "") -> str:
        filled = round(percent * 20 / 100)
        bar = "█" * filled + "░" * (20 - filled)
        return f"{label:<24}[{bar}] {percent:>2}%{note}"

    return "\n".join(
        [
            "Overall, a playable build needs all three bars full.",
            "",
            "```",
            row("Matching decompilation", module_percent, "   (Game modules)"),
            row("Loader as matching C", loader_percent),
            row("Native PC port", 0),
            "```",
        ]
    )


def block(table: str, bars: str = "", sdk: str = "") -> str:
    parts = [
        START,
        table,
        "",
        "Generated by `tools/progress.py` from the C in `src/xff/` and",
        "`src/loader/`. Done counts Matched functions. Totals count each Game",
        "module's functions: those in its symbol table, plus the static",
        "functions the Original references that have only Placeholder names.",
        "SDK routines listed in",
        "`config/sdk_routines.txt` are identified rather than decompiled, so",
        "they're left out, and so are the Loader's SDK routines",
        "(`config/loader_functions.csv`). Refreshed periodically on main, so it",
        "can lag behind the latest merges.",
    ]
    if sdk:
        parts.extend(["", sdk])
    if bars:
        parts.extend(["", bars])
    parts.append(END)
    return "\n".join(parts)


def update_readme(readme: str, table: str, bars: str = "", sdk: str = "") -> str:
    """Replace the marked block with a fresh table and optional progress bars."""
    pattern = re.compile(re.escape(START) + r".*?" + re.escape(END), re.DOTALL)
    if not pattern.search(readme):
        raise ValueError(f"README.md has no {START} ... {END} block")
    return pattern.sub(lambda _: block(table, bars, sdk), readme, count=1)


NONMATCHING_RE = re.compile(r"^nonmatching (\w+), (0x[0-9A-Fa-f]+)", re.MULTILINE)


def unmatched_functions(
    asm_text: str,
    labels: dict[str, int],
    functions: set[str],
    defined: set[str],
    statics: set[str],
    sdk: set[str],
) -> list[tuple[int, str]]:
    """The real (referenced or named) Game code functions the C doesn't Match yet,
    as (size in bytes, name) sorted smallest first. Sizes come from the asm's
    `nonmatching` lines; unreferenced tail labels are not in `functions`."""
    sizes = {m.group(1): int(m.group(2), 16) for m in NONMATCHING_RE.finditer(asm_text)}
    ordered = sorted(set(labels.values()))
    for name in functions:
        if name not in sizes and name in labels:
            later = [a for a in ordered if a > labels[name]]
            sizes[name] = (later[0] - labels[name]) if later else 0
    todo = (functions - defined - statics) - sdk
    return sorted((sizes.get(name, 0), name) for name in todo)


@dataclass
class GroupRow:
    """One Source group with unmatched functions: its label, start (.text offset),
    Game code function count and the unmatched ones as (size, name, parked)."""

    label: str
    start: int
    total: int
    unmatched: list[tuple[int, str, bool]]


def group_rows(
    groups: list[tuple[int, str]],
    offsets: dict[str, int],
    game: set[str],
    unmatched: list[tuple[int, str]],
    parked: set[str],
) -> tuple[list[GroupRow], int]:
    """Sort a module's Game code into Source groups, in work order: fewest
    unmatched functions first, then by address. `groups` holds each group's
    (start offset, label) in address order; a function belongs to the last group
    starting at or before its offset. Returns the groups with unmatched
    functions and the number of groups that are fully matched."""
    starts = [start for start, _ in groups]
    rows = [GroupRow(label, start, 0, []) for start, label in groups]

    def row(name: str) -> GroupRow | None:
        i = bisect.bisect_right(starts, offsets.get(name, -1)) - 1
        return rows[i] if i >= 0 and name in offsets else None

    for name in game:
        if r := row(name):
            r.total += 1
    for size, name in unmatched:
        if r := row(name):
            r.unmatched.append((size, name, name in parked))
    for r in rows:
        # Parked attempts first, then fresh functions, smallest first.
        r.unmatched.sort(key=lambda u: (not u[2], u[0], u[1]))
    todo = sorted((r for r in rows if r.unmatched), key=lambda r: (len(r.unmatched), r.start))
    done = sum(1 for r in rows if r.total and not r.unmatched)
    return todo, done


def render_unmatched(
    rows: dict[str, list[tuple[int, str]]],
    groups: dict[str, tuple[list[GroupRow], int]] | None = None,
) -> str:
    """Markdown list of unmatched real functions per module, sorted into Source
    groups in work order when `groups` is given."""
    out = [
        "# Unmatched Game code functions",
        "",
        "Generated by `python tools/progress.py --unmatched docs/unmatched.md`.",
        "Only real functions are listed: named symbols and Placeholder labels the",
        "Original references. Tails of larger functions that spimdisasm split off are",
        "left out. Parked drafts (`#ifdef NONMATCHING`) still count as unmatched.",
        "Size is in bytes, from the asm; 0 means unknown.",
    ]
    if groups is not None:
        out += [
            "",
            "Functions are sorted into Source groups (`tools/xff_tus.py`) in work order:",
            "the groups with the fewest unmatched functions first. Within a group,",
            "Parked attempts (marked *parked*) come first, then fresh functions,",
            "smallest first. A group is named after its Original source file when a",
            "string gives one, otherwise after its first and last functions.",
        ]
    out.append("")
    for module, items in rows.items():
        out += [f"## {module} ({len(items)})", ""]
        if groups is None or module not in groups:
            out += [f"- `{name}` {size}" for size, name in items]
            out.append("")
            continue
        todo, done = groups[module]
        out += [f"{len(todo)} Source groups to go, {done} fully matched.", ""]
        for g in todo:
            out += [f"### {g.label}: {len(g.unmatched)} of {g.total} unmatched", ""]
            out += [
                f"- `{name}` {size}" + (" *parked*" if parked else "")
                for size, name, parked in g.unmatched
            ]
            out.append("")
    return "\n".join(out)


def source_groups(xff_path: Path) -> list[tuple[int, str]]:
    """(start .text offset, label) of each Source group in a Game module."""
    from tools.functions import open_module
    from tools.xff_tus import infer

    result = infer(open_module(xff_path.stem, xff_path.parent))
    out = []
    for g in result.groups:
        first, last = result.functions[g.first], result.functions[g.last]
        if g.names:
            label = ", ".join(sorted(g.names))
        elif g.first == g.last:
            label = first[1]
        else:
            label = f"{first[1]} .. {last[1]}"
        out.append((first[0], label))
    return out


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument(
        "--asm-dir",
        type=Path,
        default=REPO / "asm" / "xff",
        help="generated Game module assembly (default: asm/xff in this checkout)",
    )
    parser.add_argument(
        "--iso-dir",
        type=Path,
        default=REPO / "iso",
        help="the Original Game modules (default: iso in this checkout)",
    )
    parser.add_argument(
        "--unmatched",
        type=Path,
        metavar="FILE",
        help="write the list of unmatched real functions to FILE (Markdown) and exit",
    )
    args = parser.parse_args(argv)
    sdk = read_sdk_routines(SDK_ROUTINES)
    handwritten = read_sdk_routines(HANDWRITTEN_ASM)
    progress = {}
    unmatched = {}
    groups: dict[str, tuple[list[GroupRow], int]] = {}
    for module in MODULES:
        asm_path = args.asm_dir / module / "text.s"
        xff_path = args.iso_dir / f"{module}.XFF"
        for path in (asm_path, xff_path):
            if not path.exists():
                print(f"missing {path}; run `python configure.py` first", file=sys.stderr)
                return 1
        named, targets = read_module(xff_path)
        labels = label_addresses(asm_path.read_text(encoding="latin-1"))
        defined, statics = c_functions(REPO / "src" / "xff" / module)
        if args.unmatched:
            functions = module_functions(named, labels, targets)
            module_sdk = sdk.get(module, set()) | handwritten.get(module, set())
            unmatched[module] = unmatched_functions(
                asm_path.read_text(encoding="latin-1"),
                labels,
                functions,
                defined,
                statics,
                module_sdk,
            )
            base = text_base(named, labels)
            offsets = {name: labels[name] - base for name in functions if name in labels}
            groups[module] = group_rows(
                source_groups(xff_path),
                offsets,
                functions - module_sdk,
                unmatched[module],
                parked_functions(REPO / "src" / "xff" / module),
            )
            continue
        progress[module] = count(
            module_functions(named, labels, targets),
            defined,
            statics,
            sdk.get(module, set()),
            handwritten.get(module, set()),
        )
    if args.unmatched:
        args.unmatched.write_text(render_unmatched(unmatched, groups), encoding="utf-8")
        print(f"wrote {args.unmatched}")
        return 0
    loader = loader_progress(
        LOADER_FUNCTIONS_CSV, REPO / "src" / "loader", handwritten.get("LOADER", set())
    )
    table = render_table(progress, loader)
    README.write_text(
        update_readme(
            README.read_text(encoding="utf-8"),
            table,
            render_bars(progress, loader),
            render_sdk(progress, loader),
        ),
        encoding="utf-8",
    )
    print(table)
    print(render_sdk(progress, loader))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
