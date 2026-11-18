from tools.handwritten_asm import Entry, loader_function, parse_list
from tools.sdk_routines import signature


def test_parse_list_keeps_the_evidence_text():
    text = "# comment\n\nMANAGER func_0001E9C0 0x1b0 6bbaa869df029314 di/ei, no prologue # note\n"

    assert parse_list(text) == [
        Entry("MANAGER", "func_0001E9C0", 0x1B0, "6bbaa869df029314", "di/ei, no prologue")
    ]


def test_entry_line_round_trips():
    entry = Entry("LOADER", "setCop0Epc", 0xC, "4cd66a4120bb8ab4", "lone mtc0")

    assert parse_list(entry.line()) == [entry]


def test_loader_function_reads_code_from_the_loaded_segment(tmp_path, monkeypatch):
    import tools.handwritten_asm as hw

    code = bytes(range(12))
    csv_path = tmp_path / "loader.csv"
    csv_path.write_text(
        "address,size,name,class,library,evidence\n0x00100004,0xC,f,game,loader,x\n",
        encoding="utf-8",
    )

    def fake(elf_path, address, size):
        assert (address, size) == (0x100004, 0xC)
        return code

    monkeypatch.setattr(hw, "elf_bytes", fake)
    assert loader_function(csv_path, tmp_path / "x.elf", "f") == (0xC, signature(code, {}))
