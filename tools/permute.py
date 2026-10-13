"""Run decomp-permuter on a function that doesn't match yet.

    python tools/permute.py setup src/xff/GAMECORE/sword.c func_000C29B0
    python tools/permute.py run build/permuter/func_000C29B0 -j8

decomp-permuter (github.com/simonlindholm/decomp-permuter) randomly rewrites a
C function in ways that keep its meaning, compiles each version and keeps the
ones whose code is closer to the original. It's the standard tool for the
register allocation and scheduling differences that are hard to fix by hand.
It lives outside the repo, at $SOTC_PERMUTER (default
D:/Modding/decomp-tools/decomp-permuter).

`setup` writes build/permuter/<function>/:
- base.c: the C file with only this function's parked (NONMATCHING) attempt
  switched on;
- target.o: the original function's words. Relocated fields are zeroed and
  every relocation points at one placeholder symbol: the original and the C
  name statics differently, which says nothing about the code;
- compile.sh: compiles with tools/ee_cc.py (ee-gcc 2.96 -O2 -G0 + ee-as);
- settings.toml: the function name and this script as objdump.

`run` starts the permuter with what it expects on Windows: Git's bash,
ee-gcc 2.96's cpp0 (under WSL) for preprocessing, and the PS2DEV objdump (via `objdump`
below, which applies the same placeholder normalization to candidates).
Better candidates land in build/permuter/<function>/output-*/.
"""

from __future__ import annotations

import argparse
import io
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

from elftools.elf.elffile import ELFFile

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from tools.try_compilers import (  # noqa: E402
    ADDRESS_NAME_RE,
    DEFAULT_COMPILERS,
    I386_LIBS,
    wsl_path,
)
from tools.xff2 import parse, to_elf  # noqa: E402
from tools.xff_splice import FIELD_MASKS, RELOC_NAMES  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
PERMUTER = Path(os.environ.get("SOTC_PERMUTER", "D:/Modding/decomp-tools/decomp-permuter"))
CROSS = os.environ.get("SOTC_CROSS", "mips64r5900el-ps2-elf-")
GIT_BASH = Path(os.environ.get("SOTC_BASH", "C:/Program Files/Git/bin/bash.exe"))
PLACEHOLDER = "reloc_target"
NUMBER_RE = re.compile(r"(?<![\w$.])-?(?:0x[0-9a-fA-F]+|\d+)(?![\w])")


