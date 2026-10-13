"""Flatten an ELF's loadable sections into a raw image, like
`objcopy -O binary --gap-fill=0x00`.

splat works on this flat image. Doing it in Python means splitting doesn't
depend on having binutils installed. It also accepts objcopy-style arguments,
so it can be passed to `splat create_config --objcopy`.
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from elftools.elf.constants import SH_FLAGS
from elftools.elf.elffile import ELFFile


def loadable_sections(elf: ELFFile) -> list[tuple[int, bytes]]:
    """(address, contents) of every allocated section that occupies file space."""
    sections = []
    for section in elf.iter_sections():
        if not section["sh_flags"] & SH_FLAGS.SHF_ALLOC:
            continue
        if section["sh_type"] == "SHT_NOBITS" or section["sh_size"] == 0:
            continue
        sections.append((section["sh_addr"], section.data()))
    return sorted(sections)


def flatten(elf_path: Path, gap_fill: int = 0) -> bytes:
    with elf_path.open("rb") as f:
        sections = loadable_sections(ELFFile(f))
    if not sections:
        raise ValueError(f"{elf_path} has no loadable sections")

    base = sections[0][0]
    end = max(addr + len(data) for addr, data in sections)
    image = bytearray([gap_fill]) * (end - base)
    for addr, data in sections:
        image[addr - base : addr - base + len(data)] = data
    return bytes(image)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("-O", dest="output_format", default="binary")
    parser.add_argument("--gap-fill", default="0x00")
    parser.add_argument("--version", action="store_true")
    parser.add_argument("elf", nargs="?", type=Path)
    parser.add_argument("output", nargs="?", type=Path)
    args = parser.parse_args(argv)

    if args.version:
        print("elf2rom (objcopy -O binary stand-in)")
        return 0
    if args.output_format != "binary" or args.elf is None or args.output is None:
        parser.error("usage: elf2rom.py [-O binary] [--gap-fill=N] ELF OUTPUT")

    args.output.write_bytes(flatten(args.elf, int(args.gap_fill, 0)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
