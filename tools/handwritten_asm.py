"""List and check the Handwritten asm functions (ADR 0017).

config/handwritten_asm.txt names each function written in assembly by hand,
with its size, a signature and the evidence that gcc 2.96 couldn't have
produced it. The signature is computed as for SDK routines
(tools/sdk_routines.py): the first 16 hex digits of the SHA-1 of the code with
every relocated field zeroed. These functions stay in the build as generated
asm, so the check only makes sure the list still names the Original's code.

    python tools/handwritten_asm.py                          # check every entry
    python tools/handwritten_asm.py --print MANAGER func_0001E9C0 -- "evidence"

Game module entries need the Original Game modules in iso/ (and, for
Placeholder names, the generated asm/); LOADER entries need iso/SCUS_974.72
and config/loader_functions.csv. tools/progress.py leaves the listed functions
out of the Game code totals.
"""

from __future__ import annotations

import argparse
import csv
import sys
from dataclasses import dataclass
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))

from tools.progress import HANDWRITTEN_ASM, LOADER_FUNCTIONS_CSV  # noqa: E402
from tools.sdk_routines import ModuleCode, signature  # noqa: E402

LOADER = "LOADER"


@dataclass(frozen=True)
class Entry:
    module: str
    name: str
    size: int
    signature: str
    evidence: str

    def line(self) -> str:
        return f"{self.module} {self.name} {self.size:#x} {self.signature} {self.evidence}"


def parse_list(text: str) -> list[Entry]:
    entries = []
    for line in text.splitlines():
        line = line.split("#", 1)[0].strip()
        if line:
            module, name, size, sig, evidence = line.split(None, 4)
            entries.append(Entry(module, name, int(size, 0), sig, evidence))
    return entries


def elf_bytes(elf_path: Path, address: int, size: int) -> bytes:
    """`size` bytes at virtual `address` of a linked ELF's loaded segments."""
    from elftools.elf.elffile import ELFFile

    with elf_path.open("rb") as f:
        elf = ELFFile(f)
        for segment in elf.iter_segments():
            start = segment["p_vaddr"]
            if segment["p_type"] == "PT_LOAD" and start <= address < start + segment["p_filesz"]:
                data = segment.data()
                return data[address - start : address - start + size]
    raise KeyError(f"{LOADER}: address {address:#x} isn't loaded from {elf_path}")


def loader_function(csv_path: Path, elf_path: Path, name: str) -> tuple[int, str]:
    """Size and signature of a Loader function. The Loader is linked, so its
    code has no relocations left to zero."""
    with csv_path.open(encoding="utf-8", newline="") as f:
        rows = {row["name"]: row for row in csv.DictReader(f)}
    if name not in rows:
        raise KeyError(f"{LOADER}: no function {name}")
    address, size = int(rows[name]["address"], 16), int(rows[name]["size"], 16)
    return size, signature(elf_bytes(elf_path, address, size), {})


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument("--iso-dir", type=Path, default=REPO / "iso")
    parser.add_argument("--asm-dir", type=Path, default=REPO / "asm" / "xff")
    parser.add_argument("--list", type=Path, default=HANDWRITTEN_ASM)
    parser.add_argument(
        "--print", nargs="+", metavar="ARG", help="MODULE NAME EVIDENCE...: print a new list line"
    )
    args = parser.parse_args(argv)
    modules: dict[str, ModuleCode] = {}

    def find(module: str, name: str) -> tuple[int, str]:
        if module == LOADER:
            return loader_function(LOADER_FUNCTIONS_CSV, args.iso_dir / "SCUS_974.72", name)
        if module not in modules:
            modules[module] = ModuleCode(
                args.iso_dir / f"{module}.XFF", args.asm_dir / module / "text.s"
            )
        routine = modules[module].routine(module, name, "-")
        return routine.size, routine.signature

    if args.print:
        if len(args.print) < 3:
            parser.error("--print needs MODULE NAME EVIDENCE...")
        module, name, *evidence = args.print
        size, sig = find(module, name)
        print(Entry(module, name, size, sig, " ".join(evidence)).line())
        return 0

    listed = parse_list(args.list.read_text(encoding="utf-8"))
    bad = 0
    for entry in listed:
        try:
            size, sig = find(entry.module, entry.name)
        except KeyError as e:
            print(e.args[0])
            bad += 1
            continue
        if (size, sig) != (entry.size, entry.signature):
            print(
                f"{entry.module} {entry.name}: listed {entry.size:#x} {entry.signature}, "
                f"found {size:#x} {sig}"
            )
            bad += 1
    print(f"{len(listed) - bad} of {len(listed)} Handwritten asm functions match")
    return 1 if bad else 0


if __name__ == "__main__":
    raise SystemExit(main())
