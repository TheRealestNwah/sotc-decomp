# sotc-decomp

Private, machine-specific notes (agent workflow, handoffs) live in `CLAUDE.local.md`, which is gitignored. If it exists, read it before starting work.

Matching decompilation of Shadow of the Colossus (PS2, NTSC-U `SCUS-97472`), with a Native port to PC as the long-term goal.

## Autonomous work

Unless the owner specifies a task or another stopping condition, a request to work autonomously means to continue through the backlog until usage is exhausted. Follow any requested issue order, record phase or evidence blockers before advancing, and continue to the next actionable item after each investigation or merge. An arbitrary batch boundary is not a stopping condition.

At usage exhaustion, save a resumable handoff. Resume automatically when the five-hour usage window resets, provided no successor agent is active; do not track or self-limit against weekly usage totals.

## Goals

1. Rebuild the Original byte-for-byte from source in this repo.
2. Replace assembly with C, one Matched function at a time, keeping the build matching at every step.
3. Once all Game code is Matched functions, build the Native port on top of the matched source.

Current phase:
- The Loader `SCUS_974.72` splits with splat and rebuilds byte-for-byte from assembly.
- The three Game modules (`KERNEL.XFF`, `MANAGER.XFF`, `GAMECORE.XFF`, xff2 format in `docs/xff2.md`) split into assembly that reassembles to objects whose sections and relocations match the Original exactly.
- `ninja check` covers all of it.
- The complete Game modules rebuild byte-for-byte through `tools/xff_rebuild.py`, using original table-layout and loader metadata. `ninja check` verifies the complete files as well as sections and relocations; see `docs/xff2.md` for the metadata dependency.
- The compiler is identified (see Matching rules), and the C build works: `src/xff/<MODULE>/*.c` is compiled and spliced into the Game module (see "Matching a function").

## Matching rules

- **Never edit generated assembly to force a match.** If something doesn't match, fix the split config, the build flags or the C, never the asm by hand.
- **C must compile to identical bytes.** A function counts as a Matched function only when the compiled output matches the Original exactly, with no hand-written asm patching around it.
- **No game files in git.** Everything from the disc (`iso/`), everything splat generates (`asm/`, `*.ld`, `undefined_*_auto.txt`) and all build output stay gitignored.
- **Compiler: Sony `ee-gcc` 2.96 (`2.96-ee-001003-1`), `-O2 -G0`, assembled with that package's own `ee-as`.** Chosen by evidence (with the user's OK), recorded in `docs/findings.md`. Don't switch compilers or flags without new evidence. Modern binutils expands `move` and jump-table loads differently from the original assembler, so C must go through the package's `ee-as`.
- SDK routines (from the Sony SDK 3.0.x libraries listed in `docs/findings.md`) get identified by signature, not decompiled by hand. Record each one in `config/sdk_routines.txt` (names and signatures only, never SDK library files or code); `tools/progress.py` leaves them out of the Game code totals.

## Toolchain (native Windows)

- Python 3.11+ with a venv: `python -m venv .venv`, then `.venv\Scripts\pip install -r requirements.txt` (installs splat, pyelftools, ninja, pytest, ruff)
- PS2 EE binutils from PS2DEV (`mips64r5900el-ps2-elf-as` / `-ld`, tested with v2.0.0 / binutils 2.45.1) on `PATH`. On this machine it's at `D:\Modding\ps2dev\ps2dev\ee\bin`. To use another prefix, pass `--cross` or set `SOTC_CROSS`.
  - The Windows build is 32-bit and needs a **32-bit** `libzstd.dll`, which it doesn't ship. Put one (from the official zstd `win32` release) next to the `.exe`s in `ee\bin`. A 64-bit copy on `PATH` (e.g. Git's) makes it fail with exit code `0xC000007B`.
  - The linker must run with `-m elf32lr5900` (set in `configure.py`). Its default `n32` mode rejects our EABI objects with "ABI is incompatible".
