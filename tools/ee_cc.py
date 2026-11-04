"""Compile a C file to an object with the game's toolchain.

    python tools/ee_cc.py src/xff/GAMECORE/foo.c build/src/xff/GAMECORE/foo.o

ee-gcc 2.96 (-O2 -G0) and its own ee-as, the combination identified in
docs/findings.md. The Linux binaries run under WSL; see tools/try_compilers.py.
The Loader's Game code (src/loader/) reads its globals through $gp, so it's
built with -G8 instead (see "Loader function map" in docs/findings.md).
"""

from __future__ import annotations

import argparse
import json
import os
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from tools.try_compilers import (  # noqa: E402
    DEFAULT_COMPILERS,
    I386_LIBS,
    assemble,
    compile_c,
    diagnostic_message,
    find_cc1,
    find_package_as,
    wsl_path,
)

COMPILER = os.environ.get("SOTC_COMPILER", "ee-gcc2.96")
CFLAGS = ["-O2", "-G0"]
LOADER_CFLAGS = ["-O2", "-G8"]
ROOT = Path(__file__).resolve().parent.parent


def source_cflags(source: Path, root: Path | None = None) -> list[str]:
    """Add only the source-specific options supported by matching evidence."""
    root = (root or ROOT).resolve()
    try:
        relative = source.resolve().relative_to(root).as_posix()
    except ValueError:
        return CFLAGS.copy()
    base = LOADER_CFLAGS if relative.startswith("src/loader/") else CFLAGS
    settings = json.loads((root / "config/ee_cflags.json").read_text(encoding="utf-8"))
    if not isinstance(settings, dict):
        raise ValueError("config/ee_cflags.json must map source paths to flag lists")
    extra = settings.get(relative, [])
    if not isinstance(extra, list) or any(not isinstance(flag, str) for flag in extra):
        raise ValueError(f"compiler flags for {relative} must be a list of strings")
    return base + extra


def small_data_limit(flags: list[str]) -> int:
    """The -G value gcc uses (the last one given); the assembler needs the same."""
    limits = [int(f[2:]) for f in flags if f.startswith("-G") and f[2:].isdigit()]
    return limits[-1] if limits else 0


LINUX_PIPELINE = r"""
set -e
cc1=$1
assembler=$2
source=$3
output=$4
preprocess=$5
libs=$6
gp=$7
shift 7
case "$libs" in
    "~/"*) libs="$HOME/${libs:2}" ;;
esac
ld="$(dirname "$libs")/ld-linux.so.2"
[ -e "$ld" ] || ld="$libs/ld-linux.so.2"
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
cp "$source" "$work/in.c"
"$ld" --library-path "$libs" "$cc1" -quiet "$@" "$work/in.c" -o "$work/out.s"
if [ ! -s "$work/out.s" ]; then
    echo "error: compiler produced no assembly" >&2
    exit 1
fi
python3 "$preprocess" "$work/out.s" --gp "$gp"
"$ld" --library-path "$libs" "$assembler" -EL -G "$gp" -o "$work/out.o" "$work/out.s"
cp "$work/out.o" "$output"
"""


def compile_and_assemble(
    compiler_dir: Path, source: Path, flags: list[str], output: Path, package_as: Path
) -> str | None:
    """Use one WSL process for the Original Linux compiler, preparation and assembler."""
    cc1 = find_cc1(compiler_dir)
    output.unlink(missing_ok=True)
    if cc1.suffix == ".exe":
        with tempfile.TemporaryDirectory() as tmp:
            asm = Path(tmp) / "out.s"
            return compile_c(compiler_dir, source, flags, asm) or assemble(
                asm, output, package_as, small_data_limit(flags)
            )
    result = subprocess.run(
        [
            "wsl", "-e", "bash", "-c", LINUX_PIPELINE, "ee-cc",
            wsl_path(cc1), wsl_path(package_as), wsl_path(source), wsl_path(output),
            wsl_path(ROOT / "tools/ee_asm.py"), I386_LIBS, str(small_data_limit(flags)),
            *flags,
        ],
        capture_output=True, text=True, errors="replace",
    )  # fmt: skip
    if result.returncode != 0 or not output.exists() or output.stat().st_size == 0:
        output.unlink(missing_ok=True)
        return diagnostic_message(result)
    return None


def build(source: Path, output: Path, compiler_dir: Path) -> str | None:
    package_as = find_package_as(compiler_dir)
    if package_as is None:
        return f"{compiler_dir} has no ee-as"
    output.parent.mkdir(parents=True, exist_ok=True)
    return compile_and_assemble(compiler_dir, source, source_cflags(source), output, package_as)


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
