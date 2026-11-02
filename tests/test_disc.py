import struct

import pytest

from tools import disc

SECTOR = disc.SECTOR


def record(name: bytes, lba: int, size: int, is_dir: bool) -> bytes:
    length = 33 + len(name) + (len(name) + 1) % 2
    rec = bytearray(length)
    rec[0] = length
    struct.pack_into("<I", rec, 2, lba)
    struct.pack_into(">I", rec, 6, lba)
    struct.pack_into("<I", rec, 10, size)
    struct.pack_into(">I", rec, 14, size)
    rec[25] = 2 if is_dir else 0
    rec[32] = len(name)
    rec[33 : 33 + len(name)] = name
    return bytes(rec)


def make_image(tmp_path):
    image = bytearray(SECTOR * 24)
    pvd = bytearray(SECTOR)
    pvd[0:6] = b"\x01CD001"
    pvd[156 : 156 + 34] = record(b"\0", 18, SECTOR, True)
    image[16 * SECTOR : 17 * SECTOR] = pvd
    root = record(b"\0", 18, SECTOR, True) + record(b"\1", 18, SECTOR, True)
    root += record(b"SCUS_974.72;1", 20, 5, False) + record(b"MODULES", 19, SECTOR, True)
    image[18 * SECTOR : 18 * SECTOR + len(root)] = root
    sub = record(b"KERNEL.XFF;1", 21, 3, False)
    image[19 * SECTOR : 19 * SECTOR + len(sub)] = sub
    image[20 * SECTOR : 20 * SECTOR + 5] = b"hello"
    image[21 * SECTOR : 21 * SECTOR + 3] = b"xff"
    path = tmp_path / "disc.iso"
    path.write_bytes(bytes(image))
    return path


def test_reads_files_by_path(tmp_path):
    image = make_image(tmp_path)
    assert disc.read_file(image, "scus_974.72") == b"hello"
    assert disc.read_file(image, "MODULES/KERNEL.XFF") == b"xff"
    with pytest.raises(FileNotFoundError):
        disc.read_file(image, "MISSING.BIN")


def test_rejects_non_iso(tmp_path):
    path = tmp_path / "x.iso"
    path.write_bytes(bytes(SECTOR * 17))
    with pytest.raises(ValueError):
        disc.read_file(path, "SCUS_974.72")
