from dataclasses import dataclass

import pytest
from synthetic_xff import build

from tools.functions import Function, Reloc, compare, function, functions, sext16

JAL = 0x0C000000


@dataclass(frozen=True)
class At:
    section: str
    offset: int


def by_name(target, rtype=4):
    return Reloc(rtype, target, False, 0)


def same_file(section, addend, rtype=4):
    return Reloc(rtype, section, True, addend)


def placed_at(section, offset):
    return lambda reloc: At(section, offset)


# Reading


def test_functions_reads_words_and_relocations():
    found = functions(build())
    assert list(found) == ["f0", "f1", "f2", "f3"]
    assert found["f1"] == Function([JAL, 0], {0: same_file(".text", 0)})
    assert found["f2"].relocs == {0: by_name("f0"), 1: same_file(".rodata", 4, rtype=5)}


def test_lo16_addend_pairs_with_the_preceding_hi16():
    assert function(build(), "f3").relocs == {0: same_file(".rodata", 4, rtype=6)}


def test_function_by_placeholder_name_needs_a_size():
    elf = build()
    address = elf.get_section_by_name(".text")["sh_offset"] + 0x10  # asm addresses
    name = f"func_{address:08X}"
    assert function(elf, name, 8) == function(elf, "f2")
    with pytest.raises(KeyError, match="size"):
        function(elf, name)


def test_unknown_function_is_a_key_error():
    with pytest.raises(KeyError, match="no such function"):
        function(build(), "missing")


def test_sext16():
    assert sext16(0x7FFF) == 0x7FFF
    assert sext16(0x8000) == -0x8000
    assert sext16(0x12345678) == 0x5678


# Comparing: plain words and relocated fields


def kinds(mismatches):
    return [(m.index, m.kind) for m in mismatches]


def test_identical_functions_match():
    fn = Function([0x27BDFFF0, 0x03E00008], {})
    assert compare(fn, fn) == []


def test_instruction_mismatch():
    assert kinds(compare(Function([0, 2], {}), Function([0, 1], {}))) == [(1, "instruction")]


def test_relocated_field_bits_alone_dont_decide():
    # Only the bits outside the field are compared directly; the target decides the rest.
    target = Function([JAL | 0x10], {0: same_file(".text", 0x40)})
    built = Function([JAL], {0: by_name("callee")})
    assert compare(target, built, placed_at(".text", 0x40)) == []
    other_opcode = Function([0x08000000], {0: by_name("callee")})
    assert kinds(compare(target, other_opcode, placed_at(".text", 0x40))) == [(0, "instruction")]


def test_missing_or_extra_relocation():
    reloc = {0: by_name("f")}
    assert kinds(compare(Function([JAL], reloc), Function([JAL], {}))) == [(0, "relocation")]
    assert kinds(compare(Function([JAL], {}), Function([JAL], reloc))) == [(0, "relocation")]


def test_relocation_type_must_agree():
    target = Function([0], {0: by_name("f", rtype=5)})
    built = Function([0], {0: by_name("f", rtype=6)})
    assert kinds(compare(target, built)) == [(0, "relocation")]


def test_gp_relative_relocations_compare_by_field():
    target = Function([0x8F820010], {0: by_name("g", rtype=7)})
    built = Function([0x8F820010], {0: by_name("g", rtype=7)})
    assert compare(target, built) == []


# Comparing: targets


def test_by_name_target_must_be_the_same_symbol():
    target = Function([JAL], {0: by_name("other_file")})
    assert compare(target, Function([JAL], {0: by_name("other_file")})) == []
    wrong = compare(target, Function([JAL], {0: by_name("callee")}))
    assert kinds(wrong) == [(0, "target")]
    assert "callee vs original other_file" in wrong[0].detail


def test_by_name_target_is_checked_without_placement():
    # The case try_compilers used to call MATCH: same type, different symbol.
    target = Function([JAL], {0: by_name("a")})
    assert compare(target, Function([JAL], {0: by_name("b")}))[0].verified


def test_same_file_target_is_unverified_without_placement():
    target = Function([JAL | 0x10], {0: same_file(".text", 0x40)})
    built = Function([JAL], {0: by_name("callee")})
    [m] = compare(target, built)
    assert m.kind == "unverified" and not m.verified


def test_same_file_target_must_land_on_the_same_place():
    target = Function([JAL | 0x11], {0: same_file(".text", 0x44)})
    built = Function([JAL], {0: by_name("callee")})
    [m] = compare(target, built, placed_at(".text", 0x40))
    assert m.kind == "target"
    assert "points at .text+0x40, original at .text+0x44" in m.detail


def test_same_file_target_in_another_section_is_a_mismatch():
    target = Function([JAL], {0: same_file(".text", 0x40)})
    built = Function([JAL], {0: by_name("callee")})
    assert kinds(compare(target, built, placed_at(".data", 0x40))) == [(0, "target")]
    assert kinds(compare(target, built, lambda reloc: None)) == [(0, "target")]


def test_unpaired_lo16_compares_only_the_low_half():
    # An original LO16 without its own HI16 implies 0x40 - 0x10000.
    target = Function([0x24420040], {0: same_file(".text", 0x40 - 0x10000, rtype=6)})
    built = Function([0x24420000], {0: by_name("callee", rtype=6)})
    assert compare(target, built, placed_at(".text", 0x40)) == []


def test_lo16_to_a_different_low_half_is_a_mismatch():
    target = Function([0x24420044], {0: same_file(".text", 0x44, rtype=6)})
    built = Function([0x24420000], {0: by_name("callee", rtype=6)})
    assert kinds(compare(target, built, placed_at(".text", 0x40))) == [(0, "target")]


def test_hi16_offsets_compare_exactly():
    target = Function([0x3C020001], {0: same_file(".text", 0x40 + 0x10000, rtype=5)})
    built = Function([0x3C020000], {0: by_name("callee", rtype=5)})
    assert kinds(compare(target, built, placed_at(".text", 0x40))) == [(0, "target")]


# Comparing: length and padding


def test_trailing_padding_is_ignored_on_either_side():
    assert compare(Function([1, 2, 0, 0], {}), Function([1, 2], {})) == []
    assert compare(Function([1, 2], {}), Function([1, 2, 0], {})) == []


def test_other_length_differences_are_a_mismatch():
    [m] = compare(Function([1, 2, 3], {}), Function([1, 2], {}))
    assert (m.index, m.kind) == (2, "length")
    assert m.detail == "C is 2 words, original is 3"


def test_a_relocated_zero_word_is_not_padding():
    target = Function([1, 0], {1: by_name("table", rtype=2)})
    assert kinds(compare(target, Function([1], {}))) == [(1, "length")]
