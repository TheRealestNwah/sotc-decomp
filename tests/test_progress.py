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


def test_main_keeps_table_and_bars_in_sync_as_matching_source_changes(tmp_path, monkeypatch):
    from tools import progress

    source_dir = tmp_path / "src" / "xff" / "TEST"
    source_dir.mkdir(parents=True)
    source = source_dir / "functions.c"
    source.write_text("int first(void) { return 0; }\n", encoding="utf-8")
    asm_dir = tmp_path / "asm" / "TEST"
    asm_dir.mkdir(parents=True)
    (asm_dir / "text.s").write_text("glabel first\nglabel second\n", encoding="utf-8")
    readme = tmp_path / "README.md"
    readme.write_text(
        "before\n<!-- progress:start -->\nstale 68%\n<!-- progress:end -->\nafter\n",
        encoding="utf-8",
    )
    monkeypatch.setattr(progress, "REPO", tmp_path)
    monkeypatch.setattr(progress, "README", readme)
    monkeypatch.setattr(progress, "MODULE_FUNCTIONS", {"TEST": 2})

    assert progress.main(["--asm-dir", str(asm_dir.parent)]) == 0
    half = readme.read_text(encoding="utf-8")
    assert "| All three `.XFF` modules as matching C | 1 | 2 functions | 50% |" in half
    assert "[██████████░░░░░░░░░░] 50%" in half
    assert "68%" not in half
    assert half.startswith("before\n") and half.endswith("after\n")

    source.write_text(
        "int first(void) { return 0; }\nint second(void) { return 1; }\n", encoding="utf-8"
    )
    assert progress.main(["--asm-dir", str(asm_dir.parent)]) == 0
    complete = readme.read_text(encoding="utf-8")
    assert "| All three `.XFF` modules as matching C | 2 | 2 functions | 100% |" in complete
    assert "[████████████████████] 100%" in complete
    assert "[██████████░░░░░░░░░░] 50%" not in complete
    assert progress.main(["--asm-dir", str(asm_dir.parent)]) == 0
    assert readme.read_text(encoding="utf-8") == complete
