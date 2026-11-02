"""Sort the Loader's functions into Game code and SDK routines (ADR 0004).

    python tools/loader_funcs.py            # summary
    python tools/loader_funcs.py --write    # rewrite config/loader_functions.csv
    python tools/loader_funcs.py --check    # fail if the checked-in list is stale

Inputs: the splat disassembly of the Loader (asm/cod/000000.s) for function
starts and instruction words, and KERNEL.XFF from the Original disc. KERNEL
links against the Loader, so its symbol table carries SHN_ABS entries naming
845 Loader functions with their Original names and sizes. No Sony library
file is read.

Classification follows the Loader's link order. The game's own objects come
first (the xff loader, LoaderSys* services, padSys*, usbSerialSys*, the debug
font and display), then the SDK libraries the Loader links: libkernl syscall
stubs from RFU000_FullReset on, then sif/fileio/tty, libpkt, libgraph, libdma,
libpad2, libvib, libdbc, libcdvd, libinet/libnet, libmrpc, libmc2, netcnfif,
libgcc and newlib, and the handwritten cache routines. crt0 sits at the very
start. Each library is a contiguous block, so a function with no Original
name takes the library of the named block it sits in.
"""

from __future__ import annotations

import argparse
import bisect
import csv
import io
import re
import sys
from dataclasses import dataclass
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from tools.xff2 import parse  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
ASM = ROOT / "asm/cod/000000.s"
KERNEL = ROOT / "iso/KERNEL.XFF"
LIST = ROOT / "config/loader_functions.csv"

SHN_ABS = 0xFFF1
STT_FUNC = 2

GAME = "game"
SDK = "sdk"

# (first address, class, library). Each block runs to the next one's start.
# The addresses are the first named function of each block.
BLOCKS = [
    (0x100000, GAME, "loader"),  # two-word pointer table before crt0
    (0x100010, SDK, "crt0"),  # _start and its exit stubs
    (0x1000D0, GAME, "loader"),  # ResolveRelocation .. PutChar
    (0x106BC0, SDK, "libkernl"),  # RFU000_FullReset: syscall stubs, sif, fileio, tty
    (0x113078, SDK, "libpkt"),  # sceVif1Pk*
    (0x113390, SDK, "libgraph"),  # sceGs*
    (0x114918, SDK, "libdma"),  # sceDma*
    (0x115008, SDK, "libpad2"),  # scePad2*
    (0x1158C0, SDK, "libvib"),  # sceVib*
    (0x115A88, SDK, "libdbc"),  # sceDbc*
    (0x116C80, SDK, "libcdvd"),  # sceCd*
    (0x1185A8, SDK, "libinet"),  # sceInet*
    (0x119288, SDK, "libnet"),  # sceLibnet*
    (0x1198B8, SDK, "libmrpc"),  # sceSifM*
    (0x11A188, SDK, "libmc2"),  # sceMc2*, _sceMcFat*, _sceMcp*, _sceMcCore*
    (0x122128, SDK, "netcnfif"),  # sceNetcnfif*
    (0x123380, SDK, "libgcc"),  # __divdi3 .. __pack_f, dp*, frame unwind
    (0x127448, SDK, "libc"),  # newlib: abort .. _realloc_r
    (0x131818, SDK, "libkernl"),  # _sceSDC, SyncDCache, InvalidDCache
    (0x131A98, SDK, "libgcc"),  # __fixdfdi, dptoli
]

FUNC_RE = re.compile(r"^nonmatching (\S+), 0x([0-9A-F]+)", re.M)
WORD_RE = re.compile(r"^\s*/\* [0-9A-F]+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/", re.M)
GLABEL_RE = re.compile(r"^glabel (\S+)\n\s*/\* [0-9A-F]+ ([0-9A-F]{8})", re.M)


@dataclass
class Function:
    address: int
    size: int
    name: str
    cls: str
    library: str
    note: str


def splat_functions(asm: str) -> tuple[list[tuple[int, int, str]], dict[int, int]]:
    """Function (address, size, name) list and address -> instruction word,
    both read from the splat disassembly. Words are printed little-endian."""
    sizes = {m.group(1): int(m.group(2), 16) for m in FUNC_RE.finditer(asm)}
    starts = {m.group(1): int(m.group(2), 16) for m in GLABEL_RE.finditer(asm)}
    funcs = sorted((starts[n], sizes[n], n) for n in sizes if n in starts)
    words = {
        int(m.group(1), 16): int.from_bytes(bytes.fromhex(m.group(2)), "little")
        for m in WORD_RE.finditer(asm)
    }
    return funcs, words


