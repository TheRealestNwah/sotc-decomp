import struct

import pytest

from tests.refrun_helpers import FakePCSX2
from tools.pine import MAX_IPC_RETURN_SIZE, Pine, PineError, chunk_reads, frame, read_command


def test_frame_counts_its_own_length():
    msg = frame([read_command(4, 0x100000), read_command(1, 0x10)])
    assert struct.unpack_from("<I", msg)[0] == len(msg) == 14
    assert msg[4:9] == bytes([2]) + struct.pack("<I", 0x100000)


def test_chunk_reads_respects_reply_limit():
    reads = [(i * 8, 8) for i in range(120000)]
    batches = chunk_reads(reads)
    assert sum(len(b) for b in batches) == len(reads)
    assert all(5 + 8 * len(b) <= MAX_IPC_RETURN_SIZE for b in batches)


@pytest.fixture
def fake():
    ram = bytearray(range(256)) * 4
    server = FakePCSX2(ram, ram_base=0x1000)
    yield server
    server.close()


def test_reads_and_strings(fake):
    with Pine(fake.port) as pine:
        assert pine.read([(0x1000, 1), (0x1002, 2), (0x1004, 4), (0x1008, 8)]) == [
            0x00,
            0x0302,
            0x07060504,
            0x0F0E0D0C0B0A0908,
        ]
        assert pine.read_block(0x1003, 6) == bytes(range(3, 9))
        assert pine.game_id() == "SCUS-97472"
        assert pine.version() == "PCSX2 Fake"
        assert pine.status() == "running"


def test_failed_request_raises(fake):
    with Pine(fake.port) as pine, pytest.raises(PineError):
        pine.call([bytes([0x55])])
