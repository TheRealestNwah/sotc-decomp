"""Prepare ee-gcc assembly for the Original assembler using only the standard library.

Kept importable on Windows and executable inside WSL so both compile paths
apply exactly the same transformations.
"""

from __future__ import annotations

import argparse
import re
from pathlib import Path


def fix_moves(asm: Path) -> None:
    """The original assembler expanded `move` to `daddu rd, rs, $zero` (64-bit
    EABI); modern binutils picks a different encoding."""
    text = asm.read_text(encoding="latin-1")
    text = re.sub(r"\bmove\t(\$\w+),(\$\w+)", r"daddu\t\1,\2,$0", text)
    asm.write_text(text, encoding="latin-1")


def volatile_barriers(asm: Path) -> None:
    """gcc brackets each volatile memory access with `.set volatile` /
    `.set novolatile`, written as comments in GAS mode. The original build
    never moved a volatile access into a branch delay slot, so turn each
    marker into an empty `.set noreorder` / `.set reorder` pair: any `.set`
    stops ee-as from reordering across it (docs/findings.md)."""
    text = asm.read_text(encoding="latin-1")
    text = re.sub(
        r"^(\s*)#\.set\s+(?:no)?volatile\s*$",
        r"\1.set\tnoreorder\n\1.set\treorder",
        text,
        flags=re.M,
    )
    asm.write_text(text, encoding="latin-1")


def indexed_la_barriers(asm: Path) -> None:
    """gcc writes an indexed address as the macro `la $r,sym($b)`, which ee-as
    expands to `lui $at` / `addiu $at` / `addu $r,$at,$b`. Our ee-as moves that
    final `addu` into a following jump's delay slot; the original build never
    did (no `addu ...,$at,...` sits in a delay slot in any module), so put an
    empty `.set noreorder` / `.set reorder` pair after each one
    (docs/findings.md)."""
    text = asm.read_text(encoding="latin-1")
    text = re.sub(
        r"^(\s*)(la\s+\$\w+,[^\s()]+\(\$\w+\).*)$",
        r"\1\2\n\1.set\tnoreorder\n\1.set\treorder",
        text,
        flags=re.M,
    )
    asm.write_text(text, encoding="latin-1")


INDEXED_LOAD_RE = re.compile(
    r"^(\s*)(lw|lhu)\s+(\$\w+),((?![-+]?\d)[^\s()%]+)\((\$\w+)\)[ \t]*(#.*)?$", flags=re.M
)


def expand_indexed_loads(asm: Path) -> None:
    """gcc writes an indexed load from a constant-base array as the macro
    `lw $r,sym($b)` or `lhu $r,sym($b)`. Our ee-as sometimes encodes the
    `lui` of its expansion with the load opcode (issues #2343 and #2265),
    so write out the expansion the assembler would make: `lui` / `addu` /
    load with `%lo`, through $r or through $at when $r is also the base. Only for -G0
    code, where the assembler never picks a $gp-relative form."""
    text = asm.read_text(encoding="latin-1")

    def expand(m: re.Match[str]) -> str:
        indent, opcode, reg, sym, base = m.group(1, 2, 3, 4, 5)
        tmp = "$at" if reg == base else reg
        return (
            f"{indent}lui\t{tmp},%hi({sym})\n"
            f"{indent}addu\t{tmp},{tmp},{base}\n"
            f"{indent}{opcode}\t{reg},%lo({sym})({tmp})"
        )

    asm.write_text(INDEXED_LOAD_RE.sub(expand, text), encoding="latin-1")


JUMP_RE = re.compile(r"^\s*(?:j|jal|jalr|jr|b|bal|b(?:eq|ne|lt|le|gt|ge)\w*|bc[01][tf]l?)\s")


def jump_barriers(asm: Path) -> None:
    """gcc fills the delay slots it can inside its own `.set noreorder`
    blocks and leaves every other jump or branch to the assembler. Our
    ee-as then moves an earlier instruction into the slot; the original
    assembler never did (docs/findings.md). So put an empty
    `.set noreorder` / `.set reorder` pair before each jump or branch that
    gcc emits in reorder mode, which makes ee-as leave the slot as a `nop`.
    This covers the volatile and indexed-`la` cases above as well."""
    lines = asm.read_text(encoding="latin-1").split("\n")
    out = []
    reorder = True
    for line in lines:
        stripped = line.strip()
        if stripped.startswith(".set"):
            if "noreorder" in stripped:
                reorder = False
            elif stripped.split()[-1] == "reorder":
                reorder = True
        elif reorder and JUMP_RE.match(line):
            out.append("\t.set\tnoreorder")
            out.append("\t.set\treorder")
        out.append(line)
    asm.write_text("\n".join(out), encoding="latin-1")


def prepare_asm(asm: Path, gp: int = 0) -> None:
    volatile_barriers(asm)
    indexed_la_barriers(asm)
    if gp == 0:
        expand_indexed_loads(asm)
    jump_barriers(asm)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("assembly", type=Path)
    parser.add_argument("--gp", type=int, default=0)
    args = parser.parse_args(argv)
    prepare_asm(args.assembly, args.gp)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
