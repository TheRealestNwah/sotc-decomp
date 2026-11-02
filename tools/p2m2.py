"""Read and write PCSX2 Input Recording files (.p2m2, file version 1).

Layout: a 570-byte header, then one 36-byte frame per vsync (two ports of
18 bytes). Each port holds two active-low button bytes (a 0 bit is a pressed
button), right and left stick X/Y, and twelve pressure bytes.
"""

from __future__ import annotations

import struct
from dataclasses import dataclass, field

HEADER_SIZE = 570
PAD_SIZE = 18
FRAME_SIZE = 2 * PAD_SIZE
VERSION = 1

# Bit 0 first.
BUTTONS_ONE = ("select", "l3", "r3", "start", "up", "right", "down", "left")
BUTTONS_TWO = ("l2", "r2", "l1", "r1", "triangle", "circle", "cross", "square")
PRESSURES = (
    "right", "left", "up", "down", "triangle", "circle", "cross", "square",
    "l1", "r1", "l2", "r2",
)  # fmt: skip

NEUTRAL_PAD = bytes([0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F]) + bytes(12)


@dataclass(frozen=True)
class Pad:
    raw: bytes = NEUTRAL_PAD

    @property
    def pressed(self) -> frozenset[str]:
        names = [n for i, n in enumerate(BUTTONS_ONE) if not self.raw[0] >> i & 1]
        names += [n for i, n in enumerate(BUTTONS_TWO) if not self.raw[1] >> i & 1]
        return frozenset(names)

    @property
    def right_stick(self) -> tuple[int, int]:
        return self.raw[2], self.raw[3]

    @property
    def left_stick(self) -> tuple[int, int]:
        return self.raw[4], self.raw[5]

    @property
    def pressures(self) -> dict[str, int]:
        return dict(zip(PRESSURES, self.raw[6:18], strict=True))

    @classmethod
    def make(cls, pressed=(), left=(0x7F, 0x7F), right=(0x7F, 0x7F)) -> Pad:
        one = 0xFF & ~sum(1 << i for i, n in enumerate(BUTTONS_ONE) if n in pressed)
        two = 0xFF & ~sum(1 << i for i, n in enumerate(BUTTONS_TWO) if n in pressed)
        pressure = bytes(0xFF if n in pressed else 0 for n in PRESSURES)
        return cls(bytes([one, two, *right, *left]) + pressure)


@dataclass
class Recording:
    emulator: str = ""
    author: str = ""
    game: str = ""
    undo_count: int = 0
    frames: list[tuple[Pad, Pad]] = field(default_factory=list)


def _text(data: bytes) -> str:
    return data.split(b"\0")[0].decode("utf-8", "replace")


def parse(data: bytes) -> Recording:
    if len(data) < HEADER_SIZE or data[0] != VERSION:
        raise ValueError("not a version 1 .p2m2 Input Recording file")
    total, undo = struct.unpack_from("<II", data, 561)
    available = (len(data) - HEADER_SIZE) // FRAME_SIZE
    if available < total:
        raise ValueError(f"header says {total} frames but the file holds {available}")
    frames = []
    for i in range(total):
        off = HEADER_SIZE + i * FRAME_SIZE
        frames.append(
            (Pad(data[off : off + PAD_SIZE]), Pad(data[off + PAD_SIZE : off + FRAME_SIZE]))
        )
    return Recording(_text(data[1:51]), _text(data[51:306]), _text(data[306:561]), undo, frames)


def write(rec: Recording) -> bytes:
    header = struct.pack(
        "<B50s255s255sIIB",
        VERSION,
        rec.emulator.encode(),
        rec.author.encode(),
        rec.game.encode(),
        len(rec.frames),
        rec.undo_count,
        0,
    )
    return header + b"".join(p1.raw + p2.raw for p1, p2 in rec.frames)
