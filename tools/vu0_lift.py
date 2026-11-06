#!/usr/bin/env python3
"""Lift the VU0 (COP2) runs of an Original function into C inline-asm drafts.

m2c cannot read COP2 instructions: it prints one `M2C_ERROR(unknown
instruction ...)` per line. The Original compiler took the same instructions
from `__asm__` blocks, so the quickest route to a Matched function is to
keep each run of consecutive VU0 instructions together as one volatile asm
statement and write the scalar code around it in C.

    python tools/vu0_lift.py <function> [--module MANAGER] [--through NAME]

prints, for each run, an `__asm__ __volatile__` statement whose general
registers are bound to placeholder C variables named after the Original
register (`r_s1` for `$s1`). The placeholders are what the author still has to
map onto real C values; the VU0 text itself is final. A run that ends in
`qmfc2.ni` or `cfc2` followed by `mtc1` becomes a float output ("=f").
Registers `$sp`/`$zero` are not bound: `$sp` offsets stay literal in the asm
text and must be turned into a local buffer by hand.

Conventions (verified against the matched files in src/xff/*/):
- VU0 registers are written without `$` (`vf5`, `vf7y`, `Q`, `ACC`/`ACCz`);
- `$v0` as a destination of qmfc2/cfc2 is written `$2`;
- inputs are `"r"`, memory effects are declared with `"memory"`.
"""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

COP2_RE = re.compile(
    r"^(?:v[a-z0-9]+(?:\.[xyzw]+)?|lqc2|sqc2|qmfc2(?:\.ni|\.i)?|qmtc2(?:\.ni|\.i)?"
    r"|cfc2(?:\.ni|\.i)?|ctc2(?:\.ni|\.i)?|vwaitq|vcallms|vcallmsr)$"
)
LINE_RE = re.compile(
    r"^\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s*\*/\s+(\S+)\s*(.*?)\s*$"
)
GPR_RE = re.compile(r"\$[a-z0-9]+")
GPR_NAMES = {
    "$zero": 0, "$at": 1, "$v0": 2, "$v1": 3, "$a0": 4, "$a1": 5, "$a2": 6, "$a3": 7,
    "$t0": 8, "$t1": 9, "$t2": 10, "$t3": 11, "$t4": 12, "$t5": 13, "$t6": 14, "$t7": 15,
    "$s0": 16, "$s1": 17, "$s2": 18, "$s3": 19, "$s4": 20, "$s5": 21, "$s6": 22, "$s7": 23,
    "$t8": 24, "$t9": 25, "$k0": 26, "$k1": 27, "$gp": 28, "$sp": 29, "$fp": 30, "$ra": 31,
}  # fmt: skip


def read_function(text: str, name: str) -> list[tuple[int, str, str]]:
    """(address, mnemonic, operands) for every instruction of `glabel name`."""
    out: list[tuple[int, str, str]] = []
    inside = False
    for line in text.splitlines():
        if re.match(rf"\s*[ga]label\s+{re.escape(name)}\b", line):
            inside = True
            continue
        if inside and re.match(rf"\s*endlabel\s+{re.escape(name)}\b", line):
            break
        if not inside:
            continue
        m = LINE_RE.match(line)
        if m:
            out.append((int(m.group(1), 16), m.group(2), m.group(3)))
    return out


def is_cop2(mnemonic: str) -> bool:
    return bool(COP2_RE.match(mnemonic))


def split_runs(instrs: list[tuple[int, str, str]]) -> list[list[tuple[int, str, str]]]:
    runs: list[list[tuple[int, str, str]]] = []
    for item in instrs:
        if is_cop2(item[1]):
            if runs and runs[-1][-1][0] + 4 == item[0]:
                runs[-1].append(item)
            else:
                runs.append([item])
    return runs


def fmt_vu_operand(op: str) -> str:
    return op.replace("$", "").replace("$ACC", "ACC")


