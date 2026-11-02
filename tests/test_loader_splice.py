import json

import pytest

from tools import loader_splice
from tools.loader_splice import (
    R_MIPS_26,
    R_MIPS_GPREL16,
    R_MIPS_HI16,
    R_MIPS_LO16,
    CompiledFunction,
    CompiledObject,
    Names,
    Reloc,
    SpliceError,
    original_sizes,
    original_target,
    read_object_list,
    same_target,
    splice,
)

CSV = """address,size,name,class,library,evidence
0x00101000,0x8,func_00101000,game,loader,no Original name; class from its block
0x00101A30,0x14,Store,game,loader,Original name (KERNEL.XFF absolute symbol)
0x00101A44,0x8,Helper,game,loader,Original name (KERNEL.XFF absolute symbol)
"""


def line(address: int, word: int, text: str) -> str:
    """An instruction line as splat prints it (the word little-endian)."""
    raw = word.to_bytes(4, "little").hex().upper()
    return f"    /* {address - 0x100000:X} {address:08X} {raw} */  {text}"


# Store: loads D_00139E00 with %hi/%lo, stores through $gp, calls func_00101000.
ORIGINAL = [
    (0x101A30, 0x3C020014, "lui        $v0, %hi(D_00139E00)"),
    (0x101A34, 0x8C429E00, "lw         $v0, %lo(D_00139E00)($v0)"),
    (0x101A38, 0xAF828094, "sw         $v0, %gp_rel(D_00139E04)($gp)"),
    (0x101A3C, 0x0C040400, "jal        func_00101000"),
    (0x101A40, 0x00000000, "nop"),
    (0x101A44, 0x03E00008, "jr         $ra"),
    (0x101A48, 0x00000000, "nop"),
]
ASM = "glabel Store\n" + "\n".join(line(*o) for o in ORIGINAL) + "\n"


def store(**changes) -> CompiledFunction:
    """Store as the C compiles it: REL relocations with in-place addends."""
    words = [0x3C020000, 0x8C420000, 0xAF820000, 0x0C000000, 0x00000000]
    relocs = {
        0: Reloc(R_MIPS_HI16, "D_00139E00", ""),
        1: Reloc(R_MIPS_LO16, "D_00139E00", ""),
        2: Reloc(R_MIPS_GPREL16, "D_00139E04", ""),
        3: Reloc(R_MIPS_26, "func_00101000", ""),
    }
    for index, value in changes.get("words", {}).items():
        words[index] = value
    relocs.update(changes.get("relocs", {}))
    for index in changes.get("drop", ()):
        del relocs[index]
    return CompiledFunction("Store", "store", 0, words, relocs)


def helper() -> CompiledFunction:
    return CompiledFunction("Helper", "store", 0x14, [0x03E00008, 0x00000000], {})


def run(*functions: CompiledFunction, data: list[str] | None = None) -> str:
    obj = CompiledObject("store", list(functions), data or [])
    return splice(ASM, [obj], Names.load(CSV), original_sizes(CSV))


def test_splice_replaces_lines_keeping_original_operands():
    out = run(store(), helper()).splitlines()
    assert out[0] == "glabel Store"
    assert out[1] == "    /* 00101A30 from C (store.c) */  lui        $v0, %hi(D_00139E00)"
    assert out[3] == "    /* 00101A38 from C (store.c) */  sw         $v0, %gp_rel(D_00139E04)($gp)"
    assert out[4] == "    /* 00101A3C from C (store.c) */  jal        func_00101000"
    assert out[5] == "    /* 00101A40 from C (store.c) */  .word 0x00000000"
    assert out[6] == "    /* 00101A44 from C (store.c) */  .word 0x03E00008"


def test_splice_leaves_other_lines_alone():
    out = run(helper()).splitlines()
    assert out[1] == line(*ORIGINAL[0])
    assert out[6].endswith(".word 0x03E00008")


@pytest.mark.parametrize(
    ("changes", "message"),
    [
        ({"words": {4: 0x24020001}}, "instruction"),
        ({"words": {2: 0xAF830000}}, "instruction"),
        ({"relocs": {2: Reloc(R_MIPS_GPREL16, "D_00139E08", "")}}, "target D_00139E08"),
        ({"relocs": {3: Reloc(R_MIPS_26, "func_00101008", "")}}, "target func_00101008"),
        (
            {"relocs": {1: Reloc(R_MIPS_GPREL16, "D_00139E00", "")}},
            "relocation %gp_rel, original %lo",
        ),
        ({"drop": [3]}, "the C nothing"),
        ({"relocs": {4: Reloc(R_MIPS_26, "func_00101000", "")}}, "the original nothing"),
    ],
)
def test_splice_refuses_mismatches(changes, message):
    with pytest.raises(SpliceError, match=message):
        run(store(**changes))


def test_hi16_addend_includes_paired_lo16():
    # The LO16's addend (-0x7E00) moves the target to another %hi.
    fn = store(words={0: 0x3C020000, 1: 0x8C428200})
    with pytest.raises(SpliceError, match="target D_00139E00"):
        run(fn)


