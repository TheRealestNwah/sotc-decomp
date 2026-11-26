"""include/ staging for C that #includes project headers (synthetic files only)."""

import subprocess
from pathlib import Path

from tools import ee_cc
from tools.ee_cc import LINUX_PIPELINE, depfile_text
from tools.try_compilers import STAGE_INCLUDE, include_dir_for, included_headers


def make_tree(root: Path) -> Path:
    inc = root / "include"
    (inc / "gamecore").mkdir(parents=True)
    (inc / "common.h").write_text("typedef int s32;\n", encoding="utf-8")
    (inc / "gamecore/x.h").write_text('#include "common.h"\nextern s32 x;\n', encoding="utf-8")
    return inc


def test_headers_are_found_recursively(tmp_path):
    inc = make_tree(tmp_path)
    src = tmp_path / "f.c"
    src.write_text('  #  include "gamecore/x.h"\n#include <stdio.h>\nint f(void){return 0;}\n')
    assert included_headers(src, inc) == [inc / "gamecore/x.h", inc / "common.h"]
    assert include_dir_for(src, inc) == inc


def test_source_without_project_headers_is_not_staged(tmp_path):
    inc = make_tree(tmp_path)
    src = tmp_path / "f.c"
    src.write_text('#include "missing.h"\n#include <stdio.h>\nint f(void){return 0;}\n')
    assert included_headers(src, inc) == []
    assert include_dir_for(src, inc) is None


def test_include_cycles_terminate(tmp_path):
    inc = tmp_path / "include"
    inc.mkdir()
    (inc / "a.h").write_text('#include "b.h"\n')
    (inc / "b.h").write_text('#include "a.h"\n')
    src = tmp_path / "f.c"
    src.write_text('#include "a.h"\n')
    assert included_headers(src, inc) == [inc / "a.h", inc / "b.h"]


def test_depfile_lists_source_and_headers(tmp_path):
    inc = make_tree(tmp_path)
    src = tmp_path / "src dir/f.c"
    src.parent.mkdir()
    src.write_text('#include "gamecore/x.h"\n')
    text = depfile_text(src, tmp_path / "build/f.o", tmp_path)
    assert text == ("build/f.o: src\\ dir/f.c include/gamecore/x.h include/common.h\n")
    assert inc.exists()


def test_pipeline_stages_include_before_compiling():
    assert "@STAGE_INCLUDE@" not in LINUX_PIPELINE
    assert LINUX_PIPELINE.index(STAGE_INCLUDE) < LINUX_PIPELINE.index("$cc1")


def test_stage_script_copies_include_and_prepends_flag(tmp_path):
    if subprocess.run(["bash", "-c", "true"], capture_output=True).returncode:
        return
    inc = make_tree(tmp_path)
    work = tmp_path / "work"
    work.mkdir()
    script = f'work="$1"; shift; {STAGE_INCLUDE} printf "%s\n" "$@"; ls "$work/include"'
    out = subprocess.run(
        ["bash", "-c", script, "x", work.as_posix(), "-O2"],
        capture_output=True, text=True, env={"inc": inc.as_posix(), "PATH": "/usr/bin:/bin"},
    ).stdout.split()  # fmt: skip
    assert out[:2] == [f"-I{work.as_posix()}/include", "-O2"]
    assert "common.h" in out and "gamecore" in out


def test_main_writes_depfile(tmp_path, monkeypatch):
    make_tree(tmp_path)
    src = tmp_path / "f.c"
    src.write_text('#include "common.h"\n')
    monkeypatch.setattr(ee_cc, "ROOT", tmp_path)
    monkeypatch.setattr(ee_cc, "build", lambda *a, **k: None)
    dep = tmp_path / "out/f.o.d"
    assert ee_cc.main([str(src), str(tmp_path / "out/f.o"), "--depfile", str(dep)]) == 0
    assert dep.read_text() == "out/f.o: f.c include/common.h\n"
