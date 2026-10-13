from tools.permute import PLACEHOLDER, normalize_objdump, only_target, target_asm

SOURCE = """int a(void) { return 1; }

#ifdef NONMATCHING
/* close */
static int f(int x)
{
    return x;
}
#endif

#ifdef NONMATCHING
static void g(void)
{
    __asm__("nop");
}
#else
extern void g(void);
#endif
"""


def test_only_target_switches_on_the_target_and_drops_other_attempts():
    out = only_target(SOURCE, "f")
    assert "static int f(int x)" in out
    assert "__asm__" not in out
    assert "extern void g(void);" in out
    assert "NONMATCHING" not in out


def test_only_target_keeps_other_code():
    assert only_target(SOURCE, "g").startswith("int a(void) { return 1; }")


def test_target_asm_zeroes_relocated_fields():
    asm = target_asm("f", [0x3C020123, 0x03E00008], {0: 5})
    assert f".reloc ., R_MIPS_HI16, {PLACEHOLDER}\n.word 0x3C020000" in asm
    assert ".word 0x03E00008" in asm


def test_normalize_objdump_hides_symbol_names_and_addends():
    text = (
        " 780:\t3c110000 \tlui\ts1,0x0\n"
        "\t\t\t780: R_MIPS_HI16\tgcGlobalVar\n"
        " 790:\t262402b0 \taddiu\ta0,s1,688\n"
        "\t\t\t790: R_MIPS_LO16\t.data\n"
        " 794:\t10400025 \tbeqz\tv0,82c <f+0xb4>\n"
    )
    out = normalize_objdump(text).splitlines()
    assert out[1].endswith(PLACEHOLDER) and out[3].endswith(PLACEHOLDER)
    assert out[2].endswith("addiu\ta0,s1,0")
    assert out[4] == " 794:\t10400025 \tbeqz\tv0,82c <f+0xb4>"
