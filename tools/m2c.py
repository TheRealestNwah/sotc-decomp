"""First C draft of an XFF function with m2c.

    python tools/m2c.py getMinAmbient
    python tools/m2c.py func_000C0D48 --through func_000C0E78 --module GAMECORE
    python tools/m2c.py getMinAmbient --context ctx.c   # other options go to m2c

m2c (github.com/matt-kempster/m2c) decompiles MIPS assembly into C. The
output is a starting point: it has the right control flow and data accesses,
but it rarely matches as-is. It lives outside the repo, at $SOTC_M2C
(default D:/Modding/decomp-tools/m2c).

The function is taken from asm/xff/<MODULE>/text.s and cleaned up for m2c:
- local twin labels (.Lxff.name) become plain names;
- words the split had to emit raw (an explicit .reloc plus .word) are put
  back as the instruction spimdisasm wrote in the comment.
spimdisasm sometimes ends a function at a tail call and labels the rest
func_XXXXXXXX; --through LABEL includes everything up to that label's end.
"""

from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
M2C = Path(os.environ.get("SOTC_M2C", "D:/Modding/decomp-tools/m2c"))
RAW_WORD_RE = re.compile(r"^(\s*/\*[^*]*\*/\s*)\.word\s+0x[0-9A-Fa-f]+\s*/\*\s*(.*?)\s*\*/\s*$")


def extract(lines: list[str], name: str, through: str | None) -> list[str]:
    try:
        first = next(
            i
            for i, line in enumerate(lines)
            if re.match(rf"\s*\w+label\s+{re.escape(name)}\b", line)
        )
    except StopIteration:
        raise SystemExit(f"{name}: no such label") from None
    last_label = through or name
    for i in range(first, len(lines)):
        if re.match(rf"\s*endlabel\s+{re.escape(last_label)}\b", lines[i]):
            body = lines[first : i + 1]
            # One function for m2c: drop the split's inner function boundaries.
            inner = re.compile(r"\s*(glabel|endlabel|nonmatching)\b")
            return [body[0]] + [x for x in body[1:-1] if not inner.match(x)] + [body[-1]]
    raise SystemExit(f"{last_label}: no endlabel after {name}")


def clean(lines: list[str]) -> list[str]:
    out = []
    for line in lines:
        if line.strip().startswith(".reloc "):
            continue
        m = RAW_WORD_RE.match(line)
        if m:
            line = m.group(1) + m.group(2)
        out.append(line.replace(".Lxff.", ""))
    return out


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument("function")
    parser.add_argument("--module", default="GAMECORE")
    parser.add_argument("--through", help="include spimdisasm's split-off rest up to this label")
    args, m2c_args = parser.parse_known_args(argv)  # the rest goes to m2c

    text = ROOT / f"asm/xff/{args.module.upper()}/text.s"
    lines = text.read_text(encoding="latin-1").splitlines()
    body = clean(extract(lines, args.function, args.through))
    # m2c only treats glabel as a function start; alabel/jlabel are fine as labels.
    body[0] = re.sub(r"^\s*\w+label", "glabel", body[0])
    with tempfile.TemporaryDirectory() as tmp:
        asm = Path(tmp) / "fn.s"
        asm.write_text("\n".join(body) + "\n", encoding="latin-1")
        result = subprocess.run(
            [sys.executable, str(M2C / "m2c.py"), "-t", "mipsee-gcc-c", *m2c_args, str(asm)]
        )
    return result.returncode


if __name__ == "__main__":
    sys.exit(main())
