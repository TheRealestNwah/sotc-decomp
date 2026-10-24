"""Compile a C file to an object with the game's toolchain.

    python tools/ee_cc.py src/xff/GAMECORE/foo.c build/src/xff/GAMECORE/foo.o

ee-gcc 2.96 (-O2 -G0) and its own ee-as, the combination identified in
docs/findings.md. The Linux binaries run under WSL; see tools/try_compilers.py.
"""

from __future__ import annotations

import argparse
import json
import os
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from tools.try_compilers import (  # noqa: E402
    DEFAULT_COMPILERS,
    assemble,
    compile_c,
    find_package_as,
)

COMPILER = os.environ.get("SOTC_COMPILER", "ee-gcc2.96")
CFLAGS = ["-O2", "-G0"]
ROOT = Path(__file__).resolve().parent.parent


def source_cflags(source: Path, root: Path | None = None) -> list[str]:
    """Add only the source-specific options supported by matching evidence."""
    root = (root or ROOT).resolve()
    try:
        relative = source.resolve().relative_to(root).as_posix()
    except ValueError:
        return CFLAGS.copy()
    settings = json.loads((root / "config/ee_cflags.json").read_text(encoding="utf-8"))
    if not isinstance(settings, dict):
        raise ValueError("config/ee_cflags.json must map source paths to flag lists")
    extra = settings.get(relative, [])
    if not isinstance(extra, list) or any(not isinstance(flag, str) for flag in extra):
        raise ValueError(f"compiler flags for {relative} must be a list of strings")
    return CFLAGS + extra


def build(source: Path, output: Path, compiler_dir: Path) -> str | None:
    package_as = find_package_as(compiler_dir)
    if package_as is None:
        return f"{compiler_dir} has no ee-as"
    output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory() as tmp:
        asm = Path(tmp) / "out.s"
        error = compile_c(compiler_dir, source, source_cflags(source), asm)
        if error:
            return error
        output.unlink(missing_ok=True)
        return assemble(asm, output, package_as)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument("source", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--compilers", type=Path, default=DEFAULT_COMPILERS)
    args = parser.parse_args(argv)
    error = build(args.source, args.output, args.compilers / COMPILER)
    if error:
        print(f"{args.source}: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
