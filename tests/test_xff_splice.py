import pytest

from tools.xff_splice import (
    CompiledFunction,
    CompiledObject,
    DataSection,
    OriginalSection,
    Place,
    Resolver,
    SpliceError,
    Symbol,
    add_missing_twins,
    byte_lines,
    field_expression,
    generate,
    generate_data,
    place_data,
    place_functions,
    replace_data,
    replace_function,
)
from tools.xff_split import Reloc

JAL = 0x0C000000
SYMBOLS = {"callee": Symbol(0x40, ".text"), "other_file": Symbol(0x80, ".text")}


def fn(words, relocs=None):
    return CompiledFunction("f", "f", words, relocs or {})


def test_plain_words_pass_through():
    lines, twins = generate(
        fn([0x27BDFFF0, 0x03E00008]), [0x27BDFFF0, 0x03E00008], {}, Resolver(SYMBOLS)
    )
    assert lines == [["    .word 0x27BDFFF0"], ["    .word 0x03E00008"]]
    assert twins == set()


def test_instruction_mismatch_is_an_error():
    with pytest.raises(SpliceError, match="word 1"):
        generate(fn([0, 1]), [0, 2], {}, Resolver(SYMBOLS))


def test_length_mismatch_is_an_error():
    with pytest.raises(SpliceError, match="3 words"):
        generate(fn([0, 0, 0]), [0, 0], {}, Resolver(SYMBOLS))


def test_by_name_reference_keeps_the_name():
    mine = {0: Reloc(4, "other_file", False, 0)}
    theirs = {0: Reloc(4, "other_file", False, 0)}
    lines, _ = generate(fn([JAL], mine), [JAL], theirs, Resolver(SYMBOLS))
    assert lines == [['    .reloc ., R_MIPS_26, "other_file"', "    .word 0x0C000000"]]


def test_wrong_target_is_an_error():
    mine = {0: Reloc(4, "callee", False, 0)}
    theirs = {0: Reloc(4, "other_file", False, 0)}
    with pytest.raises(SpliceError, match="target"):
        generate(fn([JAL], mine), [JAL], theirs, Resolver(SYMBOLS))


def test_same_file_reference_is_recomputed_from_labels():
    # The original jal stores callee's section offset (0x40 >> 2) in its field.
    mine = {0: Reloc(4, "callee", False, 0)}
    theirs = {0: Reloc(4, ".text", True, 0x40)}
    lines, twins = generate(fn([JAL], mine), [JAL | (0x40 >> 2)], theirs, Resolver(SYMBOLS))
    assert lines[0][0] == "    .reloc ., R_MIPS_26, .Lxff.start.text"
    assert lines[0][1] == (
        "    .word 0x0C000000 | (((.Lxff.callee - .Lxff.start.text + 0x0) >> 2) & 0x3FFFFFF)"
    )
    assert twins == {"callee"}


def test_same_file_reference_to_wrong_place_is_an_error():
    mine = {0: Reloc(4, "callee", False, 0)}
    theirs = {0: Reloc(4, ".text", True, 0x44)}
    with pytest.raises(SpliceError, match="original at"):
        generate(fn([JAL], mine), [JAL | (0x44 >> 2)], theirs, Resolver(SYMBOLS))


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


# --- data owned by the C object ---

LUI, ADDIU = 0x3C020000, 0x24420000


def data_object(rodata: bytes, data_relocs=None, symbols=None):
    """One C function referencing its own .rodata+0 through a HI16/LO16 pair."""
    relocs = {0: Reloc(5, ".rodata", True, 0), 1: Reloc(6, ".rodata", True, 0)}
    fn_ = CompiledFunction("f", "f", [LUI, ADDIU], relocs, 0)
    sec = DataSection(".rodata", len(rodata), rodata, False, data_relocs or {}, symbols or {})
    return CompiledObject("f", [fn_], {".rodata": sec})


def original_rodata(data: bytes, relocs=None) -> OriginalSection:
    return OriginalSection(".rodata", 0x1000, len(data), data, False, relocs or {})


def test_c_data_is_placed_where_the_original_references_it():
    obj = data_object(b"hi\0\0")
    text_relocs = {0x40: Reloc(5, ".rodata", True, 0x20), 0x44: Reloc(6, ".rodata", True, 0x20)}
    assert place_data(obj, {"f": 0x40}, text_relocs, {}) == {".rodata": Place(".rodata", 0x20)}


def test_c_data_referenced_from_two_places_must_agree():
    obj = data_object(b"hi\0\0")
    text_relocs = {0x40: Reloc(5, ".rodata", True, 0x20), 0x44: Reloc(6, ".rodata", True, 0x30)}
    with pytest.raises(SpliceError, match="several places"):
        place_data(obj, {"f": 0x40}, text_relocs, {})


def test_c_data_referenced_where_the_original_references_nothing_is_an_error():
    obj = data_object(b"hi\0\0")
    with pytest.raises(SpliceError, match="the original nothing"):
        place_data(obj, {"f": 0x40}, {}, {})


