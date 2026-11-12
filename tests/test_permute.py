from base64 import b64decode
from types import SimpleNamespace

import pytest

from tools import permute
from tools.functions import R_MIPS_26, R_MIPS_GPREL16, R_MIPS_HI16, R_MIPS_LO16
from tools.permute import (
    PLACEHOLDER,
    loader_function,
    normalize_objdump,
    only_target,
    protect_inline_asm,
    target_asm,
)

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


def test_only_target_accepts_comments_on_directive_lines():
    source = (
        "#ifdef NONMATCHING /* 5 diffs: ordering */\n"
        "int h(void) { return 2; }\n"
        "#else /* parked */\n"
        "extern int h(void);\n"
        "#endif /* NONMATCHING */\n"
    )
    out = only_target(source, "h")
    assert out == "int h(void) { return 2; }\n"


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


def test_protect_inline_asm_preserves_multiline_strings_and_constraints():
    asm = '__asm__ __volatile__("load (\nstore )\n" : "=r"(out) : "r"(in) : "memory");'
    out = protect_inline_asm(f"void f(void) {{ {asm} return; }}")
    encoded = out.split("#pragma _permuter b64literal ")[1].splitlines()[0]
    assert b64decode(encoded).decode("utf-8") == asm
    assert "return; }" in out and "__asm__" not in out


def test_protect_inline_asm_ignores_comments_and_quoted_mentions():
    unchanged = '/* asm("(") */ const char *s = "__asm__("; // asm(")")\n'
    assert protect_inline_asm(unchanged) == unchanged
    asm = 'asm /* ) */ volatile ("nop" /* ( */) /* ) */ ;'
    out = protect_inline_asm(unchanged + asm + '\n__asm("nop");')
    assert out.startswith(unchanged)
    assert out.count("#pragma _permuter b64literal") == 2
    encoded = out.split("#pragma _permuter b64literal ")[1].splitlines()[0]
    assert b64decode(encoded).decode("utf-8") == asm


def test_protect_inline_asm_rejects_incomplete_statements():
    with pytest.raises(ValueError, match="unterminated"):
        protect_inline_asm('__asm__("nop"')
    with pytest.raises(ValueError, match="semicolon"):
        protect_inline_asm('__asm__("nop")')


def test_typedef_printer_keeps_mode_and_alignment_attributes(monkeypatch):
    class Generator:
        def _generate_type(self, node):
            return node

        def _generate_attrs(self, attributes):
            return " __attribute__((" + ", ".join(attributes) + "))" if attributes else ""

    monkeypatch.setitem(
        permute.sys.modules,
        "perm_pycparser.c_generator",
        SimpleNamespace(CGenerator=Generator),
    )
    permute.install_typedef_printer()
    generator = Generator()
    for attributes in (["mode(TI)"], ["aligned(16)"], []):
        node = SimpleNamespace(storage=["typedef"], type="int s128", gcc_attributes=attributes)
        assert generator.visit_Typedef(node) == (
            "typedef int s128" + generator._generate_attrs(attributes)
        )


@pytest.mark.parametrize("inherited", [False, True])
def test_permuter_workers_install_typedef_printer(monkeypatch, inherited):
    import sys
    from types import ModuleType

    events = []

    def original(*args):
        events.append(args)

    module = ModuleType("src.main")
    module.multiprocess_worker = permute.permuter_worker if inherited else original
    package = ModuleType("src")
    package.main = module
    monkeypatch.setitem(sys.modules, "src", package)
    monkeypatch.setitem(sys.modules, "src.main", module)
    monkeypatch.setattr(permute, "_original_permuter_worker", original if inherited else None)
    monkeypatch.setattr(permute, "install_typedef_printer", lambda: events.append("install"))
    permute.permuter_worker("context", "tasks", "results")
    assert events == ["install", ("context", "tasks", "results")]


