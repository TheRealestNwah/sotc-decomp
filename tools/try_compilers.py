"""Compile C with every candidate compiler and compare against original functions.

    python tools/try_compilers.py experiments/test.c --module GAMECORE
    python tools/try_compilers.py experiments/test.c --module GAMECORE --flags "-O2 -G0" "-O1 -G0"

Every function defined in the C file is compared with the function of the same
name in the original module, by the same rule the splice step uses
(tools/functions.py): words, relocation types and by-name targets must match.
A section-relative target depends on where the C file's statics and data land,
which only the splice step works out, so a function whose words all match but
which has such a reference prints MATCH? instead of MATCH. `ninja check`
confirms it.

Compilers come from decomp.me's archive, extracted under --compilers (default
D:/Modding/compilers or $SOTC_COMPILERS). Windows builds (cc1.exe) run
directly; Linux builds run under WSL with a private 32-bit libc
($SOTC_I386_LIBS, default ~/i386libs/root/usr/lib/i386-linux-gnu inside WSL).
"""

from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

from elftools.elf.elffile import ELFFile

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from tools.functions import Function, compare, function, functions, open_module  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
DEFAULT_COMPILERS = Path(os.environ.get("SOTC_COMPILERS", "D:/Modding/compilers"))
I386_LIBS = os.environ.get("SOTC_I386_LIBS", "~/i386libs/root/usr/lib/i386-linux-gnu")
ASSEMBLER = os.environ.get("SOTC_AS", "mips64r5900el-ps2-elf-as")
ASFLAGS = ["-EL", "-march=r5900", "-mabi=eabi", "-G", "0"]
DEFAULT_FLAGS = ["-O2 -G0", "-O1 -G0", "-O3 -G0", "-O2 -G8", "-Os -G0"]


def wsl_path(path: Path) -> str:
    p = str(path).replace("\\", "/")
    if not re.match(r"[A-Za-z]:/", p):  # not already a Windows absolute path
        p = Path(path).resolve().as_posix()
    return f"/mnt/{p[0].lower()}{p[2:]}" if re.match(r"[A-Za-z]:/", p) else p


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
        diagnostics = result.stderr.strip() or result.stdout.strip() or "no output"
        lines = diagnostics.splitlines()
        error = next(
            (
                line
                for line in lines
                if re.search(r"\berror(?=[:\s]|$)", line, re.I)
                and not re.search(r"\bwarning:", line, re.I)
            ),
            lines[-1],
        )
        return error[:200]
    return None


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


def find_package_as(compiler_dir: Path) -> Path | None:
    found = sorted(compiler_dir.rglob("ee-as"))
    return found[0] if found else None


def assemble(asm: Path, obj: Path, package_as: Path | None = None, gp: int = 0) -> str | None:
    """Assemble with the compiler package's own (era-matching) ee-as when
    given; otherwise modern binutils, patching the one known expansion
    difference. Macro expansions (`move`, `lw reg, sym(reg)`) differ between
    assembler versions, so the package's assembler is preferred. `gp` is the
    small-data limit (-G) the C was compiled with."""
    volatile_barriers(asm)
    indexed_la_barriers(asm)
    if gp == 0:
        expand_indexed_loads(asm)
    jump_barriers(asm)
    if package_as is not None:
        script = (
            f'L={I386_LIBS}; work=$(mktemp -d); cp "$1" "$work/in.s"; '
            f'"$L/ld-linux.so.2" --library-path "$L" "$0" -EL -G {gp} '
            '-o "$work/out.o" "$work/in.s" '
            "2>&1 | tail -3; status=${PIPESTATUS[0]}; "
            '[ -f "$work/out.o" ] && cp "$work/out.o" "$2"; rm -rf "$work"; exit $status'
        )
        result = subprocess.run(
            ["wsl", "-e", "bash", "-c", script, wsl_path(package_as), wsl_path(asm), wsl_path(obj)],
            capture_output=True, text=True, errors="replace",
        )  # fmt: skip
    else:
        fix_moves(asm)
        flags = [*ASFLAGS[:-1], str(gp)]
        result = subprocess.run([ASSEMBLER, *flags, "-o", str(obj), str(asm)],
                                capture_output=True, text=True)  # fmt: skip
    if result.returncode != 0 or not obj.exists():
        lines = (result.stderr or result.stdout or "assembler failed").strip().splitlines()
        return lines[-1][:200]
    return None


def verdict(target: Function, built: Function) -> tuple[str, int]:
    """(cell text, number of differing words): MATCH, MATCH? when only
    section-relative targets are left unchecked, or the count."""
    mismatches = compare(target, built)
    count = sum(m.verified for m in mismatches)
    if count:
        return str(count), count
    return ("MATCH?" if mismatches else "MATCH"), 0


def disassemble(word: int) -> str:
    import rabbitizer  # comes with spimdisasm

    return rabbitizer.Instruction(word, 0, rabbitizer.InstrCategory.R5900).disassemble()


def show_diff(name: str, target: Function, built: Function) -> None:
    """Side-by-side listing, original on the left. `*` marks a differing word,
    `?` one whose section-relative target isn't checked here."""
    marks = {}
    for m in compare(target, built):
        if m.kind == "length":
            for i in range(m.index, max(len(target.words), len(built.words))):
                marks[i] = "*"
        else:
            marks[m.index] = "*" if m.verified else "?"
    a, b = target.words, built.words
    print(f"\n{name}: original {len(a)} words, C {len(b)} words")
    for i in range(max(len(a), len(b))):
        x = a[i] if i < len(a) else None
        y = b[i] if i < len(b) else None
        left = disassemble(x) if x is not None else ""
        right = disassemble(y) if y is not None else ""
        print(f"{marks.get(i, ' ')} {4 * i:4X}  {left:40} {right}")


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
        "--diff", action="store_true", help="print a side-by-side listing of every mismatch"
    )
    parser.add_argument(
        "--modern-as", action="store_true",
        help="always use modern binutils, even when the package ships ee-as",
    )  # fmt: skip
    args = parser.parse_args(argv)

    original = open_module(args.module, ROOT / "iso")
    targets = functions(original)
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
                    built = functions(ELFFile(f))
                for n, fn in built.items():
                    if n not in targets:
                        try:
                            targets[n] = function(original, n, 4 * len(fn.words))
                        except KeyError:
                            pass  # not in the original
                names = [n for n in built if n in targets]
                if header is None:
                    header = names
                    print(f"{'':{names_width + 11}} " + " ".join(f"{n[:14]:>14}" for n in names))
                cells = [verdict(targets[n], built[n]) for n in header if n in built]
                total = sum(count for _, count in cells)
                print(f"{label} " + " ".join(f"{text:>14}" for text, _ in cells)
                      + f"   total {total}")  # fmt: skip
                if args.diff:
                    for n in header:
                        if n in built and verdict(targets[n], built[n])[0] != "MATCH":
                            show_diff(n, targets[n], built[n])
    return 0


if __name__ == "__main__":
    sys.exit(main())
