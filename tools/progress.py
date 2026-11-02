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
totals.

Don't run it in a PR that changes src/xff. Every such PR would rewrite the same
README lines, so concurrent PRs conflict and auto-merge stalls. Instead, refresh
the table on an up-to-date main every so often, as its own small PR.

Usage: python tools/progress.py
"""

from __future__ import annotations

import argparse
import io
import re
import sys
from dataclasses import dataclass
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))

README = REPO / "README.md"
SDK_ROUTINES = REPO / "config" / "sdk_routines.txt"
START = "<!-- progress:start -->"
END = "<!-- progress:end -->"

MODULES = ("KERNEL", "MANAGER", "GAMECORE")
# splat's function count for the Loader ELF, which still exists only as assembly.
LOADER_FUNCTIONS = 1038
LOADER_MATCHED = 0

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
    """One Game module's counts. Game code excludes the listed SDK routines."""

    matched: int  # Matched functions in Game code
    total: int  # Game code functions
    sdk: int  # SDK routines identified by signature


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


def module_functions(named: dict[str, int], labels: dict[str, int], targets: set[int]) -> set[str]:
    """A Game module's functions: its named symbols, plus the Placeholder-named
    labels at addresses the Original references.

    `named` maps symbol names to .text offsets, `labels` asm labels to asm
    addresses and `targets` holds the .text offsets of section-relative
    relocations. Asm addresses are .text offsets plus a fixed base, found from
    the named symbols' labels."""
    bases = {labels[name] - value for name, value in named.items() if name in labels}
    if len(bases) > 1:
        raise ValueError(f"named symbols disagree on the asm .text base: {sorted(bases)}")
    base = bases.pop() if bases else 0
    functions = set(named)
    for name, address in labels.items():
        if name not in named and PLACEHOLDER_RE.fullmatch(name) and address - base in targets:
            functions.add(name)
    return functions


def count(functions: set[str], defined: set[str], statics: set[str], sdk: set[str]) -> Progress:
    """Matched and total Game code functions, with SDK routines counted apart.
    Statics the C defines that the module scan didn't find count as functions too."""
    everything = functions | statics
    matched = (defined & functions) | statics
    game = everything - sdk
    return Progress(matched=len(matched & game), total=len(game), sdk=len(everything & sdk))


def read_sdk_routines(path: Path) -> dict[str, set[str]]:
    """Module name -> SDK routine names, from config/sdk_routines.txt."""
    routines: dict[str, set[str]] = {}
    if not path.exists():
        return routines
    for line in path.read_text(encoding="utf-8").splitlines():
        line = line.split("#", 1)[0].strip()
        if line:
            module, name = line.split()[:2]
            routines.setdefault(module, set()).add(name)
    return routines


def read_module(xff: Path) -> tuple[dict[str, int], set[int]]:
    """A Game module's named .text functions (name -> offset) and the .text
    offsets its section-relative relocations point at."""
    from elftools.elf.elffile import ELFFile

    from tools.xff2 import parse, to_elf
    from tools.xff_split import read_relocs

    module = parse(xff.read_bytes())
    text = module.index_of(".text")
    named = {}
    for i in range(1, module.num_symbols):
        _, value, _, info, _, shndx = module.symbol(i)
        if info & 0xF == STT_FUNC and shndx == text:
            named[module.symbol_name(i)] = value
    elf = ELFFile(io.BytesIO(to_elf(module)))
    targets = set()
    for section in elf.iter_sections():
        if section.name.startswith(".rel.") or section.name.startswith(".rela."):
            continue
        for reloc in read_relocs(elf, section.name).values():
            if reloc.section_relative and reloc.target == ".text" and reloc.addend is not None:
                targets.add(reloc.addend)
    return named, targets


def render_table(progress: dict[str, Progress]) -> str:
    """Markdown progress table of Game code per Game module."""

    def row(stage: str, done: str, total: str, percent: int) -> str:
        return f"| {stage} | {done} | {total} | {percent}% |"

    def percent(done: int, total: int) -> int:
        return round(100 * done / total) if total else 0

    lines = [
        "| Stage | Done | Total | Progress |",
        "| --- | ---: | ---: | ---: |",
        row("Rebuild byte-for-byte from assembly", "4", "4 files", 100),
        row(
            "Loader `SCUS_974.72` as matching C",
            f"{LOADER_MATCHED:,}",
            f"{LOADER_FUNCTIONS:,} functions",
            percent(LOADER_MATCHED, LOADER_FUNCTIONS),
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


def render_sdk(progress: dict[str, Progress]) -> str:
    """One line on the SDK routines left out of the table."""
    parts = ", ".join(f"{module} {p.sdk:,}" for module, p in progress.items())
    return f"SDK routines identified by signature and left out of the totals: {parts}."


def render_bars(progress: dict[str, Progress]) -> str:
    """Text progress bars using the same function totals as the status table."""
    done = sum(p.matched for p in progress.values())
    total = sum(p.total for p in progress.values())
    module_percent = round(100 * done / total) if total else 0
    loader_percent = round(100 * LOADER_MATCHED / LOADER_FUNCTIONS)

    def row(label: str, percent: int, note: str = "") -> str:
        filled = round(percent * 20 / 100)
        bar = "█" * filled + "░" * (20 - filled)
        return f"{label:<24}[{bar}] {percent:>2}%{note}"

    return "\n".join(
        [
            "Overall, a playable build needs all three bars full. The Loader's total still "
            "includes SDK routines that haven't been sorted out yet.",
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
        "Generated by `tools/progress.py` from the C in `src/xff/`. Done counts",
        "Matched functions. Totals count each Game module's functions: those in",
        "its symbol table, plus the static functions the Original references",
        "that have only Placeholder names. SDK routines listed in",
        "`config/sdk_routines.txt` are identified rather than decompiled, so",
        "they're left out. Refreshed periodically on main, so it can lag behind",
        "the latest merges.",
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
    args = parser.parse_args(argv)
    sdk = read_sdk_routines(SDK_ROUTINES)
    progress = {}
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
        progress[module] = count(
            module_functions(named, labels, targets), defined, statics, sdk.get(module, set())
        )
    README.write_text(
        update_readme(
            README.read_text(encoding="utf-8"),
            render_table(progress),
            render_bars(progress),
            render_sdk(progress),
        ),
        encoding="utf-8",
    )
    print(render_table(progress))
    print(render_sdk(progress))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
