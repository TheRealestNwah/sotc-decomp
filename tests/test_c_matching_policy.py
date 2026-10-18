"""Prevent artificial assembler barriers from entering counted C sources."""

import re
from pathlib import Path


def test_counted_c_has_no_empty_assembler_ordering_pairs():
    sources = sorted((Path(__file__).resolve().parents[1] / "src" / "xff").glob("*/*.c"))
    assert sources
    split_literals = re.compile(r'"\.set noreorder\\n"\s*"\.set reorder\\n"')
    single_literal = r".set noreorder\n.set reorder\n"
    offenders = []
    for source in sources:
        text = source.read_text(encoding="utf-8")
        if split_literals.search(text) or single_literal in text:
            offenders.append(source.name)
    assert not offenders, f"Empty assembler ordering pairs in counted C: {offenders}"
