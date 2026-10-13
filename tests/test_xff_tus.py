import io
import struct

from elftools.elf.elffile import ELFFile

from tools.xff2 import (
    SHT_PROGBITS,
    SHT_REL,
    SHT_STRTAB,
    SHT_SYMTAB,
    Module,
    RelTable,
    Section,
    to_elf,
)
from tools.xff_tus import infer, source_names

NAMES = ["", ".text", ".rel.text", ".rodata", ".shstrtab", ".symtab", ".strtab"]
JAL = 0x0C000000


def sym(name: int, value: int, size: int, info: int, shndx: int) -> bytes:
    return struct.pack("<IIIBBH", name, value, size, info, 0, shndx)


def build() -> ELFFile:
    """Four 8-byte functions:
    f0 (global), f1 calls f0 section-relative (same file),
    f2 calls f0 by name (other file) and loads a string naming foo.c, f3 is alone."""
    shstrtab, offs = b"\0", [0]
    for name in NAMES[1:]:
        offs.append(len(shstrtab))
        shstrtab += name.encode() + b"\0"
    strtab = b"\0f0\0f1\0f2\0f3\0"
    symbols = b"".join(
        [
            bytes(16),
            sym(0, 0, 0, 0x03, 1),  # 1: .text section symbol
            sym(0, 0, 0, 0x03, 3),  # 2: .rodata section symbol
            sym(1, 0x00, 8, 0x12, 1),  # 3: f0 global func
            sym(4, 0x08, 8, 0x02, 1),  # 4: f1 local func
            sym(7, 0x10, 8, 0x12, 1),  # 5: f2 global func
            sym(10, 0x18, 8, 0x12, 1),  # 6: f3 global func
        ]
    )
    text = struct.pack("<8I", 0, 0, JAL | 0, 0, JAL, 0x3C040000, 0x24840004, 0)
    rodata = b"\0\0\0\0src/foo.c: bad\0"
    sections = [
        Section(0, 0, 0, 0),
        Section(offs[1], SHT_PROGBITS, len(text), 8, text),
        Section(offs[2], SHT_REL, 32, 4),
        Section(offs[3], SHT_PROGBITS, len(rodata), 16, rodata),
        Section(offs[4], SHT_STRTAB, len(shstrtab), 1),
        Section(offs[5], SHT_SYMTAB, len(symbols), 4, symbols),
        Section(offs[6], SHT_STRTAB, len(strtab), 1),
    ]
    word = lambda off: struct.unpack_from("<I", text, off)[0]  # noqa: E731
    locals_ = [
        (0x08, (1 << 8) | 4, word(0x08), 0),  # f1: jal .text+0 (f0), same file
        (0x10, (3 << 8) | 4, word(0x10), 0),  # f2: jal f0 by name, other file
        (0x14, (2 << 8) | 5, word(0x14), 0),  # f2: %hi(.rodata+4)
        (0x18, (2 << 8) | 6, word(0x18), 0),  # %lo(.rodata+4), in f3's range
    ]
    module = Module(
        sections=sections,
        shstrtab=shstrtab,
        strtab=strtab,
        symbols=symbols,
        reltables=[RelTable(1, True, []), RelTable(1, False, locals_)],
        imports=[],
        entry=0,
        num_locals=4,
    )
    return ELFFile(io.BytesIO(to_elf(module)))


def test_source_names_key_by_containing_string():
    rodata = b"\0\0\0\0src/foo.c: bad\0other\0C:\\x\\bar.cpp\0"
    assert source_names(rodata) == {4: "foo.c", 25: "bar.cpp"}


def test_infer_groups_and_evidence():
    result = infer(build())
    groups = [(g.first, g.last) for g in result.groups]
    assert groups == [(0, 1), (2, 2), (3, 3)]
    assert result.same_file_links == 1
    assert result.cross_file_links == 1
    assert result.conflicts == []
    # f3's %lo pairs with f2's %hi: the string at .rodata+4 names f3's group.
    assert result.groups[2].names == {"foo.c"}
