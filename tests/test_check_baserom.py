import hashlib
import json
from pathlib import Path

from tools.check_baserom import check, main, sha1_of


def write_config(tmp_path: Path, sha1: str | None) -> Path:
    config = {
        "elf_name": "GAME.ELF",
        "path": "baserom/GAME.ELF",
        "sha1": sha1,
    }
    config_path = tmp_path / "baserom.json"
    config_path.write_text(json.dumps(config), encoding="utf-8")
    return config_path


def write_rom(tmp_path: Path, data: bytes) -> str:
    rom = tmp_path / "baserom" / "GAME.ELF"
    rom.parent.mkdir()
    rom.write_bytes(data)
    return hashlib.sha1(data).hexdigest()


def test_sha1_of_matches_hashlib(tmp_path):
    expected = write_rom(tmp_path, b"colossus" * 1000)
    assert sha1_of(tmp_path / "baserom" / "GAME.ELF") == expected


def test_missing_rom_fails(tmp_path):
    ok, message = check(write_config(tmp_path, "abc"), tmp_path)
    assert not ok
    assert "Missing" in message


def test_unset_hash_fails_and_reports_actual(tmp_path):
    actual = write_rom(tmp_path, b"data")
    ok, message = check(write_config(tmp_path, None), tmp_path)
    assert not ok
    assert actual in message


def test_matching_hash_passes(tmp_path):
    actual = write_rom(tmp_path, b"data")
    ok, _ = check(write_config(tmp_path, actual.upper()), tmp_path)
    assert ok


def test_mismatched_hash_fails(tmp_path):
    write_rom(tmp_path, b"data")
    ok, message = check(write_config(tmp_path, "0" * 40), tmp_path)
    assert not ok
    assert "mismatch" in message


def test_main_exit_codes(tmp_path):
    actual = write_rom(tmp_path, b"data")
    good = write_config(tmp_path, actual)
    assert main(["--config", str(good), "--root", str(tmp_path)]) == 0
    bad = write_config(tmp_path, "0" * 40)
    assert main(["--config", str(bad), "--root", str(tmp_path)]) == 1
