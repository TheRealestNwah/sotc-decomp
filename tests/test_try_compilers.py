from pathlib import Path

from tools.try_compilers import Function, diff, fix_moves, strip_padding, wsl_path


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
