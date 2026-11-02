"""List and check the SDK routines identified in the Game modules.

config/sdk_routines.txt names each SDK routine (Sony SDK library or toolchain
libc/libm code linked into a Game module) with its library, size and signature.
The signature is the first 16 hex digits of the SHA-1 of the routine's
instruction words with every relocated field zeroed, so it doesn't depend on
where the module or its imports end up. It identifies the code without
reproducing it; no SDK library file is ever needed or kept in the repo.

    python tools/sdk_routines.py                       # check every listed routine
    python tools/sdk_routines.py --print KERNEL libcdvd sceCdRead sceCdStatus

--print writes list lines for new routines. Both need the Original Game modules
in iso/ (and, for routines with Placeholder names, the generated asm/).
tools/progress.py leaves the listed routines out of the Game code totals.
"""

from __future__ import annotations

import argparse
import hashlib
import io
import sys
from dataclasses import dataclass
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))

from tools.progress import (  # noqa: E402
    SDK_ROUTINES,
    STT_FUNC,
    label_addresses,
    module_functions,
    read_module,
)

R_MIPS_32, R_MIPS_26 = 2, 4
# Bits of an instruction word each relocation type fills in.
RELOC_MASKS = {R_MIPS_32: 0xFFFFFFFF, R_MIPS_26: 0x03FFFFFF}
FIELD16 = 0x0000FFFF  # HI16, LO16, GPREL16


@dataclass(frozen=True)
class Routine:
    module: str
    name: str
    library: str
    size: int
    signature: str

    def line(self) -> str:
        return f"{self.module} {self.name} {self.library} {self.size:#x} {self.signature}"


def parse_list(text: str) -> list[Routine]:
    routines = []
    for line in text.splitlines():
        line = line.split("#", 1)[0].strip()
        if line:
            module, name, library, size, signature = line.split()
            routines.append(Routine(module, name, library, int(size, 0), signature))
    return routines


def signature(code: bytes, relocs: dict[int, int]) -> str:
    """Signature of a routine's code. `relocs` maps word offsets within it to
    relocation types."""
    words = bytearray(code)
    for offset, reloc_type in relocs.items():
        word = int.from_bytes(words[offset : offset + 4], "little")
        word &= ~RELOC_MASKS.get(reloc_type, FIELD16) & 0xFFFFFFFF
        words[offset : offset + 4] = word.to_bytes(4, "little")
    return hashlib.sha1(bytes(words)).hexdigest()[:16]


def function_extents(
    starts: dict[str, int], sizes: dict[str, int], text_size: int
) -> dict[str, tuple[int, int]]:
    """(start, size) of each function: a named symbol's own size, otherwise up to
    the next function."""
    ordered = sorted(set(starts.values())) + [text_size]
    extents = {}
    for name, start in starts.items():
        following = next(a for a in ordered if a > start)
        extents[name] = (start, sizes.get(name) or following - start)
    return extents


class ModuleCode:
    """A Game module's .text, relocations and function extents."""

    def __init__(self, xff: Path, asm: Path | None):
        from elftools.elf.elffile import ELFFile

        from tools.xff2 import parse, to_elf
        from tools.xff_split import read_relocs

        module = parse(xff.read_bytes())
        text = module.index_of(".text")
        self.code = module.sections[text].data
        sizes = {}
        for i in range(1, module.num_symbols):
            _, _, size, info, _, shndx = module.symbol(i)
            if info & 0xF == STT_FUNC and shndx == text:
                sizes[module.symbol_name(i)] = size
        named, targets = read_module(xff)
        starts = dict(named)
        if asm is not None and asm.exists():
            labels = label_addresses(asm.read_text(encoding="latin-1"))
            base = next(labels[n] - v for n, v in named.items() if n in labels)
            for name in module_functions(named, labels, targets) - set(named):
                starts[name] = labels[name] - base
        self.extents = function_extents(starts, sizes, len(self.code))
        elf = ELFFile(io.BytesIO(to_elf(module)))
        self.relocs = {o: r.type for o, r in read_relocs(elf, ".text").items()}

    def routine(self, module: str, name: str, library: str) -> Routine:
        if name not in self.extents:
            raise KeyError(f"{module}: no function {name}")
        start, size = self.extents[name]
        relocs = {o - start: t for o, t in self.relocs.items() if start <= o < start + size}
        code = self.code[start : start + size]
        return Routine(module, name, library, size, signature(code, relocs))


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument("--iso-dir", type=Path, default=REPO / "iso")
    parser.add_argument("--asm-dir", type=Path, default=REPO / "asm" / "xff")
    parser.add_argument("--list", type=Path, default=SDK_ROUTINES)
    parser.add_argument(
        "--print", nargs="+", metavar="ARG", help="MODULE LIBRARY NAME...: print new list lines"
    )
    args = parser.parse_args(argv)
    modules: dict[str, ModuleCode] = {}

    def code(module: str) -> ModuleCode:
        if module not in modules:
            modules[module] = ModuleCode(
                args.iso_dir / f"{module}.XFF", args.asm_dir / module / "text.s"
            )
        return modules[module]

    if args.print:
        if len(args.print) < 3:
            parser.error("--print needs MODULE LIBRARY NAME...")
        module, library, *names = args.print
        for name in names:
            print(code(module).routine(module, name, library).line())
        return 0

    listed = parse_list(args.list.read_text(encoding="utf-8"))
    bad = 0
    for entry in listed:
        try:
            found = code(entry.module).routine(entry.module, entry.name, entry.library)
        except KeyError as e:
            print(e.args[0])
            bad += 1
            continue
        if found != entry:
            print(f"{entry.module} {entry.name}: listed {entry.line()}, found {found.line()}")
            bad += 1
    print(f"{len(listed) - bad} of {len(listed)} SDK routines match")
    return 1 if bad else 0


if __name__ == "__main__":
    raise SystemExit(main())
