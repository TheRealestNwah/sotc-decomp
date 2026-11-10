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


def test_interleavings_keep_class_order():
    types = ["void *", "void *", "float", "int", "float"]
    orders = proto_perm.interleavings(types)
    assert len(orders) == 10  # C(5, 2)
    for order in orders:
        assert [i for i in order if i in (2, 4)] == [2, 4]
        assert [i for i in order if i in (0, 1, 3)] == [0, 1, 3]
    assert tuple(range(5)) in orders


def test_interleavings_work_past_five_parameters():
    types = ["char *"] * 6 + ["float"]
    assert len(proto_perm.interleavings(types)) == 7


def test_pointer_to_float_is_not_a_float_parameter():
    assert not proto_perm.is_float_type("float *")
    assert proto_perm.is_float_type("float")
    assert proto_perm.is_float_type("const double")
