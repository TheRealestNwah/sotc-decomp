import os
import shutil
import subprocess
from pathlib import Path
from subprocess import CompletedProcess

import pytest

from tools import ee_cc


def test_linux_pipeline_uses_one_wsl_call_and_preserves_arguments(tmp_path, monkeypatch):
    source = tmp_path / "input $value; name.c"
    source.write_text("int f(void) { return 1; }")
    output = tmp_path / "result & name.o"
    cc1 = tmp_path / "cc1"
    assembler = tmp_path / "ee-as"
    monkeypatch.setattr(ee_cc, "find_cc1", lambda _: cc1)
    calls = []

    def run(command, **kwargs):
        calls.append(command)
        output.write_bytes(b"object")
        return CompletedProcess(command, 0, "", "")

    monkeypatch.setattr(ee_cc.subprocess, "run", run)
    assert ee_cc.compile_and_assemble(tmp_path, source, ["-O2", "-G8"], output, assembler) is None
    assert len(calls) == 1
    assert calls[0][:4] == ["wsl", "-e", "bash", "-c"]
    assert calls[0][6:10] == [ee_cc.wsl_path(p) for p in (cc1, assembler, source, output)]
    assert calls[0][-3:] == ["8", "-O2", "-G8"]


def test_linux_pipeline_removes_stale_or_partial_output_on_failure(tmp_path, monkeypatch):
    output = tmp_path / "out.o"
    output.write_bytes(b"stale")
    monkeypatch.setattr(ee_cc, "find_cc1", lambda _: tmp_path / "cc1")

    def run(command, **kwargs):
        assert not output.exists()
        output.write_bytes(b"partial")
        return CompletedProcess(command, 9, "", "assembly error: failed\nwarning: later\n")

    monkeypatch.setattr(ee_cc.subprocess, "run", run)
    assert ee_cc.compile_and_assemble(
        tmp_path, tmp_path / "x.c", [], output, tmp_path / "ee-as"
    ) == ("assembly error: failed")
    assert not output.exists()


def test_windows_compiler_keeps_native_compile_fallback(tmp_path, monkeypatch):
    output = tmp_path / "out.o"
    monkeypatch.setattr(ee_cc, "find_cc1", lambda _: tmp_path / "cc1.exe")
    calls = []
    monkeypatch.setattr(ee_cc, "compile_c", lambda *args: calls.append(("compile", args)))
    monkeypatch.setattr(ee_cc, "assemble", lambda *args: calls.append(("assemble", args)))
    assert (
        ee_cc.compile_and_assemble(tmp_path, tmp_path / "x.c", ["-G8"], output, tmp_path / "ee-as")
        is None
    )
    assert [step for step, _ in calls] == ["compile", "assemble"]
    assert calls[1][1][-1] == 8


@pytest.fixture
def native_pipeline(tmp_path, monkeypatch):
    if os.name != "posix" or shutil.which("bash") is None:
        pytest.skip("executes the Linux shell pipeline with synthetic toolchain programs")
    root = tmp_path / "paths with spaces $literal"
    root.mkdir()
    libs = root / "libs"
    libs.mkdir()
    log = root / "stages.log"
    work_path = root / "work-path.txt"
    monkeypatch.setenv("SOTC_TEST_PIPELINE_LOG", str(log))
    monkeypatch.setenv("SOTC_TEST_WORK_PATH", str(work_path))

    def program(path, text):
        path.write_text("#!/bin/sh\nset -eu\n" + text)
        path.chmod(0o755)
        return path

    program(libs / "ld-linux.so.2", 'shift 2\nexec "$@"\n')
    cc1 = program(
        root / "cc1",
        """
printf 'compile\n' >> "$SOTC_TEST_PIPELINE_LOG"
while [ "$1" != '-o' ]; do input=$1; shift; done
shift
printf '%s' "$(dirname "$input")" > "$SOTC_TEST_WORK_PATH"
if [ "${SOTC_TEST_FAIL:-}" = compile ]; then
    echo 'compiler error: synthetic failure' >&2
    exit 7
fi
if [ "${SOTC_TEST_FAIL:-}" = empty ]; then : > "$1"; else cp "$input" "$1"; fi
""",
    )
    assembler = program(
        root / "ee-as",
        """
printf 'assemble\n' >> "$SOTC_TEST_PIPELINE_LOG"
[ "$1" = '-EL' ]; shift
[ "$1" = '-G' ]; shift 2
[ "$1" = '-o' ]; shift
output=$1
input=$2
cp "$input" "$output"
if [ "${SOTC_TEST_FAIL:-}" = assemble ]; then
    echo 'assembler error: synthetic failure' >&2
    exit 9
fi
""",
    )
    source = root / "input ; literal.c"
    source.write_text("\t#.set\tvolatile\n\tlhu\t$2,table($3)\n\tjr\t$31\n")
    output = root / "output & literal.o"
    monkeypatch.setattr(ee_cc, "find_cc1", lambda _: cc1)
    monkeypatch.setattr(ee_cc, "wsl_path", lambda path: str(path))
    monkeypatch.setattr(ee_cc, "I386_LIBS", str(libs))
    actual_run = subprocess.run
    calls = []

    def run(command, **kwargs):
        calls.append(command)
        return actual_run(command[2:], **kwargs)

    monkeypatch.setattr(ee_cc.subprocess, "run", run)
    return root, source, output, assembler, log, work_path, calls


@pytest.mark.parametrize("gp", [0, 8])
def test_native_pipeline_prepares_assembly_and_cleans_temporary_files(native_pipeline, gp):
    root, source, output, assembler, log, work_path, calls = native_pipeline
    assert ee_cc.compile_and_assemble(root, source, ["-O2", f"-G{gp}"], output, assembler) is None
    barrier = "\t.set\tnoreorder\n\t.set\treorder\n"
    load = (
        "\tlui\t$2,%hi(table)\n\taddu\t$2,$2,$3\n\tlhu\t$2,%lo(table)($2)\n"
        if gp == 0
        else "\tlhu\t$2,table($3)\n"
    )
    assert output.read_text() == barrier + load + barrier + "\tjr\t$31\n"
    assert log.read_text().splitlines() == ["compile", "assemble"]
    assert len(calls) == 1
    assert not Path(work_path.read_text()).exists()


@pytest.mark.parametrize("failure", ["compile", "empty", "preprocess", "assemble"])
def test_native_pipeline_stops_at_failed_stage(native_pipeline, monkeypatch, failure):
    root, source, output, assembler, log, work_path, _ = native_pipeline
    output.write_bytes(b"stale")
    monkeypatch.setenv("SOTC_TEST_FAIL", failure)
    if failure == "preprocess":
        monkeypatch.setattr(ee_cc, "ROOT", root / "missing-preprocessor")
    assert ee_cc.compile_and_assemble(root, source, ["-O2", "-G0"], output, assembler) is not None
    assert not output.exists()
    assert log.read_text().splitlines() == (
        ["compile", "assemble"] if failure == "assemble" else ["compile"]
    )
    assert not Path(work_path.read_text()).exists()
