import pytest

from tools.progress import (
    block,
    compiled_functions,
    render_table,
    strip_nonmatching,
    update_readme,
)


def test_strip_nonmatching_drops_parked_branch_and_keeps_else():
    source = "\n".join(
        [
            "int kept(void) {",
            "#ifdef NONMATCHING",
            "int parked(void) {",
            "#else",
            "extern int parked();",
            "#endif",
            "}",
        ]
    )

    stripped = strip_nonmatching(source)

    assert "parked(void)" not in stripped
    assert "extern int parked();" in stripped
    assert "int kept(void)" in stripped


def test_compiled_functions_counts_only_asm_names_outside_parked_code(tmp_path):
    (tmp_path / "a.c").write_text(
        "\n".join(
            [
                "static inline int helper(int x) {",
                "    return x;",
                "}",
                "int real(int x) {",
                "    return helper(x);",
                "}",
                "#ifdef NONMATCHING",
                "int parked(void) {",
                "    return 0;",
                "}",
                "#endif",
                "extern int other(void);",
            ]
        ),
        encoding="latin-1",
    )
    asm_text = "glabel real\nglabel helper\nglabel parked\nglabel other\n"

    assert compiled_functions(tmp_path, asm_text) == {"real", "helper"}


def test_render_table_reports_module_and_total_percentages(monkeypatch):
    monkeypatch.setattr("tools.progress.MODULE_FUNCTIONS", {"A": 4, "B": 10})

    table = render_table({"A": 1, "B": 5})

    assert "| `A.XFF` as matching C | 1 | 4 functions | 25% |" in table
    assert "| All three `.XFF` modules as matching C | 6 | 14 functions | 43% |" in table


def test_update_readme_replaces_only_the_marked_block():
    readme = "before\n<!-- progress:start -->\nold\n<!-- progress:end -->\nafter\n"

    updated = update_readme(readme, "NEW TABLE")

    assert updated.startswith("before\n")
    assert updated.endswith("after\n")
    assert "NEW TABLE" in updated
    assert "old" not in updated
    assert block("NEW TABLE") in updated


def test_update_readme_requires_markers():
    with pytest.raises(ValueError):
        update_readme("no markers here", "table")


def test_compiled_functions_includes_address_labels_and_renamed_statics(tmp_path):
    (tmp_path / "callbacks.c").write_text(
        "static void recoveredLoop(void) { for (;;) {} }\n"
        "static int T_00001234(int x) { return x; }\n"
        "static inline int unusedHelper(int x) { return x; }\n"
        "int exported(void) { return 1; }\n"
        "#ifdef NONMATCHING\n"
        "static int parked(void) { return 0; }\n"
        "#endif\n",
        encoding="latin-1",
    )
    asm_text = "alabel func_00001000\nalabel T_00001234\nalabel exported\nglabel parked\n"

    assert compiled_functions(tmp_path, asm_text) == {"recoveredLoop", "T_00001234", "exported"}
