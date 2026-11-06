import json
from itertools import permutations
from pathlib import Path

import pytest
from synthetic_xff import build as synthetic_module

from tools import xff_splice
from tools.functions import Reloc
from tools.xff_splice import (
    CompiledFunction,
    CompiledObject,
    DataSection,
    FunctionReplacement,
    OriginalSection,
    Place,
    Resolver,
    SpliceError,
    Symbol,
    add_missing_twins,
    byte_lines,
    field_expression,
    function_names,
    generate,
    generate_data,
    place_data,
    place_functions,
    read_object_list,
    replace_data,
    replace_function,
    replace_functions,
)

JAL = 0x0C000000
SYMBOLS = {"callee": Symbol(0x40, ".text"), "other_file": Symbol(0x80, ".text")}


def test_object_response_file_preserves_order_and_path_characters(tmp_path):
    names = ["build/a b.o", "build/$name.o", r"C:\objects\file.o", "build/日本語.o"]
    response = tmp_path / "objects.rsp"
    response.write_text(json.dumps(names), encoding="utf-8")
    assert read_object_list(response) == [Path(name) for name in names]


@pytest.mark.parametrize("content", ["not json", "{}", "[1]", '[""]', '"one.o"'])
def test_invalid_object_response_file_is_rejected(tmp_path, content):
    response = tmp_path / "objects.rsp"
    response.write_text(content, encoding="utf-8")
    with pytest.raises(SpliceError, match="object list|object paths"):
        read_object_list(response)


def test_missing_object_response_file_is_rejected(tmp_path):
    with pytest.raises(SpliceError, match="cannot read object list"):
        read_object_list(tmp_path / "missing.rsp")


def test_splice_cli_accepts_response_file_and_positional_objects(tmp_path, monkeypatch):
    response = tmp_path / "objects.rsp"
    response.write_text('["second.o", "third.o"]', encoding="utf-8")
    monkeypatch.setattr(xff_splice, "ROOT", tmp_path)
    monkeypatch.setattr(xff_splice, "open_module", lambda m, iso_dir: f"{m} from {iso_dir}")
    calls = []
    monkeypatch.setattr(xff_splice, "splice", lambda *args: calls.append(args) or 3)
    assert xff_splice.main(["TEST", "first.o", "--objects-file", str(response)]) == 0
    assert calls[0][0] == "TEST"
    assert calls[0][1] == [Path("first.o"), Path("second.o"), Path("third.o")]
    assert calls[0][4] == f"TEST from {tmp_path / 'iso'}"


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


def test_unpaired_lo16_compares_only_the_low_half():
    # An original LO16 without its own HI16 implies 0x40 - 0x10000; only 0x0040 reaches the field.
    mine = {0: Reloc(6, "callee", False, 0)}
    theirs = {0: Reloc(6, ".text", True, 0x40 - 0x10000)}
    lines, _ = generate(fn([0x24420000], mine), [0x24420040], theirs, Resolver(SYMBOLS))
    assert lines[0][0] == "    .reloc ., R_MIPS_LO16, .Lxff.start.text"


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
    resolver = Resolver({}, text=[(0, 8, 0x40)], data={".rodata": Place(".rodata", 0x20)})
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
    resolver = Resolver({}, text=[(0, 0x10, 0x100)], labels={Place(".text", 0x108): ".Lxff..L108"})
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
    resolver = Resolver({}, text=[(0, 0x10, 0x100)])
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


def test_replace_function_continues_through_a_false_split():
    # spimdisasm ended f at a tail call and called the rest func_8.
    lines = [
        "glabel f",
        "    /* 000100 00000100 00000000 */  .word 0",
        "endlabel f",
        "glabel func_8",
        "    /* 000104 00000104 00000000 */  .word 0",
        "endlabel func_8",
        "glabel g",
    ]
    out = replace_function(lines, "f", 0x100, 0, [["    A"], ["    B"]], "f")
    assert out == [
        "glabel f",
        "    /* 0000 from C (f.c) */",
        "    A",
        "endlabel f",
        "glabel func_8",
        "    /* 0004 from C (f.c) */",
        "    B",
        "endlabel func_8",
        "glabel g",
    ]


def test_replace_function_stops_at_the_next_label_without_endlabel():
    lines = [
        "glabel f",
        "    /* 000100 00000100 00000000 */  .word 0",
        "  /* static variable */",
        "alabel T_00000104",
        "    /* 000104 00000104 00000000 */  .word 0",
    ]
    out = replace_function(lines, "f", 0x100, 0, [["    A"]], "f")
    assert out[3:] == lines[2:] and out[1:3] == ["    /* 0000 from C (f.c) */", "    A"]


MERGED = [
    "glabel f",
    "    /* 000100 00000100 00000000 */  .word 0",
    "    /* 000104 00000104 00000000 */  .word 0",
    "  .L00000108:",
    "    /* 000108 00000108 00000000 */  .word 0",
    "endlabel f",
]


