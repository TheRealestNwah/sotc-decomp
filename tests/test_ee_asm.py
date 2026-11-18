"""The per-file option for code assembled with delay-slot filling (issue #3068)."""

from subprocess import CompletedProcess

import pytest

from tools import ee_asm, ee_cc

BARRIER = "\t.set\tnoreorder\n\t.set\treorder\n"
# A volatile load before a call, then a plain branch.
SOURCE = "\t#.set\tvolatile\n\tlw\t$2,0($3)\n\t#.set\tnovolatile\n\tjal\tf\n\tbne\t$2,$0,$L1\n"


def prepared(tmp_path, *args):
    asm = tmp_path / "x.s"
    asm.write_text(SOURCE, encoding="latin-1")
    ee_asm.prepare_asm(asm, *args)
    return asm.read_text(encoding="latin-1")


def test_jump_barriers_stay_on_by_default(tmp_path):
    assert prepared(tmp_path) == (
        BARRIER
        + "\tlw\t$2,0($3)\n"
        + BARRIER
        + BARRIER
        + "\tjal\tf\n"
        + BARRIER
        + "\tbne\t$2,$0,$L1\n"
    )


def test_fill_delay_slots_drops_only_the_jump_barriers(tmp_path):
    # The volatile access still stays out of the call's delay slot.
    assert prepared(tmp_path, 0, True) == (
        BARRIER + "\tlw\t$2,0($3)\n" + BARRIER + "\tjal\tf\n\tbne\t$2,$0,$L1\n"
    )


def test_command_line_option_matches_the_function(tmp_path):
    expected = prepared(tmp_path, 0, True)
    asm = tmp_path / "x.s"
    asm.write_text(SOURCE, encoding="latin-1")
    assert ee_asm.main([str(asm), "--gp", "0", ee_asm.FILL_DELAY_SLOTS]) == 0
    assert asm.read_text(encoding="latin-1") == expected


def test_split_asm_options_keeps_the_marker_away_from_the_compiler():
    flags = ["-O2", ee_asm.FILL_DELAY_SLOTS, "-G0"]
    assert ee_asm.split_asm_options(flags) == (["-O2", "-G0"], True)
    assert ee_asm.split_asm_options(["-O2", "-G0"]) == (["-O2", "-G0"], False)


@pytest.mark.parametrize("fill", [False, True])
def test_linux_pipeline_passes_the_option_to_preparation_only(tmp_path, monkeypatch, fill):
    output = tmp_path / "out.o"
    monkeypatch.setattr(ee_cc, "find_cc1", lambda _: tmp_path / "cc1")
    calls = []

    def run(command, **kwargs):
        calls.append(command)
        output.write_bytes(b"object")
        return CompletedProcess(command, 0, "", "")

    monkeypatch.setattr(ee_cc.subprocess, "run", run)
    flags = ["-O2", "-G0"] + ([ee_asm.FILL_DELAY_SLOTS] if fill else [])
    assert (
        ee_cc.compile_and_assemble(tmp_path, tmp_path / "x.c", flags, output, tmp_path / "as")
        is None
    )
    # ... ee_asm.py, libs, assembler options, -G value, then the cc1 flags.
    assert calls[0][-4:] == [ee_asm.FILL_DELAY_SLOTS if fill else "", "0", "-O2", "-G0"]


def test_windows_compiler_passes_the_option_to_assemble(tmp_path, monkeypatch):
    monkeypatch.setattr(ee_cc, "find_cc1", lambda _: tmp_path / "cc1.exe")
    compiled, assembled = [], []
    monkeypatch.setattr(ee_cc, "compile_c", lambda *args: compiled.append(args))
    monkeypatch.setattr(ee_cc, "assemble", lambda *args, **kwargs: assembled.append(kwargs))
    flags = ["-O2", "-G0", ee_asm.FILL_DELAY_SLOTS]
    assert (
        ee_cc.compile_and_assemble(tmp_path, tmp_path / "x.c", flags, tmp_path / "o", None) is None
    )
    assert compiled[0][2] == ["-O2", "-G0"]
    assert assembled == [{"fill_delay_slots": True}]


def test_permuter_copy_carries_the_option_through_ee_cc(tmp_path, monkeypatch):
    # permute.py setup forwards config/ee_cflags.json extras as --flag=...
    calls = []
    monkeypatch.setattr(ee_cc, "build", lambda *args: calls.append(args))
    argv = ["base.c", "base.o", f"--flag={ee_asm.FILL_DELAY_SLOTS}"]
    assert ee_cc.main(argv) == 0
    assert calls[0][3] == ["-O2", "-G0", ee_asm.FILL_DELAY_SLOTS]
