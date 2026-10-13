import struct

import pytest

from tools.xff2 import (
    SHT_NOBITS,
    SHT_PROGBITS,
    SHT_REL,
    SHT_RELA,
    SHT_STRTAB,
    SHT_SYMTAB,
    Module,
    RelTable,
    Section,
    from_elf,
    main,
    parse,
    to_elf,
    write,
)

SECTION_NAMES = [
    "", ".text", ".rel.text", ".rela.text", ".data", ".rel.data", ".bss",
    ".shstrtab", ".symtab", ".strtab",
]  # fmt: skip


def make_shstrtab() -> tuple[bytes, list[int]]:
    table, offsets = b"\0", [0]
    for name in SECTION_NAMES[1:]:
        offsets.append(len(table))
        table += name.encode() + b"\0"
    return table, offsets


def sym(name: int, value: int, size: int, info: int, shndx: int) -> bytes:
    return struct.pack("<IIIBBH", name, value, size, info, 0, shndx)


def make_module() -> Module:
    """A small module: two functions, one data word, one import."""
    shstrtab, offs = make_shstrtab()
    strtab = b"\0local_fn\0entry\0imported\0"
    symbols = b"".join(
        [
            bytes(16),
            sym(0, 0, 0, 0x03, 1),  # .text section symbol
            sym(1, 0x0, 8, 0x02, 1),  # local_fn (local func)
            sym(10, 0x8, 16, 0x12, 1),  # entry (global func)
            sym(16, 0x1234, 0, 0x10, 0),  # imported (undefined, odd value kept)
        ]
    )
    text = bytes.fromhex("0000043c000084240000000c000000000800e003000000000000000000000000")
    data = struct.pack("<I", 0x10)
    sections = [
        Section(0, 0, 0, 0),
        Section(offs[1], SHT_PROGBITS, len(text), 8, text),
        Section(offs[2], SHT_REL, 32, 4),
        Section(offs[3], SHT_RELA, 0, 4),
        Section(offs[4], SHT_PROGBITS, len(data), 16, data),
        Section(offs[5], SHT_REL, 8, 4),
        Section(offs[6], SHT_NOBITS, 0x40, 16),
        Section(offs[7], SHT_STRTAB, len(shstrtab), 1),
        Section(offs[8], SHT_SYMTAB, len(symbols), 4, symbols),
        Section(offs[9], SHT_STRTAB, len(strtab), 1),
    ]
    word = lambda off: struct.unpack_from("<I", text, off)[0]  # noqa: E731
    reltables = [
        RelTable(1, True, [(0x8, (4 << 8) | 4, word(0x8), 0x305)]),
        RelTable(4, True, []),
        RelTable(
            1,
            False,
            [
                (0x0, (1 << 8) | 5, word(0x0), 0),
                (0x4, (1 << 8) | 6, word(0x4), 0),
                (0x10, (2 << 8) | 4, word(0x10), 0),
            ],
        ),  # fmt: skip
        RelTable(4, False, [(0x0, (1 << 8) | 2, 0x10, 0)]),
    ]
    return Module(
        sections=sections,
        shstrtab=shstrtab,
        strtab=strtab,
        symbols=symbols,
        reltables=reltables,
        imports=[4],
        entry=0x8,
        num_locals=2,
    )


def test_write_then_parse_is_lossless():
    module = make_module()
    data = write(module)
    assert data[:4] == b"xff2"
    assert struct.unpack_from("<I", data, 0x14)[0] == len(data)
    assert write(parse(data)) == data
    parsed = parse(data)
    assert parsed.entry == 0x8
    assert parsed.imports == [4]
    assert parsed.symbol_name(3) == "entry"


def test_header_pointers_are_offsets_plus_base():
    data = write(make_module())
    header = struct.unpack_from("<28I", data, 0)
    pointers = [header[i] for i in (8, 10, 11, 12, 13, 15, 17, 18)]
    assert [p - 0x40010000 for p in pointers] == list(header[20:28])


def test_elf_round_trip_is_byte_identical():
    original = write(make_module())
    assert write(from_elf(to_elf(parse(original)))) == original


def test_elf_has_relocations_and_symbols():
    from io import BytesIO

    from elftools.elf.elffile import ELFFile

    elf = ELFFile(BytesIO(to_elf(make_module())))
    assert elf.header.e_type == "ET_REL"
    rel = elf.get_section_by_name(".rel.text")
    assert rel.num_relocations() == 4
    names = [s.name for s in elf.get_section_by_name(".symtab").iter_symbols()]
    assert names[2:] == ["local_fn", "entry", "imported"]


def test_mixed_reloc_table_is_rejected():
    module = make_module()
    module.reltables[0].entries.append((0x0, (1 << 8) | 5, 0, 0))
    with pytest.raises(ValueError, match="mixes"):
        parse(write(module))


def test_cli_roundtrip(tmp_path, capsys):
    path = tmp_path / "TEST.XFF"
    path.write_bytes(write(make_module()))
    assert main(["roundtrip", str(path)]) == 0
    assert "OK" in capsys.readouterr().out
    assert main(["to-elf", str(path), str(tmp_path / "t.o")]) == 0
    assert main(["from-elf", str(tmp_path / "t.o"), str(tmp_path / "T2.XFF")]) == 0
    assert (tmp_path / "T2.XFF").read_bytes() == path.read_bytes()
    assert main(["info", str(path)]) == 0
