"""Shared fakes for the Reference run tests: a loaded-module RAM image and a PINE server."""

from __future__ import annotations

import socket
import struct
import threading

from tools import pine as pine_mod
from tools import xff2


def _sext16(v: int) -> int:
    return v - 0x10000 if v & 0x8000 else v


def load_into(ram: bytearray, ram_base: int, module: xff2.Module, bases: dict[int, int]) -> None:
    """Copy a module's sections into RAM at `bases` and apply its local relocations."""
    for index, base in bases.items():
        sec = module.sections[index]
        if sec.type == xff2.SHT_PROGBITS:
            ram[base - ram_base : base - ram_base + len(sec.data)] = sec.data

    def put(section: int, offset: int, value: int) -> None:
        struct.pack_into("<I", ram, bases[section] + offset - ram_base, value & 0xFFFFFFFF)

    for table in module.reltables:
        if table.is_import or table.target not in bases:
            continue
        his: list[tuple[int, int]] = []
        for offset, info, saved, _ in table.entries:
            kind, sym = info & 0xFF, info >> 8
            _, value, _, _, _, shndx = module.symbol(sym)
            target = bases.get(shndx, 0) + value
            if kind == 2:
                put(table.target, offset, saved + target)
            elif kind == 4:
                field = ((saved & 0x3FFFFFF) << 2) + target
                put(table.target, offset, (saved & ~0x3FFFFFF) | ((field >> 2) & 0x3FFFFFF))
            elif kind == 5:
                his.append((offset, saved))
            elif kind == 6:
                for hi_off, hi_saved in his:
                    total = ((hi_saved & 0xFFFF) << 16) + _sext16(saved & 0xFFFF) + target
                    high = (total + 0x8000) >> 16 & 0xFFFF
                    put(table.target, hi_off, (hi_saved & ~0xFFFF) | high)
                    put(table.target, offset, (saved & ~0xFFFF) | (total & 0xFFFF))
                his = []


class FakePCSX2:
    """A PINE server over a RAM bytearray. `on_request` runs before each reply."""

    def __init__(self, ram: bytearray, ram_base: int = 0, game_id: str = "SCUS-97472"):
        self.ram, self.ram_base, self.game_id = ram, ram_base, game_id
        self.on_request = lambda: None
        self.server = socket.create_server(("127.0.0.1", 0))
        self.port = self.server.getsockname()[1]
        self.thread = threading.Thread(target=self._serve, daemon=True)
        self.thread.start()

    def _string(self, text: str) -> bytes:
        raw = text.encode() + b"\0"
        return struct.pack("<I", len(raw)) + raw

    def _reply(self, body: bytes) -> bytes:
        self.on_request()
        out, pos = bytearray(), 0
        while pos < len(body):
            op = body[pos]
            pos += 1
            widths = {v: k for k, v in pine_mod.OP_READ.items()}
            if op in widths:
                (addr,) = struct.unpack_from("<I", body, pos)
                pos += 4
                start = addr - self.ram_base
                out += bytes(self.ram[start : start + widths[op]])
            elif op == pine_mod.OP_VERSION:
                out += self._string("PCSX2 Fake")
            elif op == pine_mod.OP_TITLE:
                out += self._string("Shadow of the Colossus")
            elif op == pine_mod.OP_ID:
                out += self._string(self.game_id)
            elif op == pine_mod.OP_STATUS:
                out += struct.pack("<I", 0)
            else:
                return struct.pack("<IB", 5, 0xFF)
        return struct.pack("<IB", len(out) + 5, 0) + out

    def _serve(self) -> None:
        conn, _ = self.server.accept()
        with conn:
            buf = b""
            while True:
                while len(buf) < 4 or len(buf) < struct.unpack_from("<I", buf)[0]:
                    chunk = conn.recv(1 << 20)
                    if not chunk:
                        return
                    buf += chunk
                (length,) = struct.unpack_from("<I", buf)
                conn.sendall(self._reply(buf[4:length]))
                buf = buf[length:]

    def close(self) -> None:
        self.server.close()


def make_module() -> xff2.Module:
    """A module with .text (lui/addiu to .bss and .data), .data (a word to .bss) and .bss.

    Symbol 1 is the global `counter` at .bss + 0x10.
    """
    import random

    names = ["", ".text", ".data", ".bss", ".shstrtab", ".symtab", ".strtab"]
    shstrtab, offs = b"\0", [0]
    for name in names[1:]:
        offs.append(len(shstrtab))
        shstrtab += name.encode() + b"\0"
    strtab = b"\0counter\0"
    symbols = bytes(16) + struct.pack("<IIIBBH", 1, 0x10, 4, 0x11, 0, 3)
    for shndx in (1, 2, 3):  # section symbols 2, 3, 4
        symbols += struct.pack("<IIIBBH", 0, 0, 0, 0x03, 0, shndx)
    rng = random.Random(7)
    text = bytearray(rng.randbytes(0x200))
    hi, lo = 0x3C020000, 0x24420010  # lui v0, 0 ; addiu v0, v0, 0x10
    struct.pack_into("<II", text, 0x100, hi, lo)
    struct.pack_into("<II", text, 0x108, 0x3C030000, 0x24630004)  # .data + 4
    data = struct.pack("<II", 0x20, 0x1234)
    sections = [
        xff2.Section(0, 0, 0, 0),
        xff2.Section(offs[1], xff2.SHT_PROGBITS, len(text), 8, bytes(text)),
        xff2.Section(offs[2], xff2.SHT_PROGBITS, len(data), 16, data),
        xff2.Section(offs[3], xff2.SHT_NOBITS, 0x40, 16),
        xff2.Section(offs[4], 3, len(shstrtab), 1),
        xff2.Section(offs[5], 2, len(symbols), 4, symbols),
        xff2.Section(offs[6], 3, len(strtab), 1),
    ]
    reltables = [
        xff2.RelTable(1, False, [
            (0x100, (4 << 8) | 5, hi, 0), (0x104, (4 << 8) | 6, lo, 0),
            (0x108, (3 << 8) | 5, 0x3C030000, 0), (0x10C, (3 << 8) | 6, 0x24630004, 0),
        ]),
        xff2.RelTable(2, False, [(0x0, (4 << 8) | 2, 0x20, 0)]),
    ]  # fmt: skip
    return xff2.Module(
        sections=sections,
        shstrtab=shstrtab,
        strtab=strtab,
        symbols=symbols,
        reltables=reltables,
        imports=[],
        entry=0,
        num_locals=1,
    )
