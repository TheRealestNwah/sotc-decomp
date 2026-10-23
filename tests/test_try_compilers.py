from pathlib import Path
from subprocess import CompletedProcess

import pytest

from tools import try_compilers
from tools.try_compilers import (
    Function,
    compile_c,
    diff,
    fix_moves,
    indexed_la_barriers,
    strip_padding,
    volatile_barriers,
    wsl_path,
)


@pytest.mark.parametrize(
    ("stderr", "stdout", "expected"),
    [
        (
            'in.c:632: parse error before "helper"\nin.c:1257: warning: pointer conversion\n',
            "",
            'in.c:632: parse error before "helper"',
        ),
        (
            "in.c:1: warning: error recovery\nin.c:2: error: invalid type\n",
            "",
            "in.c:2: error: invalid type",
        ),
        (
            "",
            "in.c:3: fatal error: missing header\nlater warning\n",
            "in.c:3: fatal error: missing header",
        ),
        (" \n", "compiler failed\n", "compiler failed"),
        ("", "", "no output"),
        ("unrecognized option\nlast diagnostic\n", "", "last diagnostic"),
        (
            "error.c: In function 'helper':\nerror.c:2: parse error before 'x'\n"
            "error.c:9: warning: pointer conversion\n",
            "",
            "error.c:2: parse error before 'x'",
        ),
    ],
)
def test_compile_c_reports_error_before_later_warnings(
    tmp_path, monkeypatch, stderr, stdout, expected
):
    monkeypatch.setattr(try_compilers, "find_cc1", lambda _: tmp_path / "cc1.exe")
    monkeypatch.setattr(
        try_compilers.subprocess,
        "run",
        lambda *args, **kwargs: CompletedProcess(args, 1, stdout, stderr),
    )
    assert compile_c(tmp_path, tmp_path / "in.c", ["-O2", "-G0"], tmp_path / "out.s") == expected


def test_compile_c_still_rejects_missing_output(tmp_path, monkeypatch):
    monkeypatch.setattr(try_compilers, "find_cc1", lambda _: tmp_path / "cc1.exe")
    monkeypatch.setattr(
        try_compilers.subprocess,
        "run",
        lambda *args, **kwargs: CompletedProcess(args, 0, "", ""),
    )
    assert compile_c(tmp_path, tmp_path / "in.c", [], tmp_path / "out.s") == "no output"


def test_wsl_path_converts_drive_letters():
    assert wsl_path(Path("D:/Modding/compilers/x")) == "/mnt/d/Modding/compilers/x"


def test_strip_padding():
    assert strip_padding([1, 2, 0, 0]) == [1, 2]


def test_diff_ignores_relocated_fields_only():
    jal = 0x0C000000
    target = Function([jal | 0x1234, 0x24840010], {0: 4})
    same_but_relocated = Function([jal | 0x9999, 0x24840010], {0: 4})
    assert diff(target, same_but_relocated) == 0
    different_opcode = Function([jal | 0x1234, 0x24850010], {0: 4})
    assert diff(target, different_opcode) == 1
    missing_reloc = Function([jal | 0x1234, 0x24840010], {})
    assert diff(target, missing_reloc) == 1


def test_diff_counts_length_difference():
    assert diff(Function([1, 2, 3], {}), Function([1, 2], {})) == 1


def test_fix_moves_uses_daddu(tmp_path):
    asm = tmp_path / "x.s"
    asm.write_text("\tmove\t$2,$3\n\tmove\t$4,$0\n", encoding="latin-1")
    fix_moves(asm)
    assert asm.read_text(encoding="latin-1") == "\tdaddu\t$2,$3,$0\n\tdaddu\t$4,$0,$0\n"


def test_volatile_barriers_replace_commented_markers(tmp_path):
    asm = tmp_path / "x.s"
    asm.write_text(
        "\t#.set\tvolatile\n\tlw\t$2,0($3)\n\t#.set\tnovolatile\n\tj\t$31\n", encoding="latin-1"
    )
    volatile_barriers(asm)
    barrier = "\t.set\tnoreorder\n\t.set\treorder\n"
    assert (
        asm.read_text(encoding="latin-1") == barrier + "\tlw\t$2,0($3)\n" + barrier + "\tj\t$31\n"
    )


def test_indexed_la_barriers_follow_indexed_la_only(tmp_path):
    asm = tmp_path / "x.s"
    asm.write_text(
        "\tla\t$4,D_1($4)\n\tjal\tf\n\tla\t$2,D_2\n\tlw\t$2,D_3($3)\n", encoding="latin-1"
    )
    indexed_la_barriers(asm)
    assert asm.read_text(encoding="latin-1") == (
        "\tla\t$4,D_1($4)\n\t.set\tnoreorder\n\t.set\treorder\n"
        "\tjal\tf\n\tla\t$2,D_2\n\tlw\t$2,D_3($3)\n"
    )