def test_function_names_fall_back_to_branch_labels():
    assert function_names(MERGED, 0) == {0x100: "f", 0x108: ".L00000108"}


def test_functions_split_at_a_branch_label_where_spimdisasm_merged_them():
    # spimdisasm ran f into the next function, which starts at .L00000108.
    patches = [
        FunctionReplacement(".L00000108", 0x108, [["    C"]], "g"),
        FunctionReplacement("f", 0x100, [["    A"], ["    B"]], "f"),
    ]
    assert replace_functions(MERGED, 0, patches) == [
        "glabel f",
        "    /* 0000 from C (f.c) */",
        "    A",
        "    /* 0004 from C (f.c) */",
        "    B",
        "  .L00000108:",
        "    /* 0000 from C (g.c) */",
        "    C",
        "endlabel f",
    ]


@pytest.mark.parametrize("order", list(permutations(range(3))))
def test_batch_function_replacement_preserves_splits_labels_and_relocations(order):
    lines = [
        ".section .text",
        "glabel f",
        '    .reloc ., R_MIPS_32, "old"',
        "    /* 000100 00000100 00000000 */ .word 0",
        "endlabel f",
        "glabel false_split",
        ".Lxff.inner:",
        "    /* 000104 00000104 00000000 */ .word 0",
        "endlabel false_split",
        "glabel g",
        "    /* 000108 00000108 00000000 */ .word 0",
        "  /* no endlabel before the next function */",
        "glabel h",
        "    /* 00010C 0000010C 00000000 */ .word 0",
        "endlabel h",
        ".section .rodata",
        "    .word 99",
    ]
    patches = [
        FunctionReplacement("f", 0, [["    A"], ["    B"]], "first"),
        FunctionReplacement("g", 8, [['    .reloc ., R_MIPS_32, "new"', "    C"]], "second"),
        FunctionReplacement("h", 12, [["    D", "    # extra comment"]], "third"),
    ]
    ordered = [patches[i] for i in order]
    expected = lines
    for r in ordered:
        expected = replace_function(expected, r.name, 0x100, r.start, r.generated, r.source)
    actual = replace_functions(lines, 0x100, ordered)
    assert actual == expected
    assert actual[-2:] == lines[-2:]
    assert ".Lxff.inner:" in actual
    assert not any('"old"' in line for line in actual)
    assert sum("from C" in line for line in actual) == 4


@pytest.mark.parametrize(
    ("lines", "patch", "message"),
    [
        (["glabel other"], FunctionReplacement("f", 0, [[" A"]], "f"), "not found"),
        (
            ["glabel f", " /* 000104 00000104 00000000 */ .word 0"],
            FunctionReplacement("f", 0, [[" A"]], "f"),
            "word 0 isn't where expected",
        ),
        (
            ["glabel f", " /* 000100 00000100 00000000 */ .word 0", "endlabel f"],
            FunctionReplacement("f", 0, [[" A"], [" B"]], "f"),
            "replaced 1 of 2 words",
        ),
    ],
)
def test_batch_function_replacement_keeps_missing_and_malformed_span_errors(lines, patch, message):
    with pytest.raises(SpliceError, match=message):
        replace_functions(lines, 0x100, [patch])


@pytest.mark.parametrize("reverse", [False, True])
@pytest.mark.parametrize("alias", [False, True])
def test_batch_overlapping_functions_retain_sequential_rejection(reverse, alias):
    lines = [
        "glabel f",
    ]
    if not alias:
        lines.append(" /* 000100 00000100 00000000 */ .word 0")
    offset = 0 if alias else 4
    lines.extend(
        [
            "glabel g",
            f" /* {0x100 + offset:06X} {0x100 + offset:08X} 00000000 */ .word 0",
            "endlabel g",
        ]
    )
    patches = [
        FunctionReplacement("f", 0, [[" A"]] if alias else [[" A"], [" B"]], "f"),
        FunctionReplacement("g", offset, [[" C"]], "g"),
    ][:: -1 if reverse else 1]
    with pytest.raises(SpliceError) as previous:
        result = lines
        for r in patches:
            result = replace_function(result, r.name, 0x100, r.start, r.generated, r.source)
    with pytest.raises(SpliceError) as batched:
        replace_functions(lines, 0x100, patches)
    assert str(batched.value) == str(previous.value)


