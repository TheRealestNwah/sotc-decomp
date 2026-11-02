import json
import struct

import pytest
from refrun_helpers import FakePCSX2, load_into, make_module

from tools import refrun
from tools.pine import Pine

RAM_BASE = 0x100000
TEXT, DATA, BSS = 0x104000, 0x104800, 0x104A00


def loaded_ram() -> tuple[bytearray, object]:
    module = make_module()
    ram = bytearray(0x8000)
    load_into(ram, RAM_BASE, module, {1: TEXT, 2: DATA, 3: BSS})
    return ram, module


def test_locate_finds_text_by_signature_and_the_rest_by_relocations():
    ram, module = loaded_ram()
    assert refrun.locate(module, bytes(ram), RAM_BASE) == {
        ".text": TEXT,
        ".data": DATA,
        ".bss": BSS,
    }


def test_locate_returns_nothing_before_the_module_loads():
    assert refrun.locate(make_module(), bytes(0x8000), RAM_BASE) == {}


def test_locate_rejects_ambiguous_signature():
    ram, module = loaded_ram()
    text = module.sections[1].data
    ram[0x6000 : 0x6000 + len(text)] = text  # a second copy of every window
    assert refrun.locate(module, bytes(ram), RAM_BASE) == {}


MAP = """
schema = 1
[frame]
name = "vsync"
module = "TEST"
section = ".data"
offset = 4
type = "u32"

[[field]]
name = "counter"
module = "TEST"
symbol = "counter"
type = "s32"

[[field]]
name = "raw"
address = 0x104A20
type = "bytes"
size = 3
count = 2

[[field]]
name = "speed"
module = "TEST"
section = ".bss"
offset = 0x30
type = "f32"
"""


def write_map(tmp_path, text=MAP):
    path = tmp_path / "state.toml"
    path.write_text(text)
    return path


def test_load_map_and_addresses(tmp_path):
    frame, fields = refrun.load_map(write_map(tmp_path))
    modules = {"TEST": make_module()}
    bases = {"TEST": {".text": TEXT, ".data": DATA, ".bss": BSS}}
    assert refrun.address_of(frame, modules, bases) == DATA + 4
    assert [refrun.address_of(f, modules, bases) for f in fields] == [
        BSS + 0x10,
        0x104A20,
        BSS + 0x30,
    ]
    with pytest.raises(LookupError):
        refrun.address_of(fields[0], modules, {"TEST": {}})


@pytest.mark.parametrize(
    "text",
    [
        MAP.replace("schema = 1", "schema = 2"),
        MAP.replace('type = "s32"', 'type = "i32"'),
        MAP.replace("size = 3\n", ""),
        MAP.replace('name = "raw"', 'name = "counter"'),
        MAP.replace(
            'section = ".data"\noffset = 4\ntype = "u32"', 'section = ".data"\ntype = "f32"'
        ),
    ],
)
def test_bad_maps_are_rejected(tmp_path, text):
    with pytest.raises(ValueError):
        refrun.load_map(write_map(tmp_path, text))


def test_record_writes_one_row_per_frame(tmp_path, monkeypatch):
    ram, module = loaded_ram()
    monkeypatch.setattr(refrun, "EE_RAM", (RAM_BASE, RAM_BASE + len(ram)))
    struct.pack_into("<f", ram, BSS + 0x30 - RAM_BASE, 1.5)
    ram[0x104A20 - RAM_BASE : 0x104A26 - RAM_BASE] = b"abcdef"
    server = FakePCSX2(ram, RAM_BASE)
    requests = 0

    def tick():  # advance the game one frame every third request
        nonlocal requests
        requests += 1
        if requests % 3 == 0:
            vsync = struct.unpack_from("<I", ram, DATA + 4 - RAM_BASE)[0]
            struct.pack_into("<I", ram, DATA + 4 - RAM_BASE, vsync + 1)
            struct.pack_into("<i", ram, BSS + 0x10 - RAM_BASE, -vsync)

    server.on_request = tick
    run = tmp_path / "run"
    run.mkdir()
    try:
        with Pine(server.port) as pine:
            stats = refrun.record(
                pine, run, write_map(tmp_path), {"TEST": module}, max_frames=5, log=lambda _: None
            )
    finally:
        server.close()
    rows = [json.loads(line) for line in (run / "state.jsonl").read_text().splitlines()]
    assert stats["frames"] == len(rows) == 5
    frames = [r["frame"] for r in rows]
    assert frames == sorted(set(frames))
    for row in rows:
        assert row["fields"]["raw"] == ["616263", "646566"]
        assert row["fields"]["speed"] == 1.5
    assert stats["module_bases"]["TEST"][".bss"] == BSS


def test_diff_reports_first_divergence():
    a = {1: {"x": 1, "y": 2}, 2: {"x": 2, "y": 2}, 3: {"x": 3, "y": 3}}
    assert refrun.diff(a, a) is None
    b = {1: {"x": 1, "y": 2}, 2: {"x": 2, "y": 9}, 3: {"x": 0, "y": 3}}
    assert refrun.diff(a, b) == {"frame": 2, "missing": False, "fields": {"y": (2, 9)}}
    assert refrun.diff(a, b, only=["x"])["frame"] == 3
    assert refrun.diff(a, {1: a[1], 3: a[3]})["missing"] is True
    assert refrun.diff(a, {1: a[1]}) is None  # a shorter run that agrees so far


def test_diff_cli(tmp_path, capsys):
    for name, y in (("a", 2), ("b", 3)):
        (tmp_path / name).mkdir()
        rows = [{"frame": 1, "fields": {"y": 2}}, {"frame": 2, "fields": {"y": y}}]
        (tmp_path / name / "state.jsonl").write_text("".join(json.dumps(r) + "\n" for r in rows))
    assert refrun.main(["diff", str(tmp_path / "a"), str(tmp_path / "a")]) == 0
    assert refrun.main(["diff", str(tmp_path / "a"), str(tmp_path / "b")]) == 1
    assert "frame 2" in capsys.readouterr().out


def test_sha1_tree_covers_names_and_contents(tmp_path):
    (tmp_path / "card").mkdir()
    (tmp_path / "card" / "a").write_bytes(b"1")
    first = refrun.sha1_tree(tmp_path / "card")
    (tmp_path / "card" / "a").rename(tmp_path / "card" / "b")
    assert refrun.sha1_tree(tmp_path / "card") != first
