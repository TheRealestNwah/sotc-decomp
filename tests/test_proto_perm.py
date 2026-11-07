"""tools/proto_perm.py rewrites a prototype and its single call together."""

from tools import proto_perm

SRC = """extern void f(int, void *, float, float);

void g(int obj, void *p, float a, float b)
{
    f(obj, p, a, b);
}
"""


def test_split_args_respects_nesting():
    assert proto_perm.split_args("int, float *(*cb)(int, int), x[2]") == [
        "int",
        "float *(*cb)(int, int)",
        "x[2]",
    ]


def test_permutation_changes_prototype_and_call_together():
    out = proto_perm.permuted(SRC, "f", (0, 2, 3, 1))
    assert "extern void f(int, float, float, void *);" in out
    assert "    f(obj, a, b, p);" in out


def test_identity_is_unchanged():
    assert proto_perm.permuted(SRC, "f", (0, 1, 2, 3)) == SRC