def test_named_c_data_is_placed_by_the_original_symbol():
    obj = data_object(b"\1\0\0\0", symbols={"table": 0})
    obj.functions = []
    placed = place_data(obj, {}, {}, {"table": Symbol(0x8, ".rodata")})
    assert placed == {".rodata": Place(".rodata", 0x8)}


def test_text_reference_into_c_data_goes_through_the_local_label():
    obj = data_object(b"hi\0\0")
    resolver = Resolver({}, [(0, 8, 0x40)], {".rodata": Place(".rodata", 0x20)})
    resolver.labels = {Place(".rodata", 0x20): ".Lxff.RO_str"}
    theirs = {0: Reloc(5, ".rodata", True, 0x20), 1: Reloc(6, ".rodata", True, 0x20)}
    lines, _ = generate(obj.functions[0], [LUI, ADDIU], theirs, resolver)
    assert lines[1] == [
        "    .reloc ., R_MIPS_LO16, .Lxff.start.rodata",
        "    .word 0x24420000 | ((.Lxff.RO_str - .Lxff.start.rodata) & 0xFFFF)",
    ]


def test_jump_table_entries_map_to_the_original_function():
    # C .rodata+0 holds .text+0x8 of a function the original has at .text+0x100.
    sec = DataSection(".rodata", 4, (8).to_bytes(4, "little"), False,
                      {0: Reloc(2, ".text", True, 8)}, {})  # fmt: skip
    original = original_rodata((0x108).to_bytes(4, "little"), {0: Reloc(2, ".text", True, 0x108)})
    resolver = Resolver({}, [(0, 0x10, 0x100)], {}, {Place(".text", 0x108): ".Lxff..L108"})
    lines, _ = generate_data("f", sec, Place(".rodata", 0), original, resolver)
    assert lines == {
        0: [
            "    .reloc ., R_MIPS_32, .Lxff.start.text",
            "    .word (.Lxff..L108 - .Lxff.start.text)",
        ]
    }


def test_jump_table_entry_to_the_wrong_case_is_an_error():
    sec = DataSection(".rodata", 4, (4).to_bytes(4, "little"), False,
                      {0: Reloc(2, ".text", True, 4)}, {})  # fmt: skip
    original = original_rodata((0x108).to_bytes(4, "little"), {0: Reloc(2, ".text", True, 0x108)})
    resolver = Resolver({}, [(0, 0x10, 0x100)])
    with pytest.raises(SpliceError, match=r"points at \.text\+0x104"):
        generate_data("f", sec, Place(".rodata", 0), original, resolver)


def test_c_data_bytes_must_match():
    sec = DataSection(".rodata", 4, b"hj\0\0", False, {}, {})
    with pytest.raises(SpliceError, match="differs: C 6A, original 69"):
        generate_data("f", sec, Place(".rodata", 0), original_rodata(b"hi\0\0"), Resolver({}))


def test_missing_relocation_in_c_data_is_an_error():
    sec = DataSection(".rodata", 4, b"\0\0\0\0", False, {}, {})
    original = original_rodata(b"\0\0\0\0", {0: Reloc(2, "other", False, 0)})
    with pytest.raises(SpliceError, match="nothing in C, other in the original"):
        generate_data("f", sec, Place(".rodata", 0), original, Resolver({}))


def test_replace_data_keeps_labels_and_outside_bytes():
    original = original_rodata(b"abcdhi\0\0wxyz")
    lines = [
        ".section .rodata",
        "dlabel A",
        "    /* 001000 00001000 61626364 */ .word 0x64636261",
        "dlabel B",
        ".Lxff.B:",
        "    /* 001004 00001004 68690000 */ .word 0x00006968",
        '    .reloc ., R_MIPS_32, "x"',
        "    /* 001008 00001008 7778797A */ .word x",
    ]
    out = replace_data(lines, original, 4, 6, b"hi", {}, "f")
    assert out[3:] == [
        "dlabel B",
        ".Lxff.B:",
        "    /* 001004 from C (f.c) */",
        "    .word 0x00006968",
        '    .reloc ., R_MIPS_32, "x"',
        "    /* 001008 00001008 7778797A */ .word x",
    ]


def test_byte_lines_mix_words_and_bytes():
    assert byte_lines(b"\1\2\3\4\5", 3) == [
        "    .byte 0x01",
        "    .word 0x05040302",
    ]


def test_unnamed_static_is_placed_by_its_caller():
    caller = CompiledFunction("f", "f", [JAL], {0: Reloc(4, ".text", True, 0x10)}, 0)
    static = CompiledFunction("g", "f", [0, 0], {}, 0x10, local=True)
    obj = CompiledObject("f", [caller, static], {})
    starts = place_functions(
        obj, {"f": Symbol(0x100, ".text")}, {0x100: Reloc(4, ".text", True, 0x200)}
    )
    assert starts == {"f": 0x100, "g": 0x200}


def test_unreferenced_unnamed_static_is_an_error():
    static = CompiledFunction("g", "f", [0], {}, 0, local=True)
    with pytest.raises(SpliceError, match="can't be placed"):
        place_functions(CompiledObject("f", [static], {}), {}, {})
