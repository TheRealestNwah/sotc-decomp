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
from tools.ee_asm import FILL_DELAY_SLOTS, split_asm_options  # noqa: E402
from tools.try_compilers import (  # noqa: E402
    DEFAULT_COMPILERS,
    I386_LIBS,
    STAGE_INCLUDE,
    assemble,
    compile_c,
    diagnostic_message,
    find_cc1,
    find_package_as,
    include_dir_for,
    included_headers,
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


LINUX_PIPELINE_TEMPLATE = r"""
set -e
cc1=$1
assembler=$2
source=$3
output=$4
preprocess=$5
libs=$6
asm_options=$7
gp=$8
shift 8
case "$libs" in
    "~/"*) libs="$HOME/${libs:2}" ;;
esac
ld="$(dirname "$libs")/ld-linux.so.2"
[ -e "$ld" ] || ld="$libs/ld-linux.so.2"
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
cp "$source" "$work/in.c"
@STAGE_INCLUDE@
"$ld" --library-path "$libs" "$cc1" -quiet "$@" "$work/in.c" -o "$work/out.s"
if [ ! -s "$work/out.s" ]; then
    echo "error: compiler produced no assembly" >&2
    exit 1
fi
python3 "$preprocess" "$work/out.s" --gp "$gp" $asm_options
"$ld" --library-path "$libs" "$assembler" -EL -G "$gp" -o "$work/out.o" "$work/out.s"
cp "$work/out.o" "$output"
"""
# $inc (the include directory, or empty) comes in through the environment.
LINUX_PIPELINE = LINUX_PIPELINE_TEMPLATE.replace("@STAGE_INCLUDE@", STAGE_INCLUDE)


def compile_and_assemble(
    compiler_dir: Path, source: Path, flags: list[str], output: Path, package_as: Path
) -> str | None:
    """Use one WSL process for the Original Linux compiler, preparation and assembler.
    `flags` may include the assembler options of tools/ee_asm.py, which never reach cc1."""
    flags, fill_delay_slots = split_asm_options(flags)
    cc1 = find_cc1(compiler_dir)
    output.unlink(missing_ok=True)
    if cc1.suffix == ".exe":
        with tempfile.TemporaryDirectory() as tmp:
            asm = Path(tmp) / "out.s"
            return compile_c(compiler_dir, source, flags, asm) or assemble(
                asm, output, package_as, small_data_limit(flags), fill_delay_slots=fill_delay_slots
            )
    include = include_dir_for(source)
    result = subprocess.run(
        [
            "wsl", "-e", *(["env", f"inc={wsl_path(include)}"] if include else []),
            "bash", "-c", LINUX_PIPELINE, "ee-cc",
            wsl_path(cc1), wsl_path(package_as), wsl_path(source), wsl_path(output),
            wsl_path(ROOT / "tools/ee_asm.py"), I386_LIBS,
            FILL_DELAY_SLOTS if fill_delay_slots else "", str(small_data_limit(flags)),
            *flags,
        ],
        capture_output=True, text=True, errors="replace",
    )  # fmt: skip
    if result.returncode != 0 or not output.exists() or output.stat().st_size == 0:
        output.unlink(missing_ok=True)
        return diagnostic_message(result)
    return None


def depfile_text(source: Path, output: Path, root: Path | None = None) -> str:
    """A Makefile-style depfile for ninja (`deps = gcc`): the object depends on
    its source and every header from include/ it pulls in."""
    root = (root or ROOT).resolve()

    def name(path: Path) -> str:
        try:
            text = path.resolve().relative_to(root).as_posix()
        except ValueError:
            text = path.resolve().as_posix()
        return text.replace(" ", "\\ ")

    headers = included_headers(source, root / "include")
    return f"{name(output)}: " + " ".join(name(p) for p in [source, *headers]) + "\n"


def build(
    source: Path, output: Path, compiler_dir: Path, flags: list[str] | None = None
) -> str | None:
    package_as = find_package_as(compiler_dir)
    if package_as is None:
        return f"{compiler_dir} has no ee-as"
    output.parent.mkdir(parents=True, exist_ok=True)
    if flags is None:
        flags = source_cflags(source)
    return compile_and_assemble(compiler_dir, source, flags, output, package_as)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument("source", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--compilers", type=Path, default=DEFAULT_COMPILERS)
    parser.add_argument(
        "--loader",
        action="store_true",
        help="use the Loader's flags (-O2 -G8) wherever the source is, e.g. a permuter copy",
    )
    parser.add_argument(
        "--flag",
        action="append",
        default=[],
        help="an extra compiler flag (repeatable, e.g. --flag=-fno-strict-aliasing), "
        "for a copy outside src/ that config/ee_cflags.json can't name",
    )
    parser.add_argument(
        "--depfile",
        type=Path,
        help="also write a depfile listing the headers from include/ the source uses",
    )
    args = parser.parse_args(argv)
    flags = LOADER_CFLAGS.copy() if args.loader else None
    if args.flag:
        flags = (flags or CFLAGS.copy()) + args.flag
    error = build(args.source, args.output, args.compilers / COMPILER, flags)
    if args.depfile:
        args.depfile.parent.mkdir(parents=True, exist_ok=True)
        args.depfile.write_text(depfile_text(args.source, args.output), encoding="utf-8")
    if error:
        print(f"{args.source}: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
