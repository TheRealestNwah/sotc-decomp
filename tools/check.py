"""Compare the rebuilt flat image against the original, byte for byte.

    python tools/check.py build/SCUS_974.72.rom iso/SCUS_974.72.rom

Both images come from tools/elf2rom.py, so this compares every loaded byte of
code and data. ELF headers and section tables are not compared.
"""

from __future__ import annotations

import argparse
import hashlib
import sys
from pathlib import Path


def first_difference(a: bytes, b: bytes) -> int | None:
    for i, (x, y) in enumerate(zip(a, b, strict=False)):
        if x != y:
            return i
    if len(a) != len(b):
        return min(len(a), len(b))
    return None


def compare(built: bytes, original: bytes) -> tuple[bool, str]:
    built_sha1 = hashlib.sha1(built).hexdigest()
    original_sha1 = hashlib.sha1(original).hexdigest()
    if built_sha1 == original_sha1:
        return True, f"OK: matches ({built_sha1})"

    lines = [
        "MISMATCH",
        f"  built:    {built_sha1} ({len(built):#x} bytes)",
        f"  original: {original_sha1} ({len(original):#x} bytes)",
    ]
    offset = first_difference(built, original)
    if offset is not None:
        lines.append(f"  first difference at image offset {offset:#x}")
        diffs = sum(x != y for x, y in zip(built, original, strict=False))
        lines.append(f"  {diffs} differing bytes in the overlapping range")
    return False, "\n".join(lines)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("built", type=Path)
    parser.add_argument("original", type=Path)
    args = parser.parse_args(argv)

    ok, message = compare(args.built.read_bytes(), args.original.read_bytes())
    print(message)
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
