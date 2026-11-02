"""Minimal client for PCSX2's PINE IPC (TCP on 127.0.0.1, port = slot).

A message is a u32 little-endian total length (counting the length itself)
followed by one or more commands. The reply is a u32 length, a u8 result
(0 OK, 0xFF fail) and each command's payload in order, so many reads can share
one round trip. PCSX2 serves memory reads from its IPC thread without pausing
emulation: a batch is not atomic with a frame. Callers that need a consistent
snapshot read a frame counter at both ends of the batch and retry on change.

Enable it in PCSX2 under Settings > Advanced > PINE Settings.
"""

from __future__ import annotations

import socket
import struct

DEFAULT_SLOT = 28011

OP_READ = {1: 0, 2: 1, 4: 2, 8: 3}
OP_VERSION = 8
OP_TITLE = 0xB
OP_ID = 0xC
OP_UUID = 0xD
OP_GAME_VERSION = 0xE
OP_STATUS = 0xF

RESULT_OK = 0
MAX_IPC_SIZE = 650000
MAX_IPC_RETURN_SIZE = 450000

STATUS_NAMES = {0: "running", 1: "paused", 2: "shutdown"}


class PineError(RuntimeError):
    pass


def read_command(width: int, address: int) -> bytes:
    return struct.pack("<BI", OP_READ[width], address)


def frame(commands: list[bytes]) -> bytes:
    body = b"".join(commands)
    return struct.pack("<I", len(body) + 4) + body


def chunk_reads(reads: list[tuple[int, int]]) -> list[list[tuple[int, int]]]:
    """Split (address, width) reads into batches that fit PINE's buffers."""
    batches, batch, request, reply = [], [], 4, 5
    for address, width in reads:
        if batch and (request + 5 > MAX_IPC_SIZE or reply + width > MAX_IPC_RETURN_SIZE):
            batches.append(batch)
            batch, request, reply = [], 4, 5
        batch.append((address, width))
        request += 5
        reply += width
    if batch:
        batches.append(batch)
    return batches


class Pine:
    def __init__(self, slot: int = DEFAULT_SLOT, host: str = "127.0.0.1", timeout: float = 10.0):
        self.sock = socket.create_connection((host, slot), timeout=timeout)

    def close(self) -> None:
        self.sock.close()

    def __enter__(self) -> Pine:
        return self

    def __exit__(self, *exc) -> None:
        self.close()

    def _recv_exact(self, size: int) -> bytes:
        data = bytearray()
        while len(data) < size:
            chunk = self.sock.recv(size - len(data))
            if not chunk:
                raise PineError("PCSX2 closed the PINE connection")
            data += chunk
        return bytes(data)

    def call(self, commands: list[bytes]) -> bytes:
        """Send one framed message and return the reply payload after the result byte."""
        self.sock.sendall(frame(commands))
        (length,) = struct.unpack("<I", self._recv_exact(4))
        reply = self._recv_exact(length - 4)
        if not reply or reply[0] != RESULT_OK:
            raise PineError("PINE request failed (is a game running?)")
        return reply[1:]

    def read(self, reads: list[tuple[int, int]]) -> list[int]:
        """Read unsigned little-endian values for (address, width) pairs."""
        values: list[int] = []
        for batch in chunk_reads(reads):
            payload = self.call([read_command(w, a) for a, w in batch])
            pos = 0
            for _, width in batch:
                values.append(int.from_bytes(payload[pos : pos + width], "little"))
                pos += width
        return values

    def read_block(self, address: int, size: int) -> bytes:
        """Read `size` bytes starting at `address` using aligned 64-bit reads."""
        start = address & ~7
        end = (address + size + 7) & ~7
        words = self.read([(a, 8) for a in range(start, end, 8)])
        data = b"".join(w.to_bytes(8, "little") for w in words)
        return data[address - start : address - start + size]

    def _string(self, op: int) -> str:
        payload = self.call([bytes([op])])
        (length,) = struct.unpack_from("<I", payload)
        return payload[4 : 4 + length].split(b"\0")[0].decode("utf-8", "replace")

    def version(self) -> str:
        return self._string(OP_VERSION)

    def title(self) -> str:
        return self._string(OP_TITLE)

    def game_id(self) -> str:
        return self._string(OP_ID)

    def game_version(self) -> str:
        return self._string(OP_GAME_VERSION)

    def status(self) -> str:
        (value,) = struct.unpack("<I", self.call([bytes([OP_STATUS])])[:4])
        return STATUS_NAMES.get(value, str(value))