def test_splice_batches_reversed_functions_with_a_same_object_call(tmp_path, monkeypatch):
    elf = synthetic_module()
    text = xff_splice.original_sections(elf)[".text"]
    asm = tmp_path / "asm"
    asm.mkdir()
    lines = [".section .text", ".Lxff.start.text:"]
    for name, start, words in [("f0", 0, [0, 0]), ("f1", 8, [JAL, 0])]:
        lines.append(f"glabel {name}")
        for i, word in enumerate(words):
            address = text.base + start + 4 * i
            if word == JAL:
                lines.append("    .reloc ., R_MIPS_26, .Lxff.start.text")
            lines.append(f" /* {address:06X} {address:08X} 00000000 */ .word {word:#x}")
        lines.append(f"endlabel {name}")
    (asm / "text.s").write_text("\n".join(lines))
    f0 = CompiledFunction("f0", "pair", [0, 0], {}, 0)
    f1 = CompiledFunction("f1", "pair", [JAL, 0], {0: Reloc(4, ".text", True, 0)}, 8)
    obj = CompiledObject("pair", [f1, f0], {})
    monkeypatch.setattr(xff_splice, "load_object", lambda _: obj)
    output = tmp_path / "output"
    assert xff_splice.splice("TEST", [tmp_path / "pair.o"], asm, output, elf) == 2
    result = (output / "text.s").read_text()
    assert result.count("from C (pair.c)") == 4
    assert result.count(".reloc ., R_MIPS_26, .Lxff.start.text") == 1
    assert not any(xff_splice.LINE_RE.match(line) for line in result.splitlines())


def test_unnamed_original_objects_resolve_by_label_name():
    resolver = Resolver({}, sections={".data": (0x1000, 0x100)})
    assert resolver.place(Reloc(5, "D_00001010", False, 4)) == Place(".data", 0x14)
    assert resolver.place(Reloc(5, "D_STR_00001020", False, 0)) == Place(".data", 0x20)
    assert resolver.place(Reloc(5, "unknown", False, 0)) is None


def test_static_named_after_its_label_is_placed_there():
    static = CompiledFunction("func_00000140", "f", [0], {}, 0, local=True)
    starts = place_functions(CompiledObject("f", [static], {}), {}, {}, text_base=0x40)
    assert starts == {"func_00000140": 0x100}


@pytest.mark.parametrize("relocated_first", [False, True])
def test_adjacent_c_data_replacements_preserve_each_others_boundaries(relocated_first):
    original = original_rodata(b"abcd\0\0\0\0wxyz", {4: Reloc(2, "x", False, 0)})
    lines = [
        ".section .rodata",
        "dlabel A",
        "    /* 001000 00001000 61626364 */ .word 0x64636261",
        "dlabel B",
        '    .reloc ., R_MIPS_32, "x"',
        "    /* 001004 00001004 00000000 */ .word x",
        "dlabel C",
        "    /* 001008 00001008 7778797A */ .word 0x7A797877",
    ]
    replacements = [
        (0, 4, b"abcd", {}, "plain"),
        (4, 8, b"\0\0\0\0", {4: ['    .reloc ., R_MIPS_32, "x"', "    .word x"]}, "table"),
        (8, 12, b"wxyz", {}, "tail"),
    ]
    if relocated_first:
        replacements[0], replacements[1] = replacements[1], replacements[0]
    for lo, hi, data, relocs, source in replacements:
        lines = replace_data(lines, original, lo, hi, data, relocs, source)
    assert lines.count("    .word 0x64636261") == 1
    assert lines.count("    .word x") == 1
    assert lines.count('    .reloc ., R_MIPS_32, "x"') == 1
    assert lines.count("    .word 0x7A797877") == 1
    assert [line for line in lines if line.startswith("dlabel")] == [
        "dlabel A",
        "dlabel B",
        "dlabel C",
    ]


@pytest.mark.parametrize("word_count", [1, 2, 3])
def test_splice_enforces_explicit_original_size(tmp_path, monkeypatch, word_count):
    elf = synthetic_module()
    text = xff_splice.original_sections(elf)[".text"]
    asm = tmp_path / "asm"
    asm.mkdir()
    (asm / "text.s").write_text(
        ".section .text\nglabel f0\n"
        f"    /* {text.base:06X} {text.base:08X} 00000000 */ nop\n"
        f"    /* {text.base + 4:06X} {text.base + 4:08X} 00000000 */ nop\n"
        "endlabel f0\n"
    )
    # f0 has an authoritative eight-byte size, not an inferred asm boundary.
    obj = CompiledObject("f0", [CompiledFunction("f0", "f0", [0] * word_count, {})], {})
    monkeypatch.setattr(xff_splice, "load_object", lambda _: obj)
    output = tmp_path / "output"
    if word_count == 2:
        assert xff_splice.splice("TEST", [tmp_path / "f0.o"], asm, output, elf) == 1
        result = (output / "text.s").read_text()
        assert result.count("from C") == 2
        assert not any(xff_splice.LINE_RE.match(line) for line in result.splitlines())
    else:
        with pytest.raises(SpliceError, match="f0.*size"):
            xff_splice.splice("TEST", [tmp_path / "f0.o"], asm, output, elf)
        assert not output.exists()


def test_named_function_without_explicit_size_keeps_inferred_extent_behavior():
    obj = CompiledObject("f", [fn([0, 0, 0])], {})
    assert place_functions(obj, {"f": Symbol(0, ".text")}, {}) == {"f": 0}
