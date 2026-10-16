import pytest

from tools.xff_split import (
    Fixups,
    Reloc,
    SectionAsm,
    add_twins,
    global_aliases,
    label_addresses,
    postprocess,
    referenced_address,
    sext16,
)

BASE = 0x100  # spimdisasm address of the section start


def test_missing_vu_exports_bind_to_emitted_section_offsets():
    sections = [SectionAsm(".vutext", [], size=0x40)]
    exports = [
        ("MC_LINE", ".vutext", 0, "STT_NOTYPE"),
        ("MC_SKIN", ".vutext", 0x20, "STT_NOTYPE"),
        ("existing", ".vutext", 8, "STT_FUNC"),
        ("overlay", ".DVP.overlay.test", 0, "STT_NOTYPE"),
    ]
    assert global_aliases(exports, sections, {"existing"}) == {
        "MC_LINE": ['.set "MC_LINE", .Lxff.start.vutext + 0x0'],
        "MC_SKIN": ['.set "MC_SKIN", .Lxff.start.vutext + 0x20'],
    }


@pytest.mark.parametrize("offset", [-1, 0x41])
def test_export_outside_emitted_section_is_rejected(offset):
    with pytest.raises(ValueError, match="outside .vutext"):
        global_aliases(
            [("bad", ".vutext", offset, "STT_NOTYPE")],
            [SectionAsm(".vutext", [], size=0x40)],
            set(),
        )


def test_missing_function_export_retains_its_type_at_section_end():
    assert global_aliases(
        [("end", ".text", 0x40, "STT_FUNC")],
        [SectionAsm(".text", [], size=0x40)],
        set(),
    )["end"] == ['.set "end", .Lxff.start.text + 0x40', '.type "end", @function']


def line(offset: int, raw: str, text: str) -> str:
    address = BASE + offset
    return f"    /* {address:06X} {address:08X} {raw} */  {text}"


def section(lines, data, relocs=None, name=".data"):
    return SectionAsm(name, lines, BASE, len(data), data, relocs or {})


def run(sec, labels=None, bases=None):
    fixups = Fixups()
    labels = labels if labels is not None else label_addresses([sec])
    out, twins, unlabeled = postprocess(sec, labels, bases or {sec.name: BASE}, fixups)
    return out, twins, unlabeled, fixups


def test_sext16():
    assert sext16(0x7FFF) == 0x7FFF
    assert sext16(0x8000) == -0x8000
    assert sext16(0x12345678) == 0x5678


def test_word_without_original_reloc_becomes_plain_value():
    data = bytes.fromhex("25640a00")
    out, _, _, fixups = run(section([line(0, "25640A00", ".word B_000A6425")], data))
    assert out[-1].endswith(".word 0x000A6425")
    assert fixups.plain_words == 1


def test_relocated_plain_word_gets_explicit_reloc():
    data = bytes.fromhex("0000023c")
    relocs = {0: Reloc(5, ".rodata", True, 0x10)}
    out, _, _, fixups = run(section([line(0, "0000023C", ".word 0x3C020000")], data, relocs))
    assert out[0] == "    .reloc ., R_MIPS_HI16, .Lxff.start.rodata"
    assert ".word 0x3C020000" in out[1]
    assert fixups.explicit_relocs == 1


def test_section_relative_reference_uses_local_twin():
    lines = [
        "dlabel D_00000104",
        line(4, "00000000", ".word 0"),
        line(0, "04000000", ".word D_00000104"),
    ]
    data = bytes.fromhex("04000000") + bytes(4)
    relocs = {0: Reloc(2, ".data", True, 4)}
    out, twins, _, _ = run(section(lines, data, relocs))
    assert ".word .Lxff.D_00000104" in out[-1]
    assert twins == {"D_00000104"}
    assert add_twins(["dlabel D_00000104"], twins) == ["dlabel D_00000104", ".Lxff.D_00000104:"]


def test_wrong_address_falls_back_to_explicit_reloc():
    lines = [
        "dlabel D_00000104",
        line(4, "00000000", ".word 0"),
        line(0, "08000000", ".word D_00000104"),
    ]
    data = bytes.fromhex("08000000") + bytes(4)
    relocs = {0: Reloc(2, ".data", True, 8)}  # original points at +8, not +4
    out, twins, _, fixups = run(section(lines, data, relocs))
    assert out[-2] == "    .reloc ., R_MIPS_32, .Lxff.start.data"
    assert out[-1].endswith(".word 0x00000008 /* .word D_00000104 */")
    assert fixups.explicit_relocs == 1 and not twins


def test_dropped_import_addend_falls_back_to_explicit_reloc():
    data = bytes.fromhex("b0020000")
    relocs = {0: Reloc(2, "gcGlobalVar", False, 0x2B0)}
    out, _, _, _ = run(section([line(0, "B0020000", ".word gcGlobalVar")], data, relocs))
    assert out[0] == '    .reloc ., R_MIPS_32, "gcGlobalVar"'


def test_import_with_matching_addend_is_kept():
    data = bytes.fromhex("b0020000")
    relocs = {0: Reloc(2, "gcGlobalVar", False, 0x2B0)}
    out, _, _, _ = run(section([line(0, "B0020000", ".word gcGlobalVar + 0x2B0")], data, relocs))
    assert out == [line(0, "B0020000", ".word gcGlobalVar + 0x2B0")]


def test_branch_to_unlabeled_address_is_resolved_locally():
    data = bytes(4)
    out, _, unlabeled, _ = run(
        section([line(0, "00000000", "bnez $v0, func_00000180")], data, name=".text"),
        bases={".text": BASE},
    )
    assert out[-1].endswith("bnez $v0, .Lxff.func_00000180")
    assert unlabeled == {"func_00000180": (".text", 0x180)}


def test_unaligned_tail_is_emitted_as_bytes():
    data = bytes.fromhex("01020304aabbcc")
    out, _, _, fixups = run(section([line(0, "01020304", ".word 0x04030201")], data))
    assert out[-1] == "    .byte 0xAA, 0xBB, 0xCC"
    assert fixups.tail_bytes == 3


def test_referenced_address_includes_offsets():
    labels = {"sym": (".data", 0x200)}
    assert referenced_address("sym", "%hi(sym + 0x6C)", labels) == 0x26C
    assert referenced_address("sym", "%lo(sym - 0x4)($v0)", labels) == 0x1FC
    assert referenced_address("RO_00000300", "%hi(RO_00000300)", labels) == 0x300
    assert referenced_address("unknown", "unknown", labels) is None
