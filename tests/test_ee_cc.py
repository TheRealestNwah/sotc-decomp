import json
from pathlib import Path

import pytest

from tools import ee_cc


def configure_flags(root, settings):
    (root / "config").mkdir()
    (root / "config/ee_cflags.json").write_text(json.dumps(settings), encoding="utf-8")


def test_override_is_limited_to_selected_source(tmp_path, monkeypatch):
    configure_flags(tmp_path, {"src/xff/MANAGER/demo.c": ["-fno-strict-aliasing"]})
    monkeypatch.chdir(tmp_path)
    selected = Path("src/xff/MANAGER/demo.c")
    expected = ["-O2", "-G0", "-fno-strict-aliasing"]
    assert ee_cc.source_cflags(selected, tmp_path) == expected
    assert ee_cc.source_cflags(selected.resolve(), tmp_path) == expected
    assert ee_cc.source_cflags(Path("src/xff/KERNEL/demo.c"), tmp_path) == ["-O2", "-G0"]
    assert ee_cc.source_cflags(tmp_path.parent / "demo.c", tmp_path) == ["-O2", "-G0"]
    assert ee_cc.CFLAGS == ["-O2", "-G0"]


def test_build_passes_selected_flags_to_original_compiler(tmp_path, monkeypatch):
    configure_flags(tmp_path, {"demo.c": ["-fno-strict-aliasing"]})
    monkeypatch.setattr(ee_cc, "ROOT", tmp_path)
    monkeypatch.setattr(ee_cc, "find_package_as", lambda _: tmp_path / "ee-as")
    calls = []
    monkeypatch.setattr(ee_cc, "compile_c", lambda *args: calls.append(args))
    monkeypatch.setattr(ee_cc, "assemble", lambda *args: None)
    assert ee_cc.build(tmp_path / "demo.c", tmp_path / "build/demo.o", tmp_path / "cc") is None
    assert calls[0][2] == ["-O2", "-G0", "-fno-strict-aliasing"]


def test_rejects_string_in_place_of_flag_list(tmp_path):
    configure_flags(tmp_path, {"demo.c": "-fno-strict-aliasing"})
    with pytest.raises(ValueError, match="list of strings"):
        ee_cc.source_cflags(tmp_path / "demo.c", tmp_path)


def test_loader_sources_use_small_data(tmp_path, monkeypatch):
    # The Loader's Game code reads its globals through $gp (docs/findings.md).
    configure_flags(tmp_path, {})
    monkeypatch.chdir(tmp_path)
    flags = ee_cc.source_cflags(Path("src/loader/demo.c"), tmp_path)
    assert flags == ["-O2", "-G8"]
    assert ee_cc.small_data_limit(flags) == 8
    assert ee_cc.small_data_limit(["-O2", "-G0", "-G4"]) == 4
    assert ee_cc.small_data_limit(["-O2"]) == 0
