# sotc-decomp

Matching decompilation of Shadow of the Colossus (PS2, NTSC-U `SCUS-97472`), with a native PC port as the long-term goal.

## Goals

1. Rebuild the original binaries byte-for-byte from source in this repo.
2. Replace assembly with C, one function at a time, keeping the build matching at every step.
3. Once fully matching, build a PC port on top of the decompiled code.

Current phase:
- The loader ELF `SCUS_974.72` splits with splat and rebuilds byte-for-byte from assembly.
- The three game modules (`KERNEL.XFF`, `MANAGER.XFF`, `GAMECORE.XFF`, format in `docs/xff2.md`) split into assembly that reassembles to objects whose sections and relocations match the originals exactly.
- `ninja check` covers all of it.
- Not done yet: rebuilding the XFF files themselves byte-for-byte. That needs the original symbol table order (see `docs/xff2.md`). The game code itself lives in `KERNEL.XFF`, `MANAGER.XFF` and `GAMECORE.XFF` (custom `xff2` format), which isn't split yet. See `docs/findings.md`.

## Matching rules

- **Never edit generated assembly to force a match.** If something doesn't match, fix the split config, the build flags or the C, never the asm by hand.
- **C must compile to identical bytes.** A function counts as decompiled only when the compiled output matches the original exactly, with no hand-written asm patching around it.
- **No game files in git.** Everything from the disc (`iso/`), everything splat generates (`asm/`, `*.ld`, `undefined_*_auto.txt`) and all build output stay gitignored.
- **Don't guess the compiler.** It's GCC-based, probably 2.9x-era EE GCC (Sony `ee-gcc` vs SN ProDG is undecided). Ask the user before picking a compiler or version, and record the evidence in `docs/findings.md`.
- Sony SDK 3.0.x libraries (listed in `docs/findings.md`) get identified by signature, not decompiled by hand.

## Toolchain (native Windows)

- Python 3.11+ with a venv: `python -m venv .venv`, then `.venv\Scripts\pip install -r requirements.txt` (installs splat, pyelftools, ninja, pytest, ruff)
- PS2 EE binutils from PS2DEV (`mips64r5900el-ps2-elf-as` / `-ld`, tested with v2.0.0 / binutils 2.45.1) on `PATH`. On this machine it's at `D:\Modding\ps2dev\ps2dev\ee\bin`. To use another prefix, pass `--cross` or set `SOTC_CROSS`.
  - The Windows build is 32-bit and needs a **32-bit** `libzstd.dll`, which it doesn't ship. Put one (from the official zstd `win32` release) next to the `.exe`s in `ee\bin`. A 64-bit copy on `PATH` (e.g. Git's) makes it fail with exit code `0xC000007B`.
  - The linker must run with `-m elf32lr5900` (set in `configure.py`). Its default `n32` mode rejects our EABI objects with "ABI is incompatible".
- No `objcopy` needed: `tools/elf2rom.py` flattens ELFs in Python (`tools/objcopy.cmd` wraps it for `splat create_config --objcopy`).

## Build and check

The original ELF must be at `iso/SCUS_974.72` (copied from the user's own disc).

```
.venv\Scripts\python configure.py     # splits with splat if asm/ is missing, writes build.ninja
.venv\Scripts\ninja                   # assemble, link, flatten -> build/SCUS_974.72.rom
.venv\Scripts\ninja check             # compare build/SCUS_974.72.rom with the original
```

- `configure.py --split` forces a fresh split of the ELF and the XFF modules (do this after editing `SCUS_974.72.yaml`, `symbol_addrs.txt` or `tools/xff_split.py`).
- XFF modules: `ninja check` assembles `asm/xff/<MODULE>/<MODULE>.s` and compares sections + relocations against `iso/<MODULE>.XFF` converted to ELF. `python tools/xff_split.py iso/KERNEL.XFF --check` does the same for one module.
- `check` compares the flattened code and data images (every loaded byte). It doesn't compare ELF headers.
- `python tools/check_baserom.py` checks that `iso/SCUS_974.72` is the expected dump (SHA1 in `config/baserom.json`).

## Tests and lint

- `pytest` covers the Python tools in `tools/` and `configure.py`'s helpers
- `ruff check .` and `ruff format --check .` (fix with `ruff format .`)
- CI (`.github/workflows/ci.yml`) runs both on every PR. CI has no game files and no PS2 toolchain, so it can't run the matching build.

## Layout

- `SCUS_974.72.yaml`: splat config. Its `sha1` is the flattened image's hash, not the ELF's.
- `symbol_addrs.txt`: named symbols (hand-maintained). `linker_script_extra.ld`: entry point.
- `configure.py`: generates `build.ninja`
- `tools/`: helper scripts; `tests/` covers them with synthetic data (CI has no game files)
  - `elf2rom.py`, `check.py`, `check_baserom.py`: loader ELF
  - `xff2.py`: XFF reader/writer and XFF <-> ELF converter (`info`, `to-elf`, `from-elf`, `roundtrip`)
  - `xff_split.py`: disassembles an XFF with spimdisasm, then post-processes the asm so it reassembles exactly (rules in its docstring)
  - `xff_tus.py`: infers the original source-file boundaries from relocations (`--list` prints every group); results summarized in `docs/findings.md`
- `asm/xff/<MODULE>/`: generated XFF assembly (gitignored like all asm)
- `include/xff_macro.inc`: label macros for XFF asm. Labels are local by default; `.globl` comes from the original symbol table.
- `include/`: `macro.inc`, `labels.inc`, `include_asm.h` (splat helpers) and, later, headers
- `src/`: decompiled C (empty for now). Mirror the asm path: `asm/<segment>/x.s` becomes `src/<segment>/x.c`.
- `docs/findings.md`: what we know about the binaries, the compiler and the SDK
- `config/baserom.json`: expected original executable path and SHA1

## Gotchas

- The original sections aren't 16-byte aligned, so the splat config sets `ld_align_section_vram_end: False`. Re-enabling it shifts everything after `.text`.
- `.data_nop` (0x39D84) is typed `sdata` in the splat config so it links between `.lit4` and `.sdata`. As `data` it would be linked too early.
- `.text_nop` and `.reginfo` sit in the data blob at `0x31BAC`. That's fine for the image match, but not a real `.reginfo`.
- Windows PowerShell 5 here: `Set-Content -NoNewline` isn't available. Read and write generated asm as latin-1 (some strings are Shift-JIS; never round-trip it through ASCII).
- spimdisasm quirks the XFF post-processing works around:
  - it gets some section-relative addresses wrong in MANAGER (extra VU sections);
  - it drops addends on imported symbols;
  - it decodes some code as `.word`.
  The tool checks every relocated line against the original relocation and falls back to raw bytes plus an explicit `.reloc` when they disagree. Don't remove those checks.
- The originals reference a global defined in the same source file as section+offset, but a global from another file by name. That's a hint at original file boundaries, useful later when splitting into C files.
