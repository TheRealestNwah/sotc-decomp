# Shadow of the Colossus Decompilation

A work-in-progress decompilation of **Shadow of the Colossus** (PlayStation 2, NTSC-U, `SCUS-97472`), with the long-term goal of a native PC port.

The aim is C source that compiles back to a byte-identical copy of the original executable. Once that matches, the code can be ported to run natively on PC.

## Status

- The loader ELF `SCUS_974.72` splits with [splat](https://github.com/ethteck/splat) (1,038 functions) and **rebuilds byte-for-byte** from assembly (`ninja check` passes).
- The game code itself lives in the `.XFF` modules (custom `xff2` format). These aren't split yet.
- Nothing is decompiled to C yet.

See [docs/findings.md](docs/findings.md) for what's known about the binaries, the compiler and the linked Sony SDK libraries.

## You need your own copy of the game

This repo contains **no game code, data or assets**. Dump your own disc and copy `SCUS_974.72` into `iso/`. Never commit anything from the disc.

## Setup (Windows)

1. Install Python 3.11+.
2. Install the PS2DEV EE toolchain (`ps2dev-windows-latest.tar.gz` from the [ps2dev/ps2dev releases](https://github.com/ps2dev/ps2dev/releases)) and put its `ee\bin` folder on `PATH`. It also needs a 32-bit `libzstd.dll` (from the [zstd releases](https://github.com/facebook/zstd/releases), `win32` zip) copied into `ee\bin`.
3. Then:

```bash
python -m venv .venv
.venv\Scripts\pip install -r requirements.txt
.venv\Scripts\python tools/check_baserom.py
.venv\Scripts\python configure.py
.venv\Scripts\ninja check
```

## Roadmap

1. ~~Verify the base executable hash~~
2. ~~Split the loader ELF with splat and rebuild it byte-for-byte~~
3. Reverse the `xff2` module format and split `KERNEL`/`MANAGER`/`GAMECORE.XFF`
4. Pin down the original compiler version and get C matching
5. Decompile functions one at a time, using [decomp.me](https://decomp.me) to match them
6. Once fully matching, build a PC port layer (graphics, audio, input)

## Layout

| Path | Purpose |
| --- | --- |
| `SCUS_974.72.yaml` | splat config for the loader ELF |
| `configure.py` | Generates `build.ninja` |
| `config/` | Expected original executable path and hash |
| `docs/` | Findings about the binaries and toolchain |
| `src/` | Decompiled C source (empty for now) |
| `include/` | Assembler macros and headers |
| `tools/` | Helper scripts (ELF flattener, match checker) |
| `tests/` | Tests for the helper scripts |
