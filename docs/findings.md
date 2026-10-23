# Binary findings

Notes on what's on the NTSC-U disc (`SCUS-97472`) and what we know about how it was built. Update this as evidence comes in.

## Disc layout

`SYSTEM.CNF` boots `cdrom0:\SCUS_974.72;1` (`VER = 1.00`, `VMODE = NTSC`).

| File | Size | SHA1 | What it is |
| --- | ---: | --- | --- |
| `SCUS_974.72` | 242,940 | `b715b3496aad6f7601a0ab8495acd1d151a1ff7b` | Loader ELF (this repo's first target) |
| `STARTUP.XFF` | 26 | `7d1bc867741c9b5ea456192051155b46788af7f8` | Text: `cdrom0:\KERNEL.XFF;1 0x400` |
| `KERNEL.XFF` | 415,908 | `1da339dbf97743ff78f5a78550d2ff83d64a237b` | Game module (`xff2`) |
| `MANAGER.XFF` | 1,650,876 | `5e3cc1cb4338b45e427aa8df45e50db181b1c6a7` | Game module (`xff2`) |
| `GAMECORE.XFF` | 2,141,864 | `4c65034d52883927250ad8994cb39f5074c05555` | Game module (`xff2`) |

Almost all game code lives in the `.XFF` modules, a custom relocatable format with the magic `xff2`. The ELF loads them at runtime. A couple of source filenames survive inside them (`effectmanager.c` in MANAGER, `sword.c` in GAMECORE). Reversing the format is tracked separately.

## Original source files in the XFF modules

The original relocations show where each `.c` file started and ended (`tools/xff_tus.py`):
- **Same-file references:** a reference made section-relative stays inside one source file. Statics always are; a global only when it's defined in the same file. Since `ld -r` keeps each file's code contiguous, every function between the two ends belongs to that file.
- **Cross-file references:** a reference by name to a global defined in the same module crosses files.

| Module | Functions | Groups | Functions in multi-function groups | Same-file refs | Cross-file refs | Conflicts |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| KERNEL | 940 | 375 | 608 | 491 | 1,017 | 31 |
| MANAGER | 2,277 | 592 | 1,765 | 2,227 | 4,739 | 62 |
| GAMECORE | 2,755 | 773 | 2,096 | 2,763 | 6,972 | 88 |

- **Groups are lower bounds.** A real file may span several adjacent groups when nothing ties them together.
- **Conflicts** are by-name references between functions that other evidence places in one file. They're about 1–3% of by-name references, and they persist with calls-only evidence, so they're likely real by-name references within one file. Treat the "by name means another file" rule as strong evidence, not proof.
- **Names:** only a few strings name source files. A group of 35 GAMECORE functions references `sword.c` (path `basescript/src/sword.c`), and MANAGER has `effectmanager.c`.
- **sword.c** (being decompiled in `src/xff/GAMECORE/sword.c`) starts at least at `BossSprStatusBegin` (it shares a static with the group) and runs past `SCRDirectionalArrowEnd` (which references a static at `0xC5718`). Its `.data` block is `0x17B070`–`0x17B1F0`: the sword effect tuning values the `get*` functions return, the sound handles and 11 particle emitter slots.

## Loader ELF (`SCUS_974.72`)

- ELF32, little-endian MIPS, `ET_EXEC`, `e_flags = 0x20924001` (R5900), entry `0x100010`
- No symbol table and no DWARF. `.mdebug.eabi64` is present but empty.
- Flattened image (`tools/elf2rom.py`): `0x3A180` bytes, SHA1 `325b0c60131d3f7ae877119cf70d8482d90c57b7`
- `_gp = 0x141D70` (`.lit4` start + `0x7FF0`)

| Section | VRAM | Size |
| --- | --- | ---: |
| `.text` | `0x100000` | `0x31BAC` |
| `.text_nop` | `0x131BAC` | `0x8` |
| `.reginfo` | `0x131BB4` | `0x18` |
| `.data` | `0x131C00` | `0x44CC` |
| `.ctors` / `.dtors` | `0x1360CC` / `0x1360D4` | `0x8` each |
| `.eh_frame` | `0x1360E0` | `0x4` |
| `.rodata` | `0x136100` | `0x3C58` |
| `.lit4` | `0x139D80` | `0x4` |
| `.data_nop` | `0x139D84` | `0x8` |
| `.sdata` | `0x139E00` | `0x380` |
| `.sbss` | `0x13A180` | `0x10` (NOBITS) |
| `.bss` | `0x13A200` | `0x30198` (NOBITS) |

splat finds 1,038 functions and about 51,000 instructions in `.text`.

## Compiler (game code): `ee-gcc` 2.96, `-O2 -G0`

**Chosen:** Sony's `ee-gcc` 2.96 (`2.96-ee-001003-1`, from decomp.me's compiler archive), `-O2 -G0`, assembled with the `ee-as` shipped alongside it. I tested by compiling hand-written C for 11 GAMECORE functions with every PS2 GCC in the archive (`tools/try_compilers.py`, sources in `experiments/`), and comparing instruction by instruction, ignoring relocated fields.

