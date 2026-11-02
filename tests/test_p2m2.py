import pytest

from tools.p2m2 import FRAME_SIZE, HEADER_SIZE, NEUTRAL_PAD, Pad, Recording, parse, write


def test_round_trip_and_layout():
    rec = Recording("PCSX2-v2.7.81", "Nick", "Shadow of the Colossus")
    rec.frames = [(Pad(), Pad()), (Pad.make({"cross", "up"}, left=(0, 0xFF)), Pad())]
    data = write(rec)
    assert len(data) == HEADER_SIZE + 2 * FRAME_SIZE
    back = parse(data)
    assert back.game == "Shadow of the Colossus" and back.author == "Nick"
    assert [p.raw for p, _ in back.frames] == [p.raw for p, _ in rec.frames]


def test_buttons_are_active_low():
    assert Pad(NEUTRAL_PAD).pressed == frozenset()
    pad = Pad.make({"cross", "up", "start"}, left=(1, 2), right=(3, 4))
    assert pad.raw[0] == 0xFF & ~(1 << 4) & ~(1 << 3)
    assert pad.raw[1] == 0xFF & ~(1 << 6)
    assert pad.pressed == {"cross", "up", "start"}
    assert pad.left_stick == (1, 2) and pad.right_stick == (3, 4)
    assert pad.pressures["cross"] == 0xFF and pad.pressures["circle"] == 0


def test_truncated_file_is_rejected():
    rec = Recording(frames=[(Pad(), Pad())] * 3)
    with pytest.raises(ValueError):
        parse(write(rec)[:-1])
    with pytest.raises(ValueError):
        parse(b"\x02" + bytes(600))
