import json
import shutil
import subprocess
import sys
from pathlib import Path

import configure
from configure import find_cross, generate, ninja_path, object_for


def test_ninja_regenerates_for_added_renamed_and_removed_c_sources(tmp_path):
    # Use the actual generator and Ninja, without disc data or PS2 tools. Only
    # build the manifest, so no compilation or binary parsing is necessary.
    shutil.copyfile(Path(configure.__file__), tmp_path / "configure.py")
    (tmp_path / configure.SPLAT_CONFIG).touch()
    (tmp_path / "iso").mkdir()
    (tmp_path / configure.BASE_ELF).touch()
    (tmp_path / "iso/KERNEL.XFF").touch()
    (tmp_path / "asm/cod").mkdir(parents=True)
    assembly = tmp_path / "asm/xff/KERNEL"
    assembly.mkdir(parents=True)
    (assembly / "KERNEL.s").touch()
    sources = tmp_path / "src/xff/KERNEL"
    sources.mkdir(parents=True)

    def run(*args):
        subprocess.run(
            [sys.executable, *args], cwd=tmp_path, check=True, capture_output=True, text=True
        )

    run("configure.py", "--cross", "test-")
    build = tmp_path / "build.ninja"
    initial_mtime = build.stat().st_mtime_ns
    inventory = tmp_path / configure.C_SOURCES_MANIFEST
    inventory_mtime = inventory.stat().st_mtime_ns
    run("-m", "ninja", "build.ninja")
    assert build.stat().st_mtime_ns == initial_mtime
    assert inventory.stat().st_mtime_ns == inventory_mtime

    source = sources / "added $name.c"
    source.write_text("void added(void) {}\n")
    run("-m", "ninja", "build.ninja")
    assert "build build/src/xff/KERNEL/added$ $$name.o: eecc" in build.read_text()
    source = source.rename(sources / "renamed.c")
    run("-m", "ninja", "build.ninja")
    assert "build build/src/xff/KERNEL/renamed.o: eecc" in build.read_text()
    assert "added$ $$name.o" not in build.read_text()
    source.unlink()
    run("-m", "ninja", "build.ninja")
    assert ": eecc " not in build.read_text()

    # Removal of the whole module source directory must work too.
    sources.rmdir()
    run("-m", "ninja", "build.ninja")
    assert ": eecc " not in build.read_text()


def test_splice_uses_response_file_for_large_object_lists(tmp_path, monkeypatch):
    source_dir = tmp_path / "src/xff/TEST"
    source_dir.mkdir(parents=True)
    names = [f"routine_{i:04d}_{'x' * 40}.c" for i in range(800)] + ["a $name.c"]
    for name in names:
        (source_dir / name).touch()
    monkeypatch.setattr(configure, "ROOT", tmp_path)
    ninja = generate("test-", [], ["TEST"])
    rule = ninja.split("rule splice\n", 1)[1].split("\n\n", 1)[0]
    command = rule.splitlines()[0]
    assert "--objects-file" in command
    assert "$in" not in command
    assert "rspfile_content = $objects_json" in rule
    assert len(command) < 200
    encoded = next(line for line in ninja.splitlines() if "  objects_json = " in line)
    objects = json.loads(encoded.split(" = ", 1)[1].replace("$$", "$"))
    expected = [f"build/src/xff/TEST/{Path(name).stem}.o" for name in sorted(names)]
    assert objects == expected
    assert len(json.dumps(objects)) > 32767
    assert "build build/src/xff/TEST/a$ $$name.o: eecc" in ninja


def test_c_objects_depend_on_compiler_wrappers(tmp_path, monkeypatch):
    source_dir = tmp_path / "src/xff/TEST"
    source_dir.mkdir(parents=True)
    (source_dir / "f.c").touch()
    monkeypatch.setattr(configure, "ROOT", tmp_path)
    ninja = generate("test-", [], ["TEST"])
    edge = next(line for line in ninja.splitlines() if ": eecc " in line)
    implicit = edge.split(" | ", 1)[1].split()
    assert "tools/ee_cc.py" in implicit
    assert "tools/try_compilers.py" in implicit
    assert "config/ee_cflags.json" in implicit


