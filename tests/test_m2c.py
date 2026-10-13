from tools.m2c import clean, extract

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


def test_clean_restores_raw_words_and_twin_labels():
    out = clean(LINES[:6])
    assert out[1] == "f:"
    assert out[2].endswith("jal         g")
    assert out[3] == "    /* 000104 00000104 0000023C */ lui $v0, %hi(D_1)"
    assert not any(".reloc" in line for line in out)


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