- No `objcopy` needed: `tools/elf2rom.py` flattens ELFs in Python (`tools/objcopy.cmd` wraps it for `splat create_config --objcopy`).
- **Original compilers** (from decomp.me's archive, `gh release download compilers --repo decompme/compilers`) are extracted under `D:\Modding\compilers\<name>` (override with `SOTC_COMPILERS`).
  - The 2.96 (and 2.9/3.2) builds are 32-bit Linux programs: they run under WSL (Ubuntu) with a private 32-bit libc unpacked from Ubuntu's `libc6:i386` package into `~/i386libs/root` (no `sudo`; override with `SOTC_I386_LIBS`).
  - Old 32-bit programs can't read files on `/mnt/<drive>` ("Value too large for defined data type"), so always copy inputs into WSL's `/tmp` first. `tools/try_compilers.py` does this.
  - The 2.95.x builds are Windows `cc1.exe` and run natively.
- `tools/try_compilers.py <file.c> --module GAMECORE`: compiles every function in a C file with each candidate compiler and flag set, and reports instruction differences against the original functions of the same name. Useful for any matching work, not just compiler ID.
- **Decomp tools** (open source, cloned outside the repo into `D:\Modding\decomp-tools`):
  - m2c (`SOTC_M2C`) needs the `graphviz` Python package.
  - decomp-permuter (`SOTC_PERMUTER`) needs `toml`.
  - Both packages are installed in `.venv`; neither is in `requirements.txt`, since CI doesn't use them.
  - The permuter runs from Windows Python with Git's bash (`SOTC_BASH`), ee-gcc 2.96's `cpp0` under WSL, and the PS2DEV objdump. `tools/permute.py` sets that up.

## Build and check

The Original Loader must be at `iso/SCUS_974.72` (copied from the owner's own disc).

```
.venv\Scripts\python configure.py     # splits with splat if asm/ is missing, writes build.ninja
.venv\Scripts\ninja                   # assemble, link, flatten -> build/SCUS_974.72.rom
.venv\Scripts\ninja check             # compare build/SCUS_974.72.rom with the Original
```

- `configure.py --split` forces a fresh split of the Loader and the Game modules (do this after editing `SCUS_974.72.yaml`, `symbol_addrs.txt` or `tools/xff_split.py`).
- Game modules: `ninja check` compares assembled sections/relocations, rebuilds complete containers with original metadata, and compares the full Game module files. `python tools/xff_split.py iso/KERNEL.XFF --check` performs only the section/relocation comparison for one module.
- `check` compares the flattened code and data images (every loaded byte). It doesn't compare ELF headers.
- `python tools/check_baserom.py` checks that `iso/SCUS_974.72` is the expected Original (SHA1 in `config/baserom.json`).

## Matching a function (Game modules)

1. Find the function in `asm/xff/<MODULE>/text.s` (`glabel <name>`). Small functions, and functions in a Source group with known ones from `tools/xff_tus.py`, are good starting points.
2. Write it in `src/xff/<MODULE>/<name>.c`. When `tools/xff_tus.py` has identified the Original source file, use one C file for it (e.g. `src/xff/GAMECORE/sword.c`), with its statics in the original order and functions in original order; otherwise one file per function. Use struct layouts with explicit padding until real headers exist.
   `python tools/m2c.py <function>` prints a first draft from m2c. Add `--through func_XXXXXXXX` when spimdisasm split the function at a tail call. Expect to fix types and structure by hand.
   For native EE type declarations, use `--ee-context types.c` (repeatable, self-contained declarations without preprocessor directives). Native `long` is 8 bytes; m2c's ordinary `--context` interprets it as 4. The wrapper adapts integer `long` to `long long` in temporary context files. Existing `--context` remains unchanged for declarations already written for m2c. Plain contexts are loaded before adapted contexts. Review the resulting draft's calls, pointer offsets and buffers; context conversion does not prove a match.
3. Iterate with `python tools/try_compilers.py src/xff/<MODULE>/<name>.c --module <MODULE> --only ee-gcc2.96 --flags "-O2 -G0"` until it says MATCH. `--diff` prints a side-by-side listing of each mismatch.
4. Run `python configure.py` (picks up new C files), then `ninja check`.
   Don't run `tools/progress.py` or touch the README progress table in a matching PR: every PR would edit the same lines and conflict with the others. The table is refreshed on main periodically, in its own PR.
5. If it's close but stuck on register allocation or instruction order, keep it as a Parked attempt in `#ifdef NONMATCHING` (with an `#else` declaring it extern if other C calls it). Then let the permuter search:
   - `python tools/permute.py setup <file.c> <function>`
   - `python tools/permute.py run build/permuter/<function> -j5 --best-only --stop-on-zero`
   - Improvements land in `build/permuter/<function>/output-<score>-*/`. A score of 0 is a match.
   - Copy the useful change back by hand, then check with try_compilers.

How it builds:
- `tools/ee_cc.py` compiles each C file with `ee-gcc` 2.96 + `ee-as` (in WSL). Before assembling, empty `.set noreorder`/`.set reorder` pairs go before every jump or branch gcc leaves to the assembler (and around volatile accesses), because the original assembler never filled a delay slot itself (see `docs/findings.md`).
- `tools/xff_splice.py` writes `build/xff/<MODULE>/spliced/`, which is the Game module's asm with each Matched function replaced by the compiled words. Relocated words become explicit `.reloc` directives.
- The Game module is assembled from that copy and checked as usual.

The splice step refuses any C function that doesn't match the Original exactly, so a wrong function fails the build instead of slipping in.

C data (string literals, `switch` jump tables, constants and statics in `.rodata`/`.data`/`.bss`):
- Each C data section is placed where the original references it (the original relocation paired with each C reference, or an original symbol of the same name). All anchors must agree, so a C file's data has to be laid out like the original's.
- Its bytes and relocations must match there; the matching lines in `rodata.s`/`data.s` are regenerated from the C output.
- Statics have no Original names. Give them their asm label as a Placeholder name (`func_000C5468`, `T_000C5570`, `D_0017B0EC`) and they're placed at that address; a renamed static function is placed by its callers' references instead. `extern` declarations with such names reference statics that aren't Matched functions yet, section-relative like the Original.
- spimdisasm sometimes ends a function at a tail call and labels the rest `func_XXXXXXXX`. The C function replaces both; try_compilers compares the full length.
- gcc 2.96 keeps unused statics and emits them in definition order. `= 0` statics go to `.data`, uninitialized ones to `.bss`.

Splice limitations:
- Whether a reference is section-relative (same Original source file) or by name is taken from the original relocation at that spot, until the C files mirror the Original source files.

## Tests and lint

- `pytest` covers the Python tools in `tools/` and `configure.py`'s helpers
- `ruff check .` and `ruff format --check .` (fix with `ruff format .`)
- CI (`.github/workflows/ci.yml`) runs both on every PR. CI has no game files and no PS2 toolchain, so it can't run the matching build.
- `port/` (Native port) builds with CMake and Clang, and its tests use synthetic data only:
  `cmake -S port -B build/port -G Ninja -DCMAKE_C_COMPILER=clang -DSOTC_PORT_WERROR=ON`, then `cmake --build build/port` and `ctest --test-dir build/port`.
  CI also runs them with `-DSOTC_PORT_SANITIZE=ON` (ASan and UBSan).

## Layout

- `SCUS_974.72.yaml`: splat config. Its `sha1` is the flattened image's hash, not the ELF's.
- `symbol_addrs.txt`: named symbols (hand-maintained). `linker_script_extra.ld`: entry point.
- `configure.py`: generates `build.ninja`
- `tools/`: helper scripts; `tests/` covers them with synthetic data (CI has no game files)
  - `elf2rom.py`, `check.py`, `check_baserom.py`: Loader
  - `xff2.py`: XFF reader/writer and XFF <-> ELF converter (`info`, `to-elf`, `from-elf`, `roundtrip`)
  - `xff_rebuild.py`: rebuilds complete Game modules from assembled payloads and original layout metadata, verifying symbol locations and relocations
  - `xff_split.py`: disassembles an XFF with spimdisasm, then post-processes the asm so it reassembles exactly (rules in its docstring)
  - `loader_funcs.py`: sorts the Loader's functions into Game code and SDK routines (`--write` regenerates `config/loader_functions.csv`, `--check` checks it)
  - `xff_tus.py`: infers Source groups from relocations (`--list` prints every group); results summarized in `docs/findings.md`
  - `ee_cc.py`: compiles one C file with the game's toolchain
  - `xff_splice.py`: splices compiled C functions into a Game module's asm, verifying they match
  - `try_compilers.py`: compiles C with candidate compilers/flags and diffs against the original functions
  - `progress.py`: refreshes the README progress table from each Game module's symbol table, relocations and the matching C (needs `iso/` and `asm/`)
  - `sdk_routines.py`: checks `config/sdk_routines.txt`, the SDK routines identified in the Game modules by signature, and prints entries for new ones
  - `m2c.py`, `permute.py`: run m2c and decomp-permuter on an XFF function
  - `refrun.py`: records and diffs Reference runs from PCSX2 (`docs/reference-runs.md`), with `pine.py` (PCSX2 PINE client), `p2m2.py` (Input Recording files) and `disc.py` (reads files from a Disc image)
- `asm/xff/<MODULE>/`: generated Game module assembly (gitignored like all asm)
- `include/xff_macro.inc`: label macros for Game module asm. Labels are local by default; `.globl` comes from the original symbol table.
- `include/`: `macro.inc`, `labels.inc`, `include_asm.h` (splat helpers) and, later, headers
- `src/xff/<MODULE>/`: Matched functions for the Game modules, one file per function for now
- `experiments/`: C used to identify the compiler (not part of the build)
- `port/`: the Native port, separate from the matching build (ADRs 0005 and 0010)
  - `disc/disc_image.c`: reads files from the owner's Disc image (ISO 9660, 2048- or 2352-byte sectors)
  - `disc/nicodat.c`: parses the `NICO.DAT` header (format in `docs/nicodat.md`)
  - `tools/nicoinfo.c`: prints a Disc image's `NICO.DAT` table of contents
  - `render/`: the Render translator prototype (`docs/render-translator.md`): `gsdump.c` reads PCSX2 GS dumps, `gs_vram.c` models GS memory layouts, `gs_translate.c` turns GIF packets into draw batches, `gs_ref.c` is the CPU reference backend
  - `tools/gsframe.c`: draws one frame of a GS dump to a PNG, next to PCSX2's screenshot
  - `tests/`: CTest programs on synthetic images and archives
- `docs/findings.md`: what we know about the binaries, the compiler and the SDK
- `config/baserom.json`: expected Original Loader path and SHA1
- `config/refrun/state.toml`: the state map, listing the game state each Reference run frame records
- `refruns/`: local Reference runs (gitignored: they need the disc)
- `config/sdk_routines.txt`: SDK routines identified in the Game modules (name, library, size, signature)
- `config/loader_functions.csv`: every Loader function with its Original or Placeholder name, class (Game code / SDK routine) and library

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
- The Game modules reference a global defined in the same Original source file as section+offset, but a global from another file by name. That's a hint at Original source file boundaries, useful later when splitting into C files.

## Worktrees

- Agent work happens in one worktree per task under `.worktrees/` (gitignored).
- Once a task's PR has merged (or the task is dropped), remove its worktree with `git worktree remove .worktrees/<name>` and delete its local branch with `git branch -D <branch>` (`-D` because squash merges don't look merged to git). Record anything worth keeping in the handoff first.
- Before starting a new task, remove any leftover worktrees whose PRs have merged. Leave alone worktrees with uncommitted changes or unmerged work, since another agent may own them.

## Agent skills

### Issue tracker

Issues live in this repo's GitHub Issues, managed with the `gh` CLI. See `docs/agents/issue-tracker.md`.

- Open and label issues for bugs, including bugs discovered during development, and feature requests explicitly requested by the project owner.
- Track routine development, matching decompilation, maintenance, refactoring and documentation directly through focused PRs. These work items do not need issues.
- Outside contributors must open an issue to discuss their proposed change before opening a PR.
- This project-specific policy replaces the general requirement to file an issue before every work item. Keep one PR per work item and retain the normal verification and CI gates.

### Triage labels

Default five-role vocabulary: `needs-triage`, `needs-info`, `ready-for-agent`, `ready-for-human`, `wontfix`. See `docs/agents/triage-labels.md`.

### Domain docs

Single-context: one `GLOSSARY.md` and `docs/adr/` at the repo root. See `docs/agents/domain.md`.