def lift_run(run: list[tuple[int, str, str]], after: tuple[int, str, str] | None) -> str:
    """One asm statement for a run; `after` is the instruction following it."""
    inputs: list[str] = []  # general registers read (base addresses, qmtc2 sources)
    outputs: list[str] = []  # general registers written by qmfc2/cfc2
    lines: list[str] = []
    clobbers = {"memory"}
    float_reg = None  # (gpr, fpr) when qmfc2/cfc2 is followed by mtc1
    for _, mnem, ops in run:
        args = [a.strip() for a in re.split(r",(?![^()]*\))", ops)] if ops else []
        rendered = []
        for arg in args:
            m = re.fullmatch(r"(-?0x[0-9A-Fa-f]+|-?\d+)?\((\$\w+)\)", arg)
            if m:  # memory operand off a general register ($sp becomes a local buffer)
                reg = m.group(2)
                if reg not in inputs:
                    inputs.append(reg)
                rendered.append(f"{m.group(1) or '0x0'}(@{reg[1:]}@)")
            elif mnem.startswith(("qmfc2", "cfc2")) and arg == args[0] and arg in GPR_NAMES:
                nxt = after[2].split(",") if after and after[1] == "mtc1" else None
                if nxt and nxt[0].strip() == arg:
                    float_reg = (arg, nxt[1].strip())
                    clobbers.add(f"${GPR_NAMES[arg]}")
                    rendered.append(f"${GPR_NAMES[arg]}")
                else:
                    outputs.append(arg)
                    rendered.append(f"@{arg[1:]}@")
            elif mnem.startswith(("qmtc2", "ctc2")) and arg in GPR_NAMES:
                if arg not in inputs:
                    inputs.append(arg)
                rendered.append(f"@{arg[1:]}@")
            else:
                rendered.append(fmt_vu_operand(arg))
        lines.append(f"{mnem} {', '.join(rendered)}" if rendered else mnem)
    if float_reg:
        lines.append(f"mtc1 ${GPR_NAMES[float_reg[0]]}, @f@")
    # Operand numbers: the float output (if any), written GPRs, then inputs.
    order: list[str] = (["@f@"] if float_reg else []) + [f"@{r[1:]}@" for r in outputs]
    order += [f"@{r[1:]}@" for r in inputs]
    body = []
    for line in lines:
        for i, key in enumerate(order):
            line = line.replace(key, f"%{i}")
        body.append(line)
    sep = '\\n"\n' + " " * 25 + '"'
    asm = sep.join(body)
    out_parts = []
    if float_reg:
        out_parts.append(f'"=f"(f_{float_reg[1][1:]})')
    out_parts += [f'"=r"(r_{r[1:]})' for r in outputs]
    in_parts = [("&sp_buf" if r == "$sp" else f"r_{r[1:]}") for r in inputs]
    in_list = ", ".join(f'"r"({p})' for p in in_parts)
    clob = ", ".join(f'"{c}"' for c in sorted(clobbers))
    start, end = run[0][0], run[-1][0]
    return (
        f"/* VU0 run {start:#x}-{end:#x} ({len(run)} instructions) */\n"
        f'__asm__ __volatile__("{asm}\\n"\n'
        f"                     : {', '.join(out_parts)}\n"
        f"                     : {in_list}\n"
        f"                     : {clob});\n"
    )


def lift_function(text: str, name: str) -> str:
    instrs = read_function(text, name)
    if not instrs:
        raise SystemExit(f"{name}: no such function in the asm")
    chunks = []
    by_addr = {a: i for i, (a, _, _) in enumerate(instrs)}
    for run in split_runs(instrs):
        i = by_addr[run[-1][0]]
        after = instrs[i + 1] if i + 1 < len(instrs) else None
        chunks.append(lift_run(run, after))
    return "\n".join(chunks) if chunks else f"/* {name}: no VU0 instructions */\n"


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument("function")
    parser.add_argument("--module", default="MANAGER")
    parser.add_argument(
        "--asm", type=Path, help="text.s to read (default: asm/xff/<MODULE>/text.s)"
    )
    args = parser.parse_args(argv)
    path = args.asm or ROOT / "asm" / "xff" / args.module / "text.s"
    text = path.read_text(encoding="latin-1")
    sys.stdout.write(lift_function(text, args.function))
    return 0


if __name__ == "__main__":
    sys.exit(main())
