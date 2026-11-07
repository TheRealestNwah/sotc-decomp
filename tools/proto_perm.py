#!/usr/bin/env python3
"""Search call-argument orders by permuting a callee's prototype parameters.

gcc 2.96 emits argument-setup instructions in the order of the *prototype's*
parameters, not in register order. When a near-miss differs only in where
`mov.s $f12, ...` / `daddu $a1, ...` land around a call, permuting the
declaration and the call together (keeping each argument in its register
class) can match. Example: `f(int, void *, float, float)` vs
`f(int, float, float, void *)` (see docs/vu0.md).

    python tools/proto_perm.py <file.c> <callee> --module MANAGER [--flags "-O2 -G0"]

Requires one `extern ... callee(<types>);` declaration and exactly one call
`callee(<args>);` in the file. Tries every permutation (at most 5 parameters),
prints the differing-word count of each improvement, and with --write leaves
the best version in the file.
"""

from __future__ import annotations

import argparse
import itertools
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def split_args(text: str) -> list[str]:
    """Split a parameter/argument list on top-level commas."""
    parts, depth, cur = [], 0, []
    for ch in text:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        if ch == "," and depth == 0:
            parts.append("".join(cur).strip())
            cur = []
        else:
            cur.append(ch)
    last = "".join(cur).strip()
    if last:
        parts.append(last)
    return parts


def find_sites(source: str, callee: str) -> tuple[re.Match[str], re.Match[str]]:
    proto = re.search(rf"^extern\s+[^;(]*\b{re.escape(callee)}\s*\(([^;]*)\)\s*;", source, re.M)
    calls = [
        m
        for m in re.finditer(rf"\b{re.escape(callee)}\s*\(([^;]*)\)\s*;", source)
        if proto is None or not (proto.start() <= m.start() < proto.end())
    ]
    if proto is None or len(calls) != 1:
        raise SystemExit(f"need one extern prototype and exactly one call of {callee}")
    return proto, calls[0]


def permuted(source: str, callee: str, order: tuple[int, ...]) -> str:
    proto, call = find_sites(source, callee)
    types = split_args(proto.group(1))
    args = split_args(call.group(1))
    if len(types) != len(args) or len(types) > 5:
        raise SystemExit("prototype and call must have the same, at most 5, parameters")
    new_proto = proto.group(0).replace(proto.group(1), ", ".join(types[i] for i in order))
    new_call = call.group(0).replace(call.group(1), ", ".join(args[i] for i in order))
    # Replace the later site first so earlier offsets stay valid.
    sites = sorted([(proto, new_proto), (call, new_call)], key=lambda s: -s[0].start())
    for match, text in sites:
        source = source[: match.start()] + text + source[match.end() :]
    return source


def diff_count(path: Path, module: str, flags: str) -> int:
    out = subprocess.run(
        [
            sys.executable,
            str(ROOT / "tools/try_compilers.py"),
            str(path),
            "--module",
            module,
            "--only",
            "ee-gcc2.96",
            "--flags",
            flags,
        ],
        capture_output=True,
        text=True,
        check=False,
    ).stdout
    found = re.findall(r"total (\d+)", out)
    return int(found[0]) if found else 10**6


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument("file", type=Path)
    parser.add_argument("callee")
    parser.add_argument("--module", required=True)
    parser.add_argument("--flags", default="-O2 -G0")
    parser.add_argument("--write", action="store_true", help="keep the best version in the file")
    args = parser.parse_args(argv)
    original = args.file.read_text(encoding="utf-8")
    count = len(split_args(find_sites(original, args.callee)[0].group(1)))
    best: tuple[int, tuple[int, ...], str] | None = None
    try:
        for order in itertools.permutations(range(count)):
            text = permuted(original, args.callee, order)
            args.file.write_text(text, encoding="utf-8")
            n = diff_count(args.file, args.module, args.flags)
            if best is None or n < best[0]:
                best = (n, order, text)
                print(f"{n} differing words with order {order}", flush=True)
            if n == 0:
                break
    finally:
        args.file.write_text(best[2] if args.write and best else original, encoding="utf-8")
    return 0


if __name__ == "__main__":
    sys.exit(main())
