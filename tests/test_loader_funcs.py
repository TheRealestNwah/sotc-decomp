from tools.loader_funcs import GAME, SDK, build, classify, splat_functions, to_csv

ASM = """\
nonmatching func_001000D0, 0x10

glabel func_001000D0
    /* D0 001000D0 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* D4 001000D4 0800E003 */  jr         $ra
    /* D8 001000D8 00000000 */   nop
    /* DC 001000DC 00000000 */  nop
endlabel func_001000D0

nonmatching func_001000E0, 0x18

glabel func_001000E0
    /* E0 001000E0 0800E003 */  jr         $ra
    /* E4 001000E4 00000000 */   nop
    /* E8 001000E8 0800E003 */  jr         $ra
    /* EC 001000EC 00000000 */   nop
    /* F0 001000F0 0800E003 */  jr         $ra
    /* F4 001000F4 00000000 */   nop
endlabel func_001000E0
"""


def test_splat_functions():
    funcs, words = splat_functions(ASM)
    assert funcs == [(0x1000D0, 0x10, "func_001000D0"), (0x1000E0, 0x18, "func_001000E0")]
    assert words[0x1000D0] == 0x27BDFFE0
    assert words[0x1000DC] == 0


def test_classify_blocks():
    assert classify(0x100010) == (SDK, "crt0")
    assert classify(0x1000D0) == (GAME, "loader")
    assert classify(0x106BB8) == (GAME, "loader")
    assert classify(0x106BC0) == (SDK, "libkernl")
    assert classify(0x127448) == (SDK, "libc")


def test_build_uses_original_names_and_splits():
    funcs, words = splat_functions(ASM)
    # First function: Original size 8 leaves only nops, so no tail row.
    # Second: Original ends at 0xE8 with code after it, and a second Original
    # function starts mid-way at 0xF0 (splat merged it).
    original = {0x1000D0: (0x8, "Foo"), 0x1000E0: (0x8, "Bar"), 0x1000F0: (0x8, "Baz")}
    rows = build(funcs, words, original)
    assert [(r.address, r.size, r.name) for r in rows] == [
        (0x1000D0, 0x8, "Foo"),
        (0x1000E0, 0x8, "Bar"),
        (0x1000E8, 0x8, "func_001000E8"),
        (0x1000F0, 0x8, "Baz"),
    ]
    assert "merged" in rows[3].note
    assert rows[2].note.startswith("no Original name")
    assert all(r.cls == GAME for r in rows)


def test_to_csv():
    funcs, words = splat_functions(ASM)
    text = to_csv(build(funcs, words, {}))
    assert text.splitlines()[0] == "address,size,name,class,library,evidence"
    assert text.splitlines()[1].startswith("0x001000D0,0x10,func_001000D0,game,loader,")
