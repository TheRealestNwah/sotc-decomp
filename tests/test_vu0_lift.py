"""tools/vu0_lift.py turns runs of VU0 instructions into inline-asm drafts."""

from tools import vu0_lift

ASM = """
glabel demo # 1
    /* 000000 00000000 00000000 */  addiu       $sp, $sp, -0x20
    /* 000004 00000004 00000000 */  lqc2        $vf5, 0x0($s1)
    /* 000008 00000008 00000000 */  lqc2        $vf6, 0x0($v1)
    /* 00000C 0000000C 00000000 */  vsub.xyzw   $vf7, $vf5, $vf6
    /* 000010 00000010 00000000 */  vmul.xyz    $vf7, $vf7, $vf7
    /* 000014 00000014 00000000 */  vaddy.x     $vf7, $vf7, $vf7y
    /* 000018 00000018 00000000 */  qmfc2.ni    $v0, $vf7
    /* 00001C 0000001C 00000000 */  mtc1        $v0, $f1
    /* 000020 00000020 00000000 */  addu        $a0, $a0, $a1
    /* 000024 00000024 00000000 */  lqc2        $vf8, 0x10($sp)
    /* 000028 00000028 00000000 */  sqc2        $vf8, 0x0($a0)
endlabel demo
"""


def test_runs_are_split_at_scalar_instructions():
    instrs = vu0_lift.read_function(ASM, "demo")
    runs = vu0_lift.split_runs(instrs)
    assert [len(r) for r in runs] == [6, 2]


def test_float_result_run_binds_registers_and_mtc1():
    text = vu0_lift.lift_function(ASM, "demo")
    first = text.split("/* VU0 run")[1]
    assert '"lqc2 vf5, 0x0(%1)' in first
    assert '"lqc2 vf6, 0x0(%2)' in first
    assert "qmfc2.ni $2, vf7" in first
    assert "mtc1 $2, %0" in first
    assert '"=f"(f_f1)' in first
    assert '"r"(r_s1), "r"(r_v1)' in first
    assert '"$2", "memory"' in first


def test_stack_operand_becomes_a_buffer_input():
    text = vu0_lift.lift_function(ASM, "demo")
    second = text.split("/* VU0 run")[2]
    assert "&sp_buf" in second
    assert "r_a0" in second
    assert "lqc2 vf8, 0x10(%0)" in second


def test_function_without_vu0_says_so():
    asm = "glabel f # 1\n    /* 0 0 0 */  jr $ra\nendlabel f\n"
    asm = asm.replace("/* 0 0 0 */", "/* 000000 00000000 03E00008 */")
    assert "no VU0" in vu0_lift.lift_function(asm, "f")


def test_branch_labels_split_runs():
    asm = """
glabel f # 1
    /* 000000 00000000 00000000 */  lqc2        $vf5, 0x0($a0)
  .L00000004:
    /* 000004 00000004 00000000 */  sqc2        $vf5, 0x0($a1)
endlabel f
"""
    runs = vu0_lift.split_runs(vu0_lift.read_function(asm, "f"))
    assert [len(r) for r in runs] == [1, 1]