| Candidate | Exact matches (of 11) | Why it's ruled out |
| --- | ---: | --- |
| **ee-gcc 2.96 + its ee-as** | **9** | Best match. The 2 misses differ only in register allocation or scheduling (see below). |
| ee-gcc 2.95.2 / 2.95.3 (all builds) | 8 | Can't produce `ResetObject`'s tail call (2.95 has no sibling-call optimization), and lays out `getPathExFinish`'s jump table differently. |
| ee-gcc 2.9 (990721, 991111) | 7 | Misses the tail call, the jump table and `GAMEUTIL_reset_position_filter`. |
| ee-gcc 3.2 (030926, 040921) | 0 | Different code generation everywhere. |

- **Both initial 2.96 misses differed only in register allocation or scheduling, which points to the exact source shape:**
  - `calcFadeParam` had identical structure, but the floats landed in different registers. It now matches in `src/xff/GAMECORE/calcFadeParam.c`: normalize the time local in place, then accumulate into the value local. The original compiler-ID experiment is retained unchanged.
  - `GAMEUTIL_reset_position_filter` initially had the same instructions in a different order. It now matches with 2.96 in `src/xff/GAMECORE/GAMEUTIL_reset_position_filter.c`: a union view of the filter preserves the original 128-bit copy and count-store order. Both initial misses are now fully verified; the compiler-ID experiments remain unchanged.
