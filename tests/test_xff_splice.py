import pytest

from tools.xff_splice import (
    CompiledFunction,
    SpliceError,
    Symbol,
    add_missing_twins,
    field_expression,
    generate,
    replace_function,
)
from tools.xff_split import Reloc

JAL = 0x0C000000
SYMBOLS = {"callee": Symbol(0x40, ".text"), "other_file": Symbol(0x80, ".text")}


def fn(words, relocs=None):
    return CompiledFunction("f", "f", words, relocs or {})


def test_plain_words_pass_through():
    lines, twins = generate(fn([0x27BDFFF0, 0x03E00008]), [0x27BDFFF0, 0x03E00008], {}, SYMBOLS, {})
    assert lines == [["    .word 0x27BDFFF0"], ["    .word 0x03E00008"]]
    assert twins == set()


def test_instruction_mismatch_is_an_error():
    with pytest.raises(SpliceError, match="word 1"):
        generate(fn([0, 1]), [0, 2], {}, SYMBOLS, {})


def test_length_mismatch_is_an_error():
    with pytest.raises(SpliceError, match="3 words"):
        generate(fn([0, 0, 0]), [0, 0], {}, SYMBOLS, {})


def test_by_name_reference_keeps_the_name():
    mine = {0: Reloc(4, "other_file", False, 0)}
    theirs = {0: Reloc(4, "other_file", False, 0)}
    lines, _ = generate(fn([JAL], mine), [JAL], theirs, SYMBOLS, {})
    assert lines == [['    .reloc ., R_MIPS_26, "other_file"', "    .word 0x0C000000"]]


def test_wrong_target_is_an_error():
    mine = {0: Reloc(4, "callee", False, 0)}
    theirs = {0: Reloc(4, "other_file", False, 0)}
    with pytest.raises(SpliceError, match="target"):
        generate(fn([JAL], mine), [JAL], theirs, SYMBOLS, {})


def test_same_file_reference_is_recomputed_from_labels():
    # The original jal stores callee's section offset (0x40 >> 2) in its field.
    mine = {0: Reloc(4, "callee", False, 0)}
    theirs = {0: Reloc(4, ".text", True, 0x40)}
    lines, twins = generate(fn([JAL], mine), [JAL | (0x40 >> 2)], theirs, SYMBOLS, {})
    assert lines[0][0] == "    .reloc ., R_MIPS_26, .Lxff.start.text"
    assert lines[0][1] == (
        "    .word 0x0C000000 | (((.Lxff.callee - .Lxff.start.text + 0x0) >> 2) & 0x3FFFFFF)"
    )
    assert twins == {"callee"}


def test_same_file_reference_to_wrong_place_is_an_error():
    mine = {0: Reloc(4, "callee", False, 0)}
    theirs = {0: Reloc(4, ".text", True, 0x44)}
    with pytest.raises(SpliceError, match="elsewhere"):
        generate(fn([JAL], mine), [JAL | (0x44 >> 2)], theirs, SYMBOLS, {})


def test_field_expressions():
    assert field_expression(0x3C020000, 5, "v") == "0x3C020000 | (((v) + 0x8000) >> 16 & 0xFFFF)"
    assert field_expression(0x24420000, 6, "v") == "0x24420000 | ((v) & 0xFFFF)"
    assert field_expression(0, 2, "v") == "(v)"


def test_replace_function_keeps_labels_and_drops_old_relocs():
    base = 0x100
    lines = [
        "glabel f",
        "    /* 000100 00000100 0000000C */  jal .Lxff.callee",
        "    .reloc ., R_MIPS_26, .Lxff.start.text",
        "  .L00000104:",
        "    /* 000104 00000104 00000000 */  .word 0x00000000",
        "endlabel f",
        "glabel g",
    ]
    generated = [["    GEN0"], ["    GEN1"]]
    out = replace_function(lines, "f", base, 0, generated, "f")
    assert out == [
        "glabel f",
        "    /* 0000 from C (f.c) */",
        "    GEN0",
        "  .L00000104:",
        "    /* 0004 from C (f.c) */",
        "    GEN1",
        "endlabel f",
        "glabel g",
    ]


def test_add_missing_twins_skips_existing():
    files = {"text.s": ["glabel a", ".Lxff.a:", "glabel b"]}
    add_missing_twins(files, {"a", "b"})
    assert files["text.s"] == ["glabel a", ".Lxff.a:", "glabel b", ".Lxff.b:"]
