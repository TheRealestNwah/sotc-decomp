from pathlib import Path

from configure import find_cross, generate, ninja_path, object_for


def test_ninja_path_escapes_special_characters():
    assert ninja_path(Path("asm") / "a b.s") == "asm/a$ b.s"
    assert ninja_path("C:/x$y") == "C$:/x$$y"


def test_object_path_matches_splat_linker_script():
    assert object_for(Path("asm/cod/000000.s")).as_posix() == "build/asm/cod/000000.o"


def test_explicit_cross_prefix_wins():
    assert find_cross("my-prefix-") == "my-prefix-"


def test_generate_wires_every_source_into_the_link():
    sources = [Path("asm/cod/000000.s"), Path("asm/data/cod/031C00.data.s")]
    ninja = generate("mips64r5900el-ps2-elf-", sources)
    assert "build build/asm/cod/000000.o: as asm/cod/000000.s" in ninja
    assert "build/asm/data/cod/031C00.data.o" in ninja.split("build build/SCUS_974.72.elf")[1]
    assert "build check: check build/SCUS_974.72.rom iso/SCUS_974.72.rom" in ninja
    assert "cross = mips64r5900el-ps2-elf-" in ninja
