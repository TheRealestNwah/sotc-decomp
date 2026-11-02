import hashlib

import pytest

from tools.sdk_routines import Routine, function_extents, parse_list, signature


def test_signature_ignores_relocated_fields():
    jal_a = (0x0C000010).to_bytes(4, "little")
    jal_b = (0x0C000F4C).to_bytes(4, "little")
    lui_a = (0x3C020001).to_bytes(4, "little")
    lui_b = (0x3C020123).to_bytes(4, "little")
    word_a = (0x00001234).to_bytes(4, "little")
    word_b = (0x00ABCDEF).to_bytes(4, "little")
    relocs = {0: 4, 4: 5, 8: 2}

    assert signature(jal_a + lui_a + word_a, relocs) == signature(jal_b + lui_b + word_b, relocs)
    masked = (0x0C000000).to_bytes(4, "little") + (0x3C020000).to_bytes(4, "little") + bytes(4)
    assert signature(jal_a + lui_a + word_a, relocs) == hashlib.sha1(masked).hexdigest()[:16]


def test_signature_keeps_unrelocated_words():
    assert signature((0x0C000010).to_bytes(4, "little"), {}) != signature(
        (0x0C000F4C).to_bytes(4, "little"), {}
    )


def test_function_extents_uses_symbol_size_or_next_function():
    starts = {"static_helper": 0x0, "named": 0x40, "last": 0x80}
    sizes = {"named": 0x30}

    assert function_extents(starts, sizes, 0xA0) == {
        "static_helper": (0x0, 0x40),
        "named": (0x40, 0x30),
        "last": (0x80, 0x20),
    }


def test_parse_list_round_trips_lines():
    routine = Routine("KERNEL", "sceCdRead", "libcdvd", 0x1E0, "0123456789abcdef")

    assert parse_list(f"# header\n\n{routine.line()}  # note\n") == [routine]


def test_parse_list_rejects_short_lines():
    with pytest.raises(ValueError):
        parse_list("KERNEL sceCdRead libcdvd\n")
