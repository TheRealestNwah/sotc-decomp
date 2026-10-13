"""Compile C with every candidate compiler and compare against original functions.

    python tools/try_compilers.py experiments/test.c --module GAMECORE
    python tools/try_compilers.py experiments/test.c --module GAMECORE --flags "-O2 -G0" "-O1 -G0"

Every function defined in the C file is compared with the function of the same
name in the original module. Relocated fields are ignored on both sides (they
depend on link layout), but relocation positions and types must line up.

Compilers come from decomp.me's archive, extracted under --compilers (default
D:/Modding/compilers or $SOTC_COMPILERS). Windows builds (cc1.exe) run
directly; Linux builds run under WSL with a private 32-bit libc
($SOTC_I386_LIBS, default ~/i386libs/root/usr/lib/i386-linux-gnu inside WSL).
"""

from __future__ import annotations

import argparse
import io
import os
import re
import subprocess
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path

from elftools.elf.elffile import ELFFile

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from tools.xff2 import parse, to_elf  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
DEFAULT_COMPILERS = Path(os.environ.get("SOTC_COMPILERS", "D:/Modding/compilers"))
I386_LIBS = os.environ.get("SOTC_I386_LIBS", "~/i386libs/root/usr/lib/i386-linux-gnu")
ASSEMBLER = os.environ.get("SOTC_AS", "mips64r5900el-ps2-elf-as")
ASFLAGS = ["-EL", "-march=r5900", "-mabi=eabi", "-G", "0"]
DEFAULT_FLAGS = ["-O2 -G0", "-O1 -G0", "-O3 -G0", "-O2 -G8", "-Os -G0"]
RELOC_MASKS = {2: 0xFFFFFFFF, 4: 0x03FFFFFF, 5: 0x0000FFFF, 6: 0x0000FFFF, 7: 0x0000FFFF}


@dataclass
class Function:
    words: list[int]
    relocs: dict[int, int]  # word index -> relocation type


def wsl_path(path: Path) -> str:
    p = path.resolve().as_posix()
    return f"/mnt/{p[0].lower()}{p[2:]}" if p[1] == ":" else p


def find_cc1(compiler_dir: Path) -> Path:
    for name in ("cc1", "cc1.exe"):
        found = sorted(compiler_dir.rglob(name))
        if found:
            return found[0]
    raise FileNotFoundError(f"no cc1 in {compiler_dir}")


def compile_c(compiler_dir: Path, source: Path, flags: list[str], out: Path) -> str | None:
    """Returns an error message, or None on success."""
    cc1 = find_cc1(compiler_dir)
    if cc1.suffix == ".exe":
        cmd = [str(cc1), "-quiet", *flags, str(source), "-o", str(out)]
    else:
        # Old 32-bit programs can't stat files on Windows-mounted drives
        # ("Value too large for defined data type"), so work in WSL's /tmp.
        script = (
            f"ld=$(dirname {I386_LIBS})/ld-linux.so.2; "
            f'[ -e "$ld" ] || ld={I386_LIBS}/ld-linux.so.2; '
            'work=$(mktemp -d); cp "$1" "$work/in.c"; cc1="$0"; shift 2; '
            f'"$ld" --library-path {I386_LIBS} "$cc1" -quiet "$@" '
            '"$work/in.c" -o "$work/out.s"; status=$?; '
            '[ -f "$work/out.s" ] && cp "$work/out.s" "$OUT"; rm -rf "$work"; exit $status'
        )
        cmd = ["wsl", "-e", "env", f"OUT={wsl_path(out)}", "bash", "-c", script, wsl_path(cc1),
               wsl_path(source), wsl_path(out), *flags]  # fmt: skip
    result = subprocess.run(cmd, capture_output=True, text=True, errors="replace")
    if result.returncode != 0 or not out.exists() or out.stat().st_size == 0:
        return (result.stderr or result.stdout or "no output").strip().splitlines()[-1][:200]
    return None


def fix_moves(asm: Path) -> None:
    """The original assembler expanded `move` to `daddu rd, rs, $zero` (64-bit
    EABI); modern binutils picks a different encoding."""
    text = asm.read_text(encoding="latin-1")
    text = re.sub(r"\bmove\t(\$\w+),(\$\w+)", r"daddu\t\1,\2,$0", text)
    asm.write_text(text, encoding="latin-1")


def find_package_as(compiler_dir: Path) -> Path | None:
    found = sorted(compiler_dir.rglob("ee-as"))
    return found[0] if found else None