def original_functions(kernel: bytes, lo: int, hi: int) -> dict[int, tuple[int, str]]:
    """address -> (size, Original name) for KERNEL's absolute function
    symbols that point into the Loader's code [lo, hi)."""
    m = parse(kernel)
    out = {}
    for i in range(1, m.num_symbols):
        _, value, size, info, _, shndx = m.symbol(i)
        if shndx == SHN_ABS and info & 0xF == STT_FUNC and lo <= value < hi:
            out[value] = (size, m.symbol_name(i))
    return out


def classify(address: int) -> tuple[str, str]:
    i = bisect.bisect_right([b[0] for b in BLOCKS], address) - 1
    if i < 0:
        raise ValueError(f"{address:#x} is before the Loader's code")
    return BLOCKS[i][1], BLOCKS[i][2]


def build(
    splat: list[tuple[int, int, str]],
    words: dict[int, int],
    original: dict[int, tuple[int, str]],
) -> list[Function]:
    """One row per function. Starts come from splat and from the Original
    symbols, which also mark code splat merged into its neighbour. When an
    Original function ends before splat's does and real code follows, that
    code gets its own placeholder row."""
    end = max(a + s for a, s, _ in splat)
    starts = {a: n for a, _, n in splat}
    splat_end = {a: a + s for a, s, _ in splat}
    for addr, (size, _) in original.items():
        tail = addr + size
        if addr in splat_end and tail < splat_end[addr] and tail not in original:
            if any(words.get(a, 0) for a in range(tail, splat_end[addr], 4)):
                starts.setdefault(tail, f"func_{tail:08X}")
    for addr in original:
        starts.setdefault(addr, f"func_{addr:08X}")

    addrs = sorted(starts)
    rows = []
    for i, addr in enumerate(addrs):
        nxt = addrs[i + 1] if i + 1 < len(addrs) else end
        cls, lib = classify(addr)
        if addr in original:
            size, name = original[addr]
            note = "Original name (KERNEL.XFF absolute symbol)"
            if addr not in splat_end:
                note += "; splat merged it into the function before"
        else:
            size, name = nxt - addr, starts[addr]
            note = "no Original name; class from its block"
            if not name.startswith("func_"):
                note = "named in symbol_addrs.txt; class from its block"
        rows.append(Function(addr, size, name, cls, lib, note))
    return rows


def to_csv(rows: list[Function]) -> str:
    buf = io.StringIO()
    w = csv.writer(buf, lineterminator="\n")
    w.writerow(["address", "size", "name", "class", "library", "evidence"])
    for r in rows:
        w.writerow([f"0x{r.address:08X}", f"0x{r.size:X}", r.name, r.cls, r.library, r.note])
    return buf.getvalue()


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--write", action="store_true", help=f"write {LIST.relative_to(ROOT)}")
    g.add_argument("--check", action="store_true", help="fail if the list is stale")
    ap.add_argument("--asm", type=Path, default=ASM, help="splat disassembly of the Loader")
    ap.add_argument("--kernel", type=Path, default=KERNEL, help="KERNEL.XFF from the Original")
    args = ap.parse_args()

    splat, words = splat_functions(args.asm.read_text(encoding="latin-1"))
    lo, hi = splat[0][0], max(a + s for a, s, _ in splat)
    rows = build(splat, words, original_functions(args.kernel.read_bytes(), lo, hi))
    text = to_csv(rows)

    if args.write:
        LIST.write_text(text, encoding="utf-8", newline="\n")
    elif args.check:
        if not LIST.exists() or LIST.read_text(encoding="utf-8") != text:
            print(f"{LIST.relative_to(ROOT)} is stale; run tools/loader_funcs.py --write")
            return 1

    named = sum(r.note.startswith("Original") for r in rows)
    for cls in (GAME, SDK):
        part = [r for r in rows if r.cls == cls]
        print(f"{cls:5} {len(part):5} functions  0x{sum(r.size for r in part):06X} bytes")
    print(f"total {len(rows):5} functions, {named} with Original names, {len(splat)} from splat")
    return 0


if __name__ == "__main__":
    sys.exit(main())