- **Assembler matters:** 2.96 emits macros (`move`, `lw reg, table(reg)`) that the assembler expands. The original expansions (`daddu rd, rs, $zero`; jump-table address via `addu`) match the package's `ee-as`, not modern binutils. All 84 GAMECORE jump tables use `addu`.
- **Final calls that are not tail calls (#382):** 2.96 turns a call followed by a return into a `j`, so a function whose last call is a plain `jal` needs something between the call and the return in the source, even if it is optimized away later. A dead assignment after the call does it (`p = 0;`), and so does returning a variable that the call only conditionally overwrites. Return types, implicit declarations and inline helpers don't matter.
- **Volatile accesses stay out of delay slots (#372):** 2.96 brackets every volatile load and store with `.set volatile` / `.set novolatile`, but in GAS mode it writes them as comments (`#.set volatile`), so our `ee-as` happily moves a volatile `lw`/`sw` into the following branch's delay slot. The original never does: `getVIntrCnt`, `getIntrGpCount`, `iosGetTCount` and `ischedStop` end in `lw`/`sw; jr $ra; nop`. `tools/try_compilers.py` (and so `ee_cc.py`) turns each marker into an empty `.set noreorder` / `.set reorder` pair, which `ee-as` treats as a reorder barrier. With that rule every previously matching function still matches, except two MANAGER setters that had used `volatile` only to force a store order; both now match with plain, natural C. So `volatile` in matching C means a real volatile object (hardware registers, interrupt-shared counters), not an ordering trick.
- **Indexed `la` stays out of delay slots:** 2.96 writes the address of an array element with a constant base as the macro `la $r,sym($b)`, and knowing it is several instructions, leaves the following jump's delay slot to the assembler. `ee-as` expands it to `lui $at` / `addiu $at` / `addu $r,$at,$b` and then moves that last `addu` into the delay slot. The original build never did: across all three modules, every `addu ...,$at,...` directly before a jump or branch (28 sites, e.g. `GetCurrentQuaternion`, `getPathInfo`, `graphInitLayer`) is followed by an unfilled `nop` slot, and none sits in a delay slot. `tools/try_compilers.py` therefore puts an empty `.set noreorder` / `.set reorder` pair after each indexed `la`, the same barrier as for volatile accesses. Every previously matching function still matches with the rule; it is what made `GetCurrentQuaternion`, `GetScriptPriorityGroup`, `getPathInfo`, `_optionWorkPtr`, `isysGetGroupSrhNext` and `graphInitLayer` match. `ee-as -O0`/`-O1` doesn't change the reordering.
- **The original assembler never filled a delay slot:** the volatile and indexed-`la` rules are two cases of one difference. gcc fills the delay slots it can inside its own `.set noreorder` blocks and writes every other jump or branch in reorder mode, leaving the slot to the assembler. Our `ee-as` then moves an earlier instruction into it; the original assembler left a `nop`. Evidence: `dsra32` occurs 270 times across the modules and never in a delay slot, because gcc emits a sign extension as the two-instruction pair `dsll`/`dsra $r,$r,32`, which it won't put in a slot itself (`iosGetField` ends `dsra32; jr $ra; nop`). `tools/try_compilers.py` therefore puts an empty `.set noreorder` / `.set reorder` pair before every jump or branch gcc emits in reorder mode. With that rule every previously matching function still matches (full `ninja check`), and `iosGetField` matches as well. `ee-as -O0`/`-O1` doesn't change the reordering, so the original build may have used an assembler version without it.
- **Inline address getters:** `st_defaultAI` matches with a static inline getter returning the address of `gcGlobalVar`. Direct global access folds the address into the loads and emits 22 words; the inline getter preserves a materialized base and the original call/constant schedule, giving the matching 24-word function. This establishes a usable source shape; the original helper declaration is still unknown. See `src/xff/GAMECORE/st_defaultAI.c`.
- **`-G0`:** none of the three modules contains a single gp-relative relocation.
- **Source-specific alias option (#726):** the plain-C `SetDemoMotionOrientInfo`
  candidate differs by 30 instructions with the base flags, but matches all 76
  instructions with `-O2 -G0 -fno-strict-aliasing`. The original reloads encoded
  resource words after storing the manager's pointer fields; strict alias
  optimization reuses those loads and moves the stores. The adjacent recovered
  `GetDemoOrientNext` matches with either setting. This establishes a reproducible
  setting for this source, rather than proving the original command line for
  every translation unit. `config/ee_cflags.json` records the additional option
  only for `src/xff/MANAGER/SetDemoMotionOrientInfo.c`; other sources retain the
  base flags. `ee_cc.py` reads that file, and Ninja tracks it as a compiler input.
  Standalone comparisons must include the additional option explicitly:
  `python tools/try_compilers.py src/xff/MANAGER/SetDemoMotionOrientInfo.c --module MANAGER --only ee-gcc2.96 --flags "-O2 -G0 -fno-strict-aliasing"`.
- **`-O2` over `-O3`:** 41 tiny static functions (6 instructions or fewer) across the modules are still called rather than inlined, which `-O3` would have done.
- **Float literals:** 2.96 truncates decimal float literals instead of rounding to nearest (`0.15f` gives `0x3E199999`, `0.735f` gives `0x3F3C28F5`). The original data has exactly these values, so plain literals like `0.15f` are right. A value that needs more digits, like π/180 (`0x3C8EFA35`), must be written with enough of them: `0.0174532925f`, not `0.017453292f`.

Running the compilers: the Linux builds are 32-bit, so they run under WSL with a private 32-bit libc, unpacked from Ubuntu's `libc6:i386` package into `~/i386libs` (no `sudo` needed). They must run from WSL's own filesystem, because old 32-bit programs can't read files on Windows-mounted drives ("Value too large for defined data type").

### Native EE declarations in m2c context (#331)

Compile-time assertions with the original ee-gcc 2.96 confirm `sizeof(long) == 8`, `sizeof(long long) == 8`, `sizeof(int) == 4` and `sizeof(void *) == 4`. m2c currently treats a single integer `long` as 4 bytes even with the `mipsee-gcc-c` target. Passing native declarations through ordinary `--context` can therefore truncate the inferred inputs and results. This was reproduced with the 64-bit mask and return of `nico_GetCharacterAttackedGPAttr`.

`python tools/m2c.py FUNCTION --ee-context types.c --valid-syntax` adapts native EE declarations into temporary m2c context: integer `long` becomes `long long`; existing `long long`, `long double`, comments and literals stay unchanged. The input file and external decompiler are never edited. Use self-contained declarations without `#include` or macros; preprocessor directives are rejected because their expansion could change the types. Repeat the option for multiple files. Ordinary `--context` files pass through unchanged and are loaded before the adapted files, so place dependencies accordingly.

The adapted real-function draft retains 64-bit inputs/results (`s64`), while the same native declarations under ordinary `--context` produce `s32`. This verifies the width correction, not the rest of a draft: missing callee prototypes, pointer scaling and buffer sizes still need review. Compiler-facing source should use reviewed native declarations and must pass the original compiler and complete matching checks. Existing matching C and compiler flags are unchanged.

## Compiler fingerprint (loader ELF, earlier static analysis)

**GCC-based, not Metrowerks: high confidence (about 90%).**
- The section set is what GNU `ld` produces from GCC objects: `.reginfo`, `.mdebug.eabi64`, `.ctors`/`.dtors` holding only the `-1`/`0` sentinels from `crtbegin`/`crtend`, and a 4-byte `.eh_frame` terminator.
- Register moves are almost all `daddu rd, rs, $zero` (5,867 of them) and the return address is saved with `sd` (685 functions). Heavy use of branch-likely (`beql`/`bnel`, about 640). This is the usual EE GCC 2.9x codegen.

**Sony `ee-gcc` vs SN Systems ProDG: undecided.** ProDG's compiler is itself a GCC fork, so this codegen fits both. Nothing in the ELF names the toolchain (no `GCC:` `.comment` strings, no SN or ProDG strings).

**Version: probably GCC 2.95/2.96-era EE GCC, low confidence.** The linked SDK is 3.0.x (2003–2004), which shipped with `ee-gcc` 2.96. The exact build is unknown.

Most of this ELF is Sony SDK library code that Sony compiled, so these patterns say more about the SDK than about Team Ico's own code. The game code in the `.XFF` modules needs its own fingerprinting.

## Sony SDK libraries in the ELF

From the `PsIIlib<name><version>` tags and library error strings. The version is SDK `3.0.x`; `3020` means 3.0.2.

| Library | Version tag | Other evidence |
| --- | --- | --- |
| libkernl (incl. libc) | 3000 | `SceKernelLibc`, `SceKernelLibcEh`, `SceKerneltopThread`, `vfprintf` message |
| libcdvd | 3000 | `Libcdvd bind err ...`, `SceCd*Sema`, `sceCdChgSys` |
| libdma | 3000 | `libdma: sync timeout` |
| libgraph | 3000 | `sceGsDefDispEnv`, `sceGsSyncPath`, `sceGsPutDrawEnv` messages |
| libpkt | 3000 | version tag only |
| libpad2 | 3020 | `libpad2: buffer addr is not 64 byte align` |
| libmc2 | 3020 | `libmc2: ...` errors, `sceMc2_*` thread and semaphore names |
| libvib | 3000 | version tag only |
| libdbc | 3020 | `sceDbc*: rpc error`, `DBCMAN.IRX` version check |
| libnet | 3000 | `insufficient buffer size in Libnet`, `LIBNET.IRX` |
| libmrpc | 3000 | `SceMrpcBind*`, `SceMrpcCall`, `sceSifMCallRpc` |

The ELF also references these IOP modules: `IOPRP300.IMG`, `MCMAN`, `MCSERV`, `NETCNFIF`, `DBCMAN`, `DEV9`, `INET`, `INETCTL`, `LIBNET`, `MSIFRPC`, `AN986`, `DS1O_D`, and others.

These libraries are candidates to identify by signature matching against the SDK 3.0.x libraries, rather than decompiling them by hand. Function-level boundaries haven't been mapped yet.
## Original sequence-stop interrupt state (#708)

In KERNEL `Sg2SepStop` (text offset `0x25E88`), an in-range sequence ID with
nonpositive status branches from `0x25EC4` to `0x25F10`. This skips `DIntr`
and the assignment of its result to `s3`, but still tests `s3` and may call
`EIntr`. That path depends on the incoming caller-preserved register rather
than an interrupt state captured by this function. The neighboring
`Sg2SepStopSndOff` instead exits directly for nonpositive status.

This is an instruction/data-flow finding, without a runtime reproduction.
Preserve it during matching. [Issue #708](https://github.com/TheRealestNwah/sotc-decomp/issues/708)
tracks confirming the intended inactive-sequence contract and interrupt
restoration during future port planning.
