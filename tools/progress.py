"""Refresh the progress table and bars in README.md from the matching C source.

Counts the functions compiled from src/xff/<MODULE>/*.c that the build splices
back into each module, and rewrites the block between the progress markers in
README.md. Needs the generated asm/ (run configure.py first); it reads no disc
files.

Don't run it in a PR that changes src/xff. Every such PR would rewrite the same
README lines, so concurrent PRs conflict and auto-merge stalls. Instead, refresh
the table on an up-to-date main every so often, as its own small PR.

Usage: python tools/progress.py
"""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
README = REPO / "README.md"
START = "<!-- progress:start -->"
END = "<!-- progress:end -->"

# Function counts from the original binaries: splat's count for the loader
# ELF, and the STT_FUNC symbol counts for the XFF modules (docs/findings.md).
LOADER_FUNCTIONS = 1038
MODULE_FUNCTIONS = {"KERNEL": 940, "MANAGER": 2277, "GAMECORE": 2755}
# The loader still exists only as assembly.
LOADER_MATCHED = 0

GLABEL_RE = re.compile(r"^(?:glabel|alabel) (\S+)", re.MULTILINE)
DEFINITION_RE = re.compile(r"^[^\s#/*}][^;{}()]*?\b([A-Za-z_]\w*)\s*\([^;{}]*\)\s*\{", re.MULTILINE)
STATIC_DEFINITION_RE = re.compile(
    r"^static\s+(?!inline\b)[^;{}()]*?\b([A-Za-z_]\w*)\s*\([^;{}]*\)\s*\{",
    re.MULTILINE,
)
NONMATCHING_BRANCH = {"nonmatching": "matching", "matching": "nonmatching", "other": "other"}


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


def compiled_functions(src_dir: Path, asm_text: str) -> set[str]:
    """Names of functions defined in matching C that exist in the module's asm."""
    asm_names = set(GLABEL_RE.findall(asm_text))
    defined: set[str] = set()
    statics: set[str] = set()
    for c_file in src_dir.glob("*.c"):
        source = strip_nonmatching(c_file.read_text(encoding="latin-1"))
        defined.update(DEFINITION_RE.findall(source))
        # Recovered static names can differ from generated address labels.
        # ee-gcc 2.96 emits non-inline static definitions even when unused.
        statics.update(STATIC_DEFINITION_RE.findall(source))
    return (defined & asm_names) | statics


def render_table(matched: dict[str, int]) -> str:
    """Markdown progress table. `matched` maps module name to compiled count."""

    def row(stage: str, done: str, total: str, percent: int) -> str:
        return f"| {stage} | {done} | {total} | {percent}% |"

    lines = [
        "| Stage | Done | Total | Progress |",
        "| --- | ---: | ---: | ---: |",
        row("Rebuild byte-for-byte from assembly", "4", "4 files", 100),
    ]
    total_done = 0
    total_all = 0
    loader_percent = round(100 * LOADER_MATCHED / LOADER_FUNCTIONS)
    lines.append(
        row(
            "Loader `SCUS_974.72` as matching C",
            f"{LOADER_MATCHED:,}",
            f"{LOADER_FUNCTIONS:,} functions",
            loader_percent,
        )
    )
    for module, total in MODULE_FUNCTIONS.items():
        done = matched[module]
        total_done += done
        total_all += total
        lines.append(
            row(
                f"`{module}.XFF` as matching C",
                f"{done:,}",
                f"{total:,} functions",
                round(100 * done / total),
            )
        )
    lines.append(
        row(
            "All three `.XFF` modules as matching C",
            f"{total_done:,}",
            f"{total_all:,} functions",
            round(100 * total_done / total_all),
        )
    )
    lines.append(row("Native PC port", "not started", "-", 0))
    return "\n".join(lines)


def render_bars(matched: dict[str, int]) -> str:
    """Text progress bars using the same function totals as the status table."""
    module_percent = round(100 * sum(matched.values()) / sum(MODULE_FUNCTIONS.values()))
    loader_percent = round(100 * LOADER_MATCHED / LOADER_FUNCTIONS)

    def row(label: str, percent: int, note: str = "") -> str:
        filled = round(percent * 20 / 100)
        bar = "█" * filled + "░" * (20 - filled)
        return f"{label:<24}[{bar}] {percent:>2}%{note}"

    return "\n".join(
        [
            "Overall, a playable build needs all three bars full. The percentages are a rough "
            "guide, since the totals include SDK routines still to be identified.",
            "",
            "```",
            row("Matching decompilation", module_percent, "   (XFF modules)"),
            row("Loader as matching C", loader_percent),
            row("Native PC port", 0),
            "```",
        ]
    )


def block(table: str, bars: str = "") -> str:
    parts = [
        START,
        table,
        "",
        "Generated by `tools/progress.py` from the C in `src/xff/`. Counts are",
        "functions the build splices in and verifies. Totals are the original",
        "symbol counts, which include SDK routines to be identified rather than",
        "decompiled, so the percentages are a rough guide. Refreshed",
        "periodically on main, so it can lag behind the latest merges.",
    ]
    if bars:
        parts.extend(["", bars])
    parts.append(END)
    return "\n".join(parts)


def update_readme(readme: str, table: str, bars: str = "") -> str:
    """Replace the marked block with a fresh table and optional progress bars."""
    pattern = re.compile(re.escape(START) + r".*?" + re.escape(END), re.DOTALL)
    if not pattern.search(readme):
        raise ValueError(f"README.md has no {START} ... {END} block")
    return pattern.sub(lambda _: block(table, bars), readme, count=1)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument(
        "--asm-dir",
        type=Path,
        default=REPO / "asm" / "xff",
        help="generated XFF assembly (default: asm/xff in this checkout)",
    )
    args = parser.parse_args(argv)
    matched = {}
    for module in MODULE_FUNCTIONS:
        asm_path = args.asm_dir / module / "text.s"
        if not asm_path.exists():
            print(f"missing {asm_path}; run `python configure.py` first", file=sys.stderr)
            return 1
        asm_text = asm_path.read_text(encoding="latin-1")
        matched[module] = len(compiled_functions(REPO / "src" / "xff" / module, asm_text))
    README.write_text(
        update_readme(
            README.read_text(encoding="utf-8"), render_table(matched), render_bars(matched)
        ),
        encoding="utf-8",
    )
    print(render_table(matched))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
