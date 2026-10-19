from base64 import b64decode
from types import SimpleNamespace

import pytest

from tools import permute
from tools.permute import (
    PLACEHOLDER,
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
