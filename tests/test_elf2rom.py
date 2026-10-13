import struct

from tools.elf2rom import flatten, main

SHF_ALLOC = 0x2
SHT_PROGBITS = 1
SHT_STRTAB = 3
SHT_NOBITS = 8


def build_elf(sections: list[tuple[str, int, int, int, bytes | int]]) -> bytes:
    """Minimal little-endian ELF32 MIPS file.

    Each section is (name, sh_type, sh_flags, addr, data or NOBITS size).
    """
    names = b"\0" + b"".join(s[0].encode() + b"\0" for s in sections) + b".shstrtab\0"
    body = bytearray()
    headers = [bytes(40)]  # null section
    offset = 52
    name_offset = 1
    for name, sh_type, flags, addr, data in sections:
        size = data if isinstance(data, int) else len(data)
        if not isinstance(data, int):
            body += data
        headers.append(
            struct.pack("<10I", name_offset, sh_type, flags, addr, offset, size, 0, 0, 4, 0)
        )
        if not isinstance(data, int):
            offset += len(data)
        name_offset += len(name) + 1
    headers.append(
        struct.pack("<10I", name_offset, SHT_STRTAB, 0, 0, offset, len(names), 0, 0, 1, 0)
    )
    body += names
    shoff = 52 + len(body)
    ident = b"\x7fELF\x01\x01\x01" + bytes(9)
    header = ident + struct.pack(
        "<HHIIIIIHHHHHH",
        2,
        8,
        1,
        0x100000,
        0,
        shoff,
        0,
        52,
        32,
        0,
        40,
        len(headers),
        len(headers) - 1,
    )
    return header + bytes(body) + b"".join(headers)


def test_flatten_fills_gaps_and_skips_nobits(tmp_path):
    elf = tmp_path / "test.elf"
    elf.write_bytes(
        build_elf(
            [
                (".text", SHT_PROGBITS, SHF_ALLOC, 0x100000, b"\x01\x02\x03\x04"),
                (".data", SHT_PROGBITS, SHF_ALLOC, 0x100008, b"\xaa\xbb"),
                (".bss", SHT_NOBITS, SHF_ALLOC, 0x100010, 0x100),
                (".comment", SHT_PROGBITS, 0, 0, b"not loaded"),
            ]
        )
    )
    assert flatten(elf) == b"\x01\x02\x03\x04\x00\x00\x00\x00\xaa\xbb"
    assert flatten(elf, gap_fill=0xFF)[4:8] == b"\xff" * 4


def test_main_accepts_objcopy_style_arguments(tmp_path):
    elf = tmp_path / "test.elf"
    elf.write_bytes(build_elf([(".text", SHT_PROGBITS, SHF_ALLOC, 0x100000, b"\x01\x02")]))
    out = tmp_path / "out.rom"
    assert main(["-O", "binary", "--gap-fill=0x00", str(elf), str(out)]) == 0
    assert out.read_bytes() == b"\x01\x02"
    assert main(["--version"]) == 0
