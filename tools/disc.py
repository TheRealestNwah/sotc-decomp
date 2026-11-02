"""Read files out of a Disc image (ISO 9660, 2048-byte sectors).

Only what reference runs need: find a file by its path and read it, so a run's
Disc image can be checked against the Loader and Game modules this repo
matches. Paths ignore case and the ";1" version suffix.
"""

from __future__ import annotations

import struct
from pathlib import Path
from typing import BinaryIO

SECTOR = 2048
PVD_SECTOR = 16


def _records(f: BinaryIO, lba: int, size: int):
    f.seek(lba * SECTOR)
    data = f.read(size)
    pos = 0
    while pos < len(data):
        length = data[pos]
        if length == 0:  # records never straddle a sector; skip to the next one
            pos = (pos // SECTOR + 1) * SECTOR
            continue
        rec = data[pos : pos + length]
        extent, extent_size = (
            struct.unpack_from("<I", rec, 2)[0],
            struct.unpack_from("<I", rec, 10)[0],
        )
        flags, name_len = rec[25], rec[32]
        name = rec[33 : 33 + name_len].decode("ascii", "replace")
        yield name, extent, extent_size, bool(flags & 2)
        pos += length


def _root(f: BinaryIO) -> tuple[int, int]:
    f.seek(PVD_SECTOR * SECTOR)
    pvd = f.read(SECTOR)
    if pvd[0] != 1 or pvd[1:6] != b"CD001":
        raise ValueError("not an ISO 9660 Disc image (no primary volume descriptor)")
    root = pvd[156 : 156 + 34]
    return struct.unpack_from("<I", root, 2)[0], struct.unpack_from("<I", root, 10)[0]


def find(f: BinaryIO, path: str) -> tuple[int, int]:
    """Return (lba, size) of the file at `path`, e.g. "SCUS_974.72"."""
    lba, size = _root(f)
    parts = [p for p in path.replace("\\", "/").upper().split("/") if p]
    for i, part in enumerate(parts):
        last = i == len(parts) - 1
        for name, extent, extent_size, is_dir in _records(f, lba, size):
            if name.split(";")[0].upper() == part and is_dir != last:
                lba, size = extent, extent_size
                break
        else:
            raise FileNotFoundError(path)
    return lba, size


def read_file(image: Path, path: str) -> bytes:
    with image.open("rb") as f:
        lba, size = find(f, path)
        f.seek(lba * SECTOR)
        return f.read(size)