def assemble(asm: Path, obj: Path, package_as: Path | None = None) -> str | None:
    """Assemble with the compiler package's own (era-matching) ee-as when
    given; otherwise modern binutils, patching the one known expansion
    difference. Macro expansions (`move`, `lw reg, sym(reg)`) differ between
    assembler versions, so the package's assembler is preferred."""
    if package_as is not None:
        script = (
            f'L={I386_LIBS}; work=$(mktemp -d); cp "$1" "$work/in.s"; '
            '"$L/ld-linux.so.2" --library-path "$L" "$0" -EL -G 0 -o "$work/out.o" "$work/in.s" '
            "2>&1 | tail -3; status=${PIPESTATUS[0]}; "
            '[ -f "$work/out.o" ] && cp "$work/out.o" "$2"; rm -rf "$work"; exit $status'
        )
        result = subprocess.run(
            ["wsl", "-e", "bash", "-c", script, wsl_path(package_as), wsl_path(asm), wsl_path(obj)],
            capture_output=True, text=True, errors="replace",
        )  # fmt: skip
    else:
        fix_moves(asm)
        result = subprocess.run([ASSEMBLER, *ASFLAGS, "-o", str(obj), str(asm)],
                                capture_output=True, text=True)  # fmt: skip
    if result.returncode != 0 or not obj.exists():
        lines = (result.stderr or result.stdout or "assembler failed").strip().splitlines()
        return lines[-1][:200]
    return None


def functions_in(elf: ELFFile) -> dict[str, Function]:
    text_index = elf.get_section_index(".text")
    text = elf.get_section_by_name(".text").data()
    relocs: dict[int, int] = {}
    rel = elf.get_section_by_name(".rel.text")
    if rel is not None:
        for r in rel.iter_relocations():
            relocs[r["r_offset"]] = r["r_info_type"]
    symbols = sorted(
        (s["st_value"], s["st_size"], s.name)
        for s in elf.get_section_by_name(".symtab").iter_symbols()
        if s["st_info"]["type"] == "STT_FUNC" and s["st_shndx"] == text_index and s.name
    )
    out = {}
    for i, (start, size, name) in enumerate(symbols):
        if size == 0:
            size = (symbols[i + 1][0] if i + 1 < len(symbols) else len(text)) - start
        words = [int.from_bytes(text[o : o + 4], "little") for o in range(start, start + size, 4)]
        out[name] = Function(
            words, {(o - start) // 4: t for o, t in relocs.items() if start <= o < start + size}
        )
    return out


def strip_padding(words: list[int]) -> list[int]:
    while words and words[-1] == 0:
        words = words[:-1]
    return words


def diff(target: Function, built: Function) -> int:
    """Number of differing instructions (0 = match)."""
    a, b = strip_padding(target.words), strip_padding(built.words)
    count = abs(len(a) - len(b))
    for i, (x, y) in enumerate(zip(a, b, strict=False)):
        ta, tb = target.relocs.get(i), built.relocs.get(i)
        if ta != tb:
            count += 1
            continue
        mask = ~RELOC_MASKS.get(ta, 0) & 0xFFFFFFFF if ta else 0xFFFFFFFF
        count += (x ^ y) & mask != 0
    return count


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument("source", type=Path)
    parser.add_argument("--module", default="GAMECORE")
    parser.add_argument("--compilers", type=Path, default=DEFAULT_COMPILERS)
    parser.add_argument("--only", nargs="*", help="compiler directory names to try")
    parser.add_argument("--flags", nargs="*", default=DEFAULT_FLAGS)
    parser.add_argument(
        "--modern-as", action="store_true",
        help="always use modern binutils, even when the package ships ee-as",
    )  # fmt: skip
    args = parser.parse_args(argv)

    original = ELFFile(io.BytesIO(to_elf(parse((ROOT / f"iso/{args.module}.XFF").read_bytes()))))
    targets = functions_in(original)
    compilers = sorted(
        p for p in args.compilers.iterdir() if p.is_dir() and not p.name.startswith("_")
    )
    if args.only:
        compilers = [p for p in compilers if p.name in args.only]

    names_width = max(len(p.name) for p in compilers)
    with tempfile.TemporaryDirectory() as tmp:
        tmpdir = Path(tmp)
        source = tmpdir / "input.c"
        source.write_text(args.source.read_text(encoding="utf-8"), encoding="utf-8")
        header = None
        for compiler in compilers:
            for flags in args.flags:
                asm, obj = tmpdir / "out.s", tmpdir / "out.o"
                asm.unlink(missing_ok=True)
                obj.unlink(missing_ok=True)
                package_as = None if args.modern_as else find_package_as(compiler)
                error = compile_c(compiler, source, flags.split(), asm) or assemble(
                    asm, obj, package_as
                )
                label = f"{compiler.name:{names_width}} {flags:10}"
                if package_as is None and not args.modern_as:
                    label += "*"
                if error:
                    print(f"{label} error: {error}")
                    continue
                with obj.open("rb") as f:
                    built = functions_in(ELFFile(f))
                names = [n for n in built if n in targets]
                if header is None:
                    header = names
                    print(f"{'':{names_width + 11}} " + " ".join(f"{n[:14]:>14}" for n in names))
                cells = [diff(targets[n], built[n]) for n in header if n in built]
                total = sum(cells)
                print(f"{label} " + " ".join(f"{('MATCH' if c == 0 else c):>14}" for c in cells)
                      + f"   total {total}")  # fmt: skip
    return 0


if __name__ == "__main__":
    sys.exit(main())