def original_function(
    module: str, name: str, size: int | None = None
) -> tuple[list[int], dict[int, int]]:
    """The original function's words and relocation types (word index -> type).
    Named functions use the symbol; statics named after their asm label start
    at the label's address and are `size` bytes long."""
    elf = ELFFile(io.BytesIO(to_elf(parse((ROOT / f"iso/{module}.XFF").read_bytes()))))
    text = elf.get_section_by_name(".text")
    data = text.data()
    symbol = next(
        (s for s in elf.get_section_by_name(".symtab").iter_symbols() if s.name == name), None
    )
    if symbol is not None and symbol["st_size"]:
        start, size = symbol["st_value"], symbol["st_size"]
    else:
        m = ADDRESS_NAME_RE.fullmatch(name)
        if not m:
            raise SystemExit(f"{name}: not a symbol of {module} and not named after an address")
        if size is None:
            raise SystemExit(f"{name}: the original has no size for it")
        start = int(m.group(1), 16) - text["sh_offset"]
    words = [int.from_bytes(data[o : o + 4], "little") for o in range(start, start + size, 4)]
    while words and words[-1] == 0:  # alignment padding
        words.pop()
    relocs = {}
    for r in elf.get_section_by_name(".rel.text").iter_relocations():
        if start <= r["r_offset"] < start + 4 * len(words):
            relocs[(r["r_offset"] - start) // 4] = r["r_info_type"]
    return words, relocs


NONMATCHING_RE = re.compile(r"^#ifdef NONMATCHING\n(.*?)^#(?:else\n(.*?)^#)?endif\n", re.M | re.S)


def only_target(source: str, name: str) -> str:
    """The C file with only `name`'s parked (NONMATCHING) attempt switched on.
    The other attempts aren't needed and might not parse: pycparser, which
    the permuter uses, rejects inline asm."""
    definition = re.compile(rf"^\w[^\n;]*\b{re.escape(name)}\(", re.M)

    def choose(m: re.Match) -> str:
        if definition.search(m.group(1)):
            return m.group(1)
        return m.group(2) or ""

    return NONMATCHING_RE.sub(choose, source)


def compiled_size(source: Path, name: str) -> int | None:
    """Size of `name` as the C file compiles now."""
    obj = source.with_suffix(".o")
    subprocess.run([sys.executable, str(ROOT / "tools/ee_cc.py"), str(source), str(obj)],
                   check=True)  # fmt: skip
    with obj.open("rb") as f:
        elf = ELFFile(io.BytesIO(f.read()))
    symbols = elf.get_section_by_name(".symtab").iter_symbols()
    sym = next((s for s in symbols if s.name == name), None)
    return sym["st_size"] if sym is not None else None


def target_asm(name: str, words: list[int], relocs: dict[int, int]) -> str:
    lines = [".set noreorder", ".set noat", ".text", f".globl {name}", f".ent {name}", f"{name}:"]
    for i, word in enumerate(words):
        if i in relocs:
            word &= ~FIELD_MASKS[relocs[i]] & 0xFFFFFFFF
            lines.append(f".reloc ., {RELOC_NAMES[relocs[i]]}, {PLACEHOLDER}")
        lines.append(f".word 0x{word:08X}")
    lines += [f".end {name}", ""]
    return "\n".join(lines)


def bash_path(path: Path) -> str:
    return path.resolve().as_posix()


def setup(c_file: Path, name: str, module: str, out: Path) -> None:
    out.mkdir(parents=True, exist_ok=True)
    base = out / "base.c"
    base.write_text(only_target(c_file.read_text(encoding="utf-8"), name), encoding="utf-8")
    words, relocs = original_function(module, name, compiled_size(base, name))
    asm = out / "target.s"
    asm.write_text(target_asm(name, words, relocs), encoding="utf-8")
    subprocess.run(
        [f"{CROSS}as", "-EL", "-march=r5900", "-mabi=eabi", "-G", "0", "-o",
         str(out / "target.o"), str(asm)],
        check=True,
    )  # fmt: skip
    python = bash_path(Path(sys.executable))
    (out / "compile.sh").write_text(
        f'#!/bin/bash\nexec "{python}" "{bash_path(ROOT / "tools/ee_cc.py")}" "$1" "$3"\n',
        encoding="utf-8",
        newline="\n",
    )
    (out / "settings.toml").write_text(
        f'func_name = "{name}"\ncompiler_type = "gcc"\n'
        f'objdump_command = "{python} {bash_path(Path(__file__))} objdump"\n',
        encoding="utf-8",
    )
    print(f"{out}: {len(words)} words, {len(relocs)} relocations")


RELOC_LINE_RE = re.compile(r"^(\s+[0-9a-f]+: R_MIPS_\w+\s+)(\S+)")
INSN_LINE_RE = re.compile(r"^\s+[0-9a-f]+:\t[0-9a-f]{8} \t")


def normalize_objdump(text: str) -> str:
    """Points every relocation at the placeholder and zeroes the relocated
    instruction's immediates, so only the code itself is compared."""
    lines = text.splitlines()
    insn = None  # index of the last instruction line
    for i, line in enumerate(lines):
        if INSN_LINE_RE.match(line):
            insn = i
            continue
        m = RELOC_LINE_RE.match(line)
        if not m:
            continue
        lines[i] = m.group(1) + PLACEHOLDER
        if insn is not None:
            parts = lines[insn].split("\t")
            if len(parts) >= 4:
                parts[3] = NUMBER_RE.sub("0", re.sub(r"\s*<.*?>", "", parts[3]))
                lines[insn] = "\t".join(parts)
    return "\n".join(lines) + "\n"


def objdump(obj: str) -> int:
    out = subprocess.run(
        [f"{CROSS}objdump", "-drz", "-m", "mips:5900", obj],
        check=True, capture_output=True, text=True,
    ).stdout  # fmt: skip
    sys.stdout.write(normalize_objdump(out))
    return 0


def run(directory: Path, extra: list[str]) -> int:
    sys.path.insert(0, str(PERMUTER))
    os.environ["PATH"] = os.pathsep.join([str(GIT_BASH.parent), os.environ["PATH"]])
    if shutil.which("bash") != str(GIT_BASH) and not shutil.which(
        "bash", path=str(GIT_BASH.parent)
    ):
        raise SystemExit(f"Git bash not found at {GIT_BASH} (set SOTC_BASH)")

    import src.main as permuter_main  # type: ignore[import-not-found]

    def preprocess(filename: str, cpp_args: list[str] | None = None) -> str:
        # ee-gcc 2.96's own cpp0, under WSL like the compiler (see try_compilers.py).
        cpp0 = next(DEFAULT_COMPILERS.joinpath("ee-gcc2.96").rglob("cpp0"))
        script = (
            f"ld=$(dirname {I386_LIBS})/ld-linux.so.2; "
            f'[ -e "$ld" ] || ld={I386_LIBS}/ld-linux.so.2; '
            'work=$(mktemp -d); cp "$1" "$work/in.c"; '
            f'"$ld" --library-path {I386_LIBS} "$0" -P -nostdinc -DPERMUTER "$work/in.c"; '
            'status=$?; rm -rf "$work"; exit $status'
        )
        return subprocess.check_output(
            ["wsl", "-e", "bash", "-c", script, wsl_path(cpp0), wsl_path(Path(filename))],
            text=True,
            encoding="utf-8",
        )

    permuter_main.preprocess = preprocess
    sys.argv = ["permuter.py", str(directory), *extra]
    permuter_main.main()
    return 0


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    sub = parser.add_subparsers(dest="command", required=True)
    p = sub.add_parser("setup")
    p.add_argument("c_file", type=Path)
    p.add_argument("function")
    p.add_argument("--module", default="GAMECORE")
    p.add_argument("--out", type=Path)
    p = sub.add_parser("run")
    p.add_argument("directory", type=Path)
    p.add_argument("permuter_args", nargs=argparse.REMAINDER)
    p = sub.add_parser("objdump")
    p.add_argument("args", nargs="+")
    args = parser.parse_args(argv)
    if args.command == "setup":
        setup(args.c_file, args.function, args.module.upper(),
              args.out or ROOT / "build/permuter" / args.function)  # fmt: skip
        return 0
    if args.command == "objdump":
        return objdump(args.args[-1])
    return run(args.directory, args.permuter_args)


if __name__ == "__main__":
    sys.exit(main())