def test_section_relative_jump_is_placed_by_the_object():
    jal_helper = CompiledFunction(
        "Store",
        "store",
        0,
        [0x0C000000 | (0x14 >> 2)],
        {0: Reloc(R_MIPS_26, "", ".text")},
    )
    asm = "\n".join(
        [line(0x101A30, 0x0C040691, "jal        Helper"), line(*ORIGINAL[5]), line(*ORIGINAL[6])]
    )
    names = Names.load(CSV)
    obj = CompiledObject("store", [jal_helper, helper()], [])
    with pytest.raises(SpliceError, match="C is 0x4 bytes"):
        splice(asm, [obj], names, original_sizes(CSV))
    out = splice(asm, [obj], names, {})
    assert out.splitlines()[0].endswith("jal        Helper")


def test_splice_refuses_c_data():
    with pytest.raises(SpliceError, match=r"has data \(\.rodata\)"):
        run(store(), data=[".rodata"])


def test_splice_refuses_data_relocations():
    fn = store(relocs={0: Reloc(R_MIPS_HI16, "", ".rodata"), 1: Reloc(R_MIPS_LO16, "", ".rodata")})
    with pytest.raises(SpliceError, match="C data in .rodata"):
        run(fn)


def test_splice_refuses_unknown_and_duplicate_functions():
    unknown = CompiledFunction("Nowhere", "store", 0, [0], {})
    with pytest.raises(SpliceError, match="not in config/loader_functions.csv"):
        run(unknown)
    with pytest.raises(SpliceError, match="already placed"):
        run(helper(), helper())


def test_splice_refuses_wrong_size():
    short = store()
    short.words = short.words[:4]
    with pytest.raises(SpliceError, match="C is 0x10 bytes, the Original 0x14"):
        run(short)


def test_original_target():
    assert original_target("lui $v0, %hi(D_00139E00 + 0x4)") == (R_MIPS_HI16, "D_00139E00", 4)
    assert original_target("sw $a0, %gp_rel(errno - 8)($gp)") == (R_MIPS_GPREL16, "errno", -8)
    assert original_target("addiu $a0, $a0, %lo(D_1)") == (R_MIPS_LO16, "D_1", 0)
    assert original_target("jal        func_00101000") == (R_MIPS_26, "func_00101000", 0)
    assert original_target("j          .L00101A40") is None
    assert original_target("jal        0x101000") is None
    assert original_target("addiu      $a0, $a0, 0xF") is None


def test_same_target():
    assert same_target(R_MIPS_HI16, 0x13FFFF, 0x138000)
    assert not same_target(R_MIPS_HI16, 0x138000, 0x137FFF)
    assert same_target(R_MIPS_LO16, 0x10004, 0x20004)
    assert not same_target(R_MIPS_GPREL16, 0x139E04, 0x139E08)
    assert same_target(R_MIPS_26, 0x10101000, 0x00101000)  # same 256 MB region field
    assert not same_target(R_MIPS_26, 0x00101004, 0x00101000)


def test_names_prefer_list_then_symbol_addrs_then_placeholders():
    names = Names.load(CSV, "Store = 0x200000; // stale\n_gp = 0x141D70;\n")
    assert names.address("Store") == 0x101A30
    assert names.address("_gp") == 0x141D70
    assert names.address("D_00139E04") == 0x139E04
    assert names.address("errno") is None


def test_original_sizes_only_cover_original_names():
    assert original_sizes(CSV) == {"Store": 0x14, "Helper": 0x8}


def test_read_object_list(tmp_path):
    rsp = tmp_path / "x.rsp"
    rsp.write_text(json.dumps(["build/a b.o"]), encoding="utf-8")
    assert [str(p).replace("\\", "/") for p in read_object_list(rsp)] == ["build/a b.o"]
    rsp.write_text('"one.o"', encoding="utf-8")
    with pytest.raises(SpliceError, match="JSON list"):
        read_object_list(rsp)


def test_main_reports_errors(tmp_path, monkeypatch, capsys):
    monkeypatch.setattr(loader_splice, "LIST", tmp_path / "list.csv")
    monkeypatch.setattr(loader_splice, "SYMBOL_ADDRS", tmp_path / "symbols.txt")
    (tmp_path / "list.csv").write_text(CSV, encoding="utf-8")
    (tmp_path / "symbols.txt").write_text("", encoding="utf-8")
    (tmp_path / "asm.s").write_text(ASM, encoding="latin-1")
    rsp = tmp_path / "objects.rsp"
    rsp.write_text("{}", encoding="utf-8")
    out = tmp_path / "out.s"
    argv = ["--objects-file", str(rsp), "--asm", str(tmp_path / "asm.s"), "--out", str(out)]
    assert loader_splice.main(argv) == 1
    assert "error:" in capsys.readouterr().err
    assert not out.exists()
    rsp.write_text("[]", encoding="utf-8")
    assert loader_splice.main(argv) == 0
    assert out.read_text(encoding="latin-1") == ASM