def test_ninja_path_escapes_special_characters():
    assert ninja_path(Path("asm") / "a b.s") == "asm/a$ b.s"
    assert ninja_path("C:/x$y") == "C$:/x$$y"


def test_object_path_matches_splat_linker_script():
    assert object_for(Path("asm/cod/000000.s")).as_posix() == "build/asm/cod/000000.o"


def test_explicit_cross_prefix_wins():
    assert find_cross("my-prefix-") == "my-prefix-"


def test_generate_wires_every_source_into_the_link(tmp_path, monkeypatch):
    monkeypatch.setattr(configure, "ROOT", tmp_path)  # no Loader C
    sources = [Path("asm/cod/000000.s"), Path("asm/data/cod/031C00.data.s")]
    ninja = generate("mips64r5900el-ps2-elf-", sources)
    assert "build build/asm/cod/000000.o: as asm/cod/000000.s" in ninja
    assert "build/asm/data/cod/031C00.data.o" in ninja.split("build build/SCUS_974.72.elf")[1]
    assert "build check-elf: check build/SCUS_974.72.rom iso/SCUS_974.72.rom" in ninja
    assert "build check: phony check-elf" in ninja


def test_generate_adds_xff_module_checks():
    # A module without decompiled C (none in src/xff/TESTMOD) assembles its split directly.
    ninja = generate("mips64r5900el-ps2-elf-", [], ["TESTMOD"])
    assert "build build/xff/TESTMOD.o: xff2elf iso/TESTMOD.XFF" in ninja
    assert "build check-TESTMOD: xffcheck build/xff/TESTMOD.o build/xff/TESTMOD/TESTMOD.o" in ninja
    assert "build check: phony check-elf check-TESTMOD" in ninja
    assert "  asflags = $asflags -I asm/xff/TESTMOD" in ninja
    assert "cross = mips64r5900el-ps2-elf-" in ninja
    assert "ld -m elf32lr5900 " in ninja
    assert "command = $python tools/xff_rebuild.py $in $out" in ninja
    assert (
        "build build/xff/TESTMOD.XFF: xffrebuild build/xff/TESTMOD/TESTMOD.o iso/TESTMOD.XFF"
        " | tools/xff_rebuild.py tools/xff2.py"
    ) in ninja
    assert "build check-XFF-TESTMOD: check build/xff/TESTMOD.XFF iso/TESTMOD.XFF" in ninja
    assert "build check: phony check-elf check-TESTMOD check-XFF-TESTMOD" in ninja
    assert "default build/SCUS_974.72.rom build/xff/TESTMOD.XFF" in ninja


def test_loader_c_is_spliced_into_the_loader_asm(tmp_path, monkeypatch):
    (tmp_path / "src/loader").mkdir(parents=True)
    (tmp_path / "src/loader/a $name.c").touch()
    monkeypatch.setattr(configure, "ROOT", tmp_path)
    ninja = generate("test-", [Path("asm/cod/000000.s"), Path("asm/data/cod/031C00.data.s")])
    assert "build build/src/loader/a$ $$name.o: eecc src/loader/a$ $$name.c" in ninja
    splice = next(line for line in ninja.splitlines() if ": loader_splice " in line)
    assert splice.startswith("build build/loader/000000.s: loader_splice build/src/loader/a$ ")
    implicit = splice.split(" | ", 1)[1].split()
    assert implicit[0] == "asm/cod/000000.s"
    assert "config/loader_functions.csv" in implicit
    assert "  objects_json = " + json.dumps(["build/src/loader/a $$name.o"]) in ninja
    assert "build build/asm/cod/000000.o: as build/loader/000000.s" in ninja
    assert "build build/asm/data/cod/031C00.data.o: as asm/data/cod/031C00.data.s" in ninja


def test_loader_without_c_assembles_its_split_directly(tmp_path, monkeypatch):
    monkeypatch.setattr(configure, "ROOT", tmp_path)
    ninja = generate("test-", [Path("asm/cod/000000.s")])
    assert "loader_splice build" not in ninja
    assert "build build/asm/cod/000000.o: as asm/cod/000000.s" in ninja