@pytest.mark.parametrize(
    "failure", [None, KeyboardInterrupt(), SystemExit(7), RuntimeError("search")]
)
@pytest.mark.parametrize("stubborn", [False, True])
def test_search_workers_reaps_only_new_children(monkeypatch, failure, stubborn):
    events = []

    class Child:
        def __init__(self, name):
            self.name = name
            self.alive = True

        def terminate(self):
            events.append((self.name, "terminate"))
            self.alive = stubborn

        def join(self, timeout):
            events.append((self.name, "join", timeout))

        def is_alive(self):
            return self.alive

        def kill(self):
            events.append((self.name, "kill"))
            self.alive = False

    existing, first, second = (Child(name) for name in ("existing", "first", "second"))
    snapshots = iter([[existing], [existing, first, second]])
    monkeypatch.setattr(permute.multiprocessing, "active_children", lambda: next(snapshots))

    def search():
        with permute.search_workers():
            if failure is not None:
                raise failure

    if failure is None:
        search()
    else:
        with pytest.raises(type(failure)) as raised:
            search()
        assert raised.value is failure

    assert events[:2] == [("first", "terminate"), ("second", "terminate")]
    assert existing.alive and not first.alive and not second.alive
    assert all(event[0] != "existing" for event in events)
    assert [event for event in events if event[1] == "join"] == [
        (name, "join", 2) for name in ("first", "second") for _ in range(2 if stubborn else 1)
    ]
    assert [event[0] for event in events if event[1] == "kill"] == (
        ["first", "second"] if stubborn else []
    )


def test_search_workers_leaves_completed_search_alone(monkeypatch):
    snapshots = iter([[], []])
    monkeypatch.setattr(permute.multiprocessing, "active_children", lambda: next(snapshots))
    with permute.search_workers():
        pass


LOADER_CSV = """address,size,name,class,library,evidence
0x00100000,0x10,f,game,loader,Original name
0x00100010,0x8,g,game,loader,Original name
"""
LOADER_ASM = """glabel f
    /* 0 00100000 1300023C */  lui        $v0, %hi(D_00130000)
    /* 4 00100004 0800E003 */  jr         $ra
    /* 8 00100008 0400428C */   lw        $v0, %lo(D_00130000)($v0)
    /* C 0010000C 00000000 */  nop
glabel g
    /* 10 00100010 0000000C */  jal        f
    /* 14 00100014 F0FF828F */   lw        $v0, %gp_rel(D_00139E04)($gp)
"""


def test_loader_function_reads_words_and_relocation_types():
    words, relocs = loader_function("f", LOADER_CSV, LOADER_ASM)
    assert words == [0x3C020013, 0x03E00008, 0x8C420004]  # padding dropped
    assert relocs == {0: R_MIPS_HI16, 2: R_MIPS_LO16}
    _, relocs = loader_function("g", LOADER_CSV, LOADER_ASM)
    assert relocs == {0: R_MIPS_26, 1: R_MIPS_GPREL16}


def test_loader_function_rejects_unknown_names():
    with pytest.raises(SystemExit):
        loader_function("h", LOADER_CSV, LOADER_ASM)


def test_protect_inline_asm_keeps_register_variable_declarations():
    decl = ' register int x __asm__("$2") = f(a, (b));'
    out = protect_inline_asm(f'void g(void) {{{decl} register int y asm("$3"); y = x; }}')
    encoded = [line.split()[-1] for line in out.splitlines() if "b64literal" in line]
    assert [b64decode(e).decode("utf-8") for e in encoded] == [decl, ' register int y asm("$3");']
    assert "asm" not in out.replace("#pragma _permuter b64literal", "")
    assert out.rstrip().endswith("y = x; }")
    # The hidden variables' types stay known to the randomizer.
    assert out.startswith("\nextern int x;\n\nextern int y;\nvoid g(void)") or out.startswith(
        "\nextern int y;\n\nextern int x;\nvoid g(void)"
    )


def test_protect_inline_asm_declares_register_variables_before_their_function():
    src = 'typedef int T;\nint h(void) { return 0; }\nvoid g(void) { register T *p __asm__("$4"); }'
    out = protect_inline_asm(src)
    assert out.index("extern T *p;") > out.index("return 0; }")
    assert out.index("extern T *p;") < out.index("void g")
    # Multiple declarators are left without a type declaration.
    assert "extern" not in protect_inline_asm('void g(void) { register int a, b __asm__("$4"); }')
