from synthetic_xff import build

from tools.xff_tus import infer, source_names


def test_source_names_key_by_containing_string():
    rodata = b"\0\0\0\0src/foo.c: bad\0other\0C:\\x\\bar.cpp\0"
    assert source_names(rodata) == {4: "foo.c", 25: "bar.cpp"}


def test_infer_groups_and_evidence():
    result = infer(build())
    groups = [(g.first, g.last) for g in result.groups]
    assert groups == [(0, 1), (2, 2), (3, 3)]
    assert result.same_file_links == 1
    assert result.cross_file_links == 1
    assert result.conflicts == []
    # f3's %lo pairs with f2's %hi: the string at .rodata+4 names f3's group.
    assert result.groups[2].names == {"foo.c"}
