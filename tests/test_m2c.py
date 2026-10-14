import re

import pytest

from tools.m2c import clean, extract, reloc_names

LINES = [
    "glabel f # 1",
    ".Lxff.f:",
    "    /* 000100 00000100 00000000 */  jal         .Lxff.g",
    "    .reloc ., R_MIPS_HI16, .Lxff.start.data",
    "    /* 000104 00000104 0000023C */ .word 0x3C020000 /* lui $v0, %hi(D_1) */",
    "endlabel f",
    "glabel func_8 # 2",
    "    /* 000108 00000108 00000000 */  nop",
    "endlabel func_8",
    "glabel h",
]


def test_extract_one_function():
    assert extract(LINES, "f", None) == LINES[:6]


def test_extract_through_a_false_split_drops_inner_boundaries():
    out = extract(LINES, "f", "func_8")
    assert out[0] == "glabel f # 1" and out[-1] == "endlabel func_8"
    assert "endlabel f" not in out and "glabel func_8 # 2" not in out


def test_interior_plain_twins_and_branches_stay_local():
    lines = [
        "glabel f",
        ".Lxff.f:",
        "    b .Lxff.jtbl_20",
        "    nop",
        "  jtbl_20:",
        ".Lxff.jtbl_20:",
        "    b jtbl_30",
        "    nop",
        "  jtbl_30:",
        ".Lxff.jtbl_30:",
        "    jal external_jtbl_30",
        "    nop",
        "endlabel f",
    ]
    out = clean(extract(lines, "f", None))
    assert "f:" in out
    assert out.count(".Lm2c.jtbl_20:") == 1
    assert out.count(".Lm2c.jtbl_30:") == 1
    assert "    b .Lm2c.jtbl_20" in out
    assert "    b .Lm2c.jtbl_30" in out
    assert "    jal external_jtbl_30" in out
    assert not any(line.strip() in {"jtbl_20:", "jtbl_30:"} for line in out)


def test_plain_labels_without_twins_are_preserved():
    lines = ["glabel f", "    b .L20", ".L20:", "    nop", "endlabel f"]
    assert clean(extract(lines, "f", None)) == lines


def test_clean_restores_raw_words_and_twin_labels():
    out = clean(LINES[:6])
    assert out[1] == "f:"
    assert out[2].endswith("jal         g")
    assert out[3] == "    /* 000104 00000104 0000023C */ lui $v0, %hi(D_1)"
    assert not any(".reloc" in line for line in out)


@pytest.mark.parametrize("destination, source", [(1, 0), (0, 1), (3, 6), (31, 30)])
def test_clean_preserves_raw_single_precision_integer_conversions(destination, source):
    word = 0x46000024 | (source << 11) | (destination << 6)
    out = clean([f"    /* 000100 00000100 00000000 */ .word 0x{word:08X}"])
    instruction = out[0].split("*/", 1)[1].strip()
    assert re.fullmatch(rf"cvt\.w\.s\s+\$f{destination},\s+\$f{source}", instruction)


@pytest.mark.parametrize("word", [0x46010064, 0x46200064])
def test_clean_leaves_reserved_conversion_bits_and_double_format_raw(word):
    out = clean([f"    /* 000100 00000100 00000000 */ .word 0x{word:08X}"])
    assert out[0].strip().endswith(f".word 0x{word:08X}")


def test_clean_decodes_relocated_words_with_raw_word_comments():
    out = clean(
        [
            '.reloc ., R_MIPS_26, "SCRGetFirstObj"',
            "    /* 0C2650 000C2650 0000000C */ .word 0x0C000000 /* .word 0x0C000000 */",
            '.reloc ., R_MIPS_HI16, "gcGlobalVar"',
            "    /* 0C2654 000C2654 0000023C */ .word 0x3C020000 /* .word 0x3C020000 */",
        ]
    )
    assert len(out) == 2
    assert "jal" in out[0] and "SCRGetFirstObj" in out[0]
    assert "lui" in out[1] and "%hi(gcGlobalVar)" in out[1]
    assert not any(".word" in line for line in out)


def test_split_tail_alias_and_branch_stay_in_one_function():
    lines = [
        "glabel first",
        ".Lxff.first:",
        "    b .Lxff.func_000C3160",
        "endlabel first",
        "glabel func_000C3160",
        ".Lxff.func_000C3160:",
        "    jr $ra",
        "    nop",
        "endlabel func_000C3160",
    ]
    out = clean(extract(lines, "first", "func_000C3160"))
    assert "first:" in out
    assert ".Lm2c.func_000C3160:" in out
    assert "    b .Lm2c.func_000C3160" in out
    assert "func_000C3160:" not in out


def test_named_raw_relocations_keep_paired_addends():
    lines = [
        '.reloc ., R_MIPS_HI16, "gcGlobalVar"',
        "    /* 0C2624 000C2624 0000023C */ .word 0x3C020000 /* .word 0x3C020000 */",
        '.reloc ., R_MIPS_LO16, "gcGlobalVar"',
        "    /* 0C2630 000C2630 B8024424 */ .word 0x244402B8 /* .word 0x244402B8 */",
    ]
    assert reloc_names(lines, {}) == {1: "gcGlobalVar + 0x2B8", 3: "gcGlobalVar + 0x2B8"}
    out = clean(lines)
    assert "%hi(gcGlobalVar + 0x2B8)" in out[0]
    assert "%lo(gcGlobalVar + 0x2B8)" in out[1]


def test_clean_corrects_stale_section_addresses_in_mnemonic_comments():
    lines = [
        ".reloc ., R_MIPS_HI16, .Lxff.start.rodata",
        "    /* 0EBC38 000EBC38 0000043C */ .word 0x3C040000 /* lui $a0, %hi(RO_0011BBA0) */",
        ".reloc ., R_MIPS_LO16, .Lxff.start.rodata",
        "    /* 0EBC48 000EBC48 506C8424 */ .word 0x24846C50"
        " /* addiu $a0, $a0, %lo(RO_0011BBA0) */",
    ]
    out = clean(lines, {".rodata": 0x13B1F0})
    assert len(out) == 2
    assert "%hi(RO_00141E40)" in out[0]
    assert "%lo(RO_00141E40)" in out[1]
    assert all("RO_0011BBA0" not in line and ".word" not in line for line in out)


def test_clean_uses_named_relocation_and_addend_over_mnemonic_comment():
    lines = [
        '.reloc ., R_MIPS_HI16, "gcGlobalVar"',
        "    /* 000100 00000100 0000023C */ .word 0x3C020000 /* lui $v0, %hi(stale) */",
        '.reloc ., R_MIPS_LO16, "gcGlobalVar"',
        "    /* 000104 00000104 B8024424 */ .word 0x244402B8 /* addiu $v0, $v0, %lo(stale) */",
    ]
    out = clean(lines)
    assert "%hi(gcGlobalVar + 0x2B8)" in out[0]
    assert "%lo(gcGlobalVar + 0x2B8)" in out[1]
    assert all("stale" not in line for line in out)


def test_clean_keeps_extracted_local_jump_alias_in_mnemonic_comment():
    lines = [
        ".reloc ., R_MIPS_26, .Lxff.start.text",
        "    /* 000100 00000100 10000008 */ .word 0x08000010 /* j .Lm2c.func_00000040 */",
    ]
    assert clean(lines, {".text": 0})[0].endswith("j .Lm2c.func_00000040")
