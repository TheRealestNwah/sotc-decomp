from tools.check import compare, first_difference, main


def test_identical_images_match():
    ok, message = compare(b"abcd", b"abcd")
    assert ok
    assert message.startswith("OK")


def test_mismatch_reports_first_difference():
    ok, message = compare(b"abXdeY", b"abcdef")
    assert not ok
    assert "offset 0x2" in message
    assert "2 differing bytes" in message


def test_length_difference():
    assert first_difference(b"abc", b"abcd") == 3
    assert first_difference(b"abc", b"abc") is None


def test_main_exit_codes(tmp_path):
    a = tmp_path / "a.rom"
    b = tmp_path / "b.rom"
    a.write_bytes(b"same")
    b.write_bytes(b"same")
    assert main([str(a), str(b)]) == 0
    b.write_bytes(b"diff")
    assert main([str(a), str(b)]) == 1
