import pytest

from tools.progress import (
    Progress,
    block,
    c_functions,
    count,
    label_addresses,
    loader_game_functions,
    module_functions,
    read_sdk_routines,
    render_sdk,
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


def test_c_functions_skips_parked_code_and_inline_statics(tmp_path):
    (tmp_path / "a.c").write_text(
        "\n".join(
            [
                "static inline int helper(int x) {",
                "    return x;",
                "}",
                "static int func_00000100(int x) {",
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

    defined, statics = c_functions(tmp_path)

    assert defined == {"helper", "func_00000100", "real"}
    assert statics == {"func_00000100"}


def test_label_addresses_reads_function_labels_and_their_first_instruction():
    asm = "\n".join(
        [
            "nonmatching func_00000138, 0x8",
            "",
            "glabel func_00000138 # 1",
            ".Lxff.func_00000138:",
            "    /* 000138 00000138 00000000 */  nop",
            "  alabel T_0000013C",
            "    /* 00013C 0000013C 0800E003 */  jr          $ra",
            "  .L00000140:",
            "    /* 000140 00000140 00000000 */  nop",
        ]
    )

    assert label_addresses(asm) == {"func_00000138": 0x138, "T_0000013C": 0x13C}


def test_module_functions_counts_named_and_referenced_placeholders():
    named = {"main": 0x0}
    labels = {
        "main": 0x38,
        "func_00000078": 0x78,  # referenced static
        "T_000000B8": 0xB8,  # function pointer target
        "func_000000F8": 0xF8,  # tail-call split nobody references
    }
    targets = {0x40, 0x80, 0x200}  # asm address minus the 0x38 base

    assert module_functions(named, labels, targets) == {"main", "func_00000078", "T_000000B8"}


def test_module_functions_rejects_inconsistent_named_labels():
    with pytest.raises(ValueError):
        module_functions({"a": 0x0, "b": 0x10}, {"a": 0x38, "b": 0x50}, set())


def test_count_matches_the_same_set_and_leaves_out_sdk_routines():
    functions = {"real", "func_00000100", "unmatched", "sceCdRead", "mktime"}
    defined = {"real", "func_00000100", "mktime", "helper_not_in_module"}
    statics = {"func_00000100", "renamed_static"}

    progress = count(functions, defined, statics, sdk={"sceCdRead", "mktime"})

    # renamed_static counts as a function and as matched; mktime is matched but SDK.
    assert progress == Progress(matched=3, total=4, sdk=2)


def test_read_sdk_routines_groups_names_by_module(tmp_path):
    path = tmp_path / "sdk.txt"
    path.write_text(
        "# comment\nKERNEL sceCdRead libcdvd 0x1e0 0123456789abcdef\n\n"
        "MANAGER rand libc 0x20 fedcba9876543210  # trailing\n",
        encoding="utf-8",
    )

    assert read_sdk_routines(path) == {"KERNEL": {"sceCdRead"}, "MANAGER": {"rand"}}
    assert read_sdk_routines(tmp_path / "missing.txt") == {}


def test_render_table_reports_module_and_total_percentages():
    table = render_table({"A": Progress(1, 4, 0), "B": Progress(5, 10, 2)}, loader_total=8)

    assert "| `A.XFF` Game code as matching C | 1 | 4 functions | 25% |" in table
    assert "| All three Game modules' Game code as matching C | 6 | 14 functions | 43% |" in table
    assert "| Loader `SCUS_974.72` Game code as matching C | 0 | 8 functions | 0% |" in table


def test_loader_game_functions_counts_game_rows(tmp_path):
    path = tmp_path / "loader.csv"
    path.write_text(
        "address,size,name,class,library,evidence\n"
        "0x00100000,0x10,func_00100000,game,loader,x\n"
        "0x00100010,0xB0,_start,sdk,crt0,y\n"
        "0x001000D0,0x1A4,ResolveRelocation,game,loader,z\n",
        encoding="utf-8",
    )

    assert loader_game_functions(path) == 2


def test_render_sdk_lists_each_module():
    line = render_sdk({"A": Progress(1, 4, 0), "B": Progress(5, 10, 2)})

    assert line.endswith("A 0, B 2.")


def test_update_readme_replaces_only_the_marked_block():
    readme = "before\n<!-- progress:start -->\nSTALE\n<!-- progress:end -->\nafter\n"

    updated = update_readme(readme, "NEW TABLE")

    assert updated.startswith("before\n")
    assert updated.endswith("after\n")
    assert "NEW TABLE" in updated
    assert "STALE" not in updated
    assert block("NEW TABLE") in updated


def test_update_readme_requires_markers():
    with pytest.raises(ValueError):
        update_readme("no markers here", "table")


def test_c_functions_finds_renamed_statics_outside_parked_code(tmp_path):
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

    _, statics = c_functions(tmp_path)

    assert statics == {"recoveredLoop", "T_00001234"}


def test_main_keeps_table_and_bars_in_sync_as_matching_source_changes(tmp_path, monkeypatch):
    from tools import progress

    source_dir = tmp_path / "src" / "xff" / "TEST"
    source_dir.mkdir(parents=True)
    source = source_dir / "functions.c"
    source.write_text("int first(void) { return 0; }\n", encoding="utf-8")
    asm_dir = tmp_path / "asm" / "TEST"
    asm_dir.mkdir(parents=True)
    (asm_dir / "text.s").write_text(
        "glabel first\n    /* 000038 00000038 00000000 */  nop\n"
        "glabel func_0000003C\n    /* 00003C 0000003C 00000000 */  nop\n"
        "glabel sdkRoutine\n    /* 000040 00000040 00000000 */  nop\n",
        encoding="utf-8",
    )
    iso_dir = tmp_path / "iso"
    iso_dir.mkdir()
    (iso_dir / "TEST.XFF").write_bytes(b"")
    sdk = tmp_path / "sdk.txt"
    sdk.write_text("TEST sdkRoutine libc 0x4 0123456789abcdef\n", encoding="utf-8")
    readme = tmp_path / "README.md"
    readme.write_text(
        "before\n<!-- progress:start -->\nstale 68%\n<!-- progress:end -->\nafter\n",
        encoding="utf-8",
    )
    monkeypatch.setattr(progress, "REPO", tmp_path)
    monkeypatch.setattr(progress, "README", readme)
    monkeypatch.setattr(progress, "SDK_ROUTINES", sdk)
    loader_csv = tmp_path / "loader.csv"
    loader_csv.write_text("address,size,name,class,library,evidence\n", encoding="utf-8")
    monkeypatch.setattr(progress, "LOADER_FUNCTIONS_CSV", loader_csv)
    monkeypatch.setattr(progress, "MODULES", ("TEST",))
    monkeypatch.setattr(
        progress, "read_module", lambda _: ({"first": 0x0, "sdkRoutine": 0x8}, {0x4})
    )
    args = ["--asm-dir", str(asm_dir.parent), "--iso-dir", str(iso_dir)]

    assert progress.main(args) == 0
    half = readme.read_text(encoding="utf-8")
    assert "| All three Game modules' Game code as matching C | 1 | 2 functions | 50% |" in half
    assert "left out of the totals: TEST 1." in half
    assert "[██████████░░░░░░░░░░] 50%" in half
    assert "68%" not in half
    assert half.startswith("before\n") and half.endswith("after\n")

    source.write_text(
        "int first(void) { return 0; }\nstatic int func_0000003C(void) { return 1; }\n",
        encoding="utf-8",
    )
    assert progress.main(args) == 0
    complete = readme.read_text(encoding="utf-8")
    assert (
        "| All three Game modules' Game code as matching C | 2 | 2 functions | 100% |" in complete
    )
    assert "[████████████████████] 100%" in complete
    assert "[██████████░░░░░░░░░░] 50%" not in complete
    assert progress.main(args) == 0
    assert readme.read_text(encoding="utf-8") == complete
