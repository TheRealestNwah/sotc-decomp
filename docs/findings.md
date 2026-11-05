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
| `NICO.DAT` | 2,667,340,678 | | Asset archive ([docs/nicodat.md](nicodat.md)) |

The owner's full image (`Shadow of the Colossus (USA).iso`, 1,315,408 sectors of 2048 bytes) has SHA1 `bd5dcb38bc1a08b261accd1b53894ee4e934788f` and MD5 `6d4a7a9d9c139a9d93db37538ba6d984`. All five files above read out of it with the hashes listed.

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
- **Indexed `lw` is written out before assembling:** 2.96 writes an indexed load from a constant-base array (`name = table[i];`) as the macro `lw $r,sym($b)`. `ee-as` expands it to `lui` / `addu` / `lw %lo`, but in some positions it encodes the `lui` with the `lw` opcode (`8e100000` instead of `3c100000`, issue #2343). Deleting almost any earlier line of the same `.s`, even a blank one, makes the bad encoding go away, so it depends on where the macro lands, not on the instruction. The opcode bits sit outside the HI16 relocation, so such a function can never match. `tools/try_compilers.py` therefore rewrites each indexed `lw` with a symbol operand into the expansion the assembler makes itself (`lui $r,%hi(sym)` / `addu $r,$r,$b` / `lw $r,%lo(sym)($r)`, through `$at` when `$r` is the base), for -G0 code only. Every previously matching function still matches, and `ReplayPauseScript` matches with it.
- **Indexed `lhu` has the same encoding fault (#2265):** KERNEL `func_0002F0D8` emits `lhu $2,pan_tbl($5)`, whose expansion can start with `94420000` (`lhu`) instead of `3c020000` (`lui`) at function offset `0x48`, carrying the same HI16 relocation. The indexed-load workaround also writes out `lhu` expansions for `-G0`; this removes the one verified word difference in that reproducer. Section-relative targets still require the splice checks. Loader `-G8` loads remain under the assembler's small-data handling.
- **Inline VU blocks must restore assembler mode (#2391):** six C blocks entered `.set noreorder` without restoring `.set reorder`, leaving their compiler-generated final `jr $ra` with no following word in the compiled object. Their output was four bytes shorter than the explicit Original function size. Restoring reorder mode after each block makes the original assembler emit the complete Original delay slot; all six full function comparisons and strict splice checks pass. The XFF splice check now requires the explicit Original size for named functions (#2389), so an incomplete matching prefix cannot silently retain the Original assembly suffix. Placeholder statics and symbols without an explicit size retain their existing placement and comparison rules.
- **Inline address getters:** `st_defaultAI` matches with a static inline getter returning the address of `gcGlobalVar`. Direct global access folds the address into the loads and emits 22 words; the inline getter preserves a materialized base and the original call/constant schedule, giving the matching 24-word function. This establishes a usable source shape; the original helper declaration is still unknown. See `src/xff/GAMECORE/st_defaultAI.c`.
- **Callee return types affect register allocation:** a function declared `void` and one declared `int` (with the result ignored) can produce different temporaries in the caller after the call. `stagemanager_refleshCurrentArea` and `iosDlLockObj` differed only in v0/v1 choices while their callee was declared `void`. Both callees really return `int`: `isysAddGroupWithLinkParam` is declared `int` by 20 existing callers, and `isysAddGroupWithLinkParamNoWait` is a tail-call wrapper that passes that result through (its recovered C says `void`, which the wrapper's matching bytes can't distinguish). When a near-miss differs only in which scratch register holds a value after a call, check the callee's real return value before restructuring the source.
- **Global base taken inside a loop:** `stagemanager_refleshCurrentArea` keeps the full address of `gcGlobalVar` in a saved register (`lui`/`addiu` into an `s` register, then `lw 0x308(sX)`) instead of folding `0x308` into `%lo`. A local `char *g = gcGlobalVar;` declared inside the loop body reproduces it; the same access written directly folds the offset.
- **Leftover delay-slot `nop` from a one-pass loop:** `isysGroupForNextForce` has a lone `nop` after its ternary that its filtering sibling `isysGroupForNext` leaves as the delay slot of the loop's back jump. Wrapping the advance in `do { ... } while (0);` reproduces it: gcc removes the jump but keeps the slot. "Force" variants appear to be the filtering function with the loop condition deleted.
- **Store order decides whether gcc merges branch tails:** in `push_back_letter_in_post` both branches store the new tail, but the original keeps two copies. Writing the empty-list branch as head store then tail store matches; tail then head lets the scheduler and cross-jumping move the tail store into a shared exit, which is what stalled earlier attempts at 3 differences.
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
- **Object-deletion source alias option (#1248):** the recovered
  `isysRequestDeleteObj` matches all 68 instructions with
  `-O2 -G0 -fno-strict-aliasing`. With the base flags, the same source differs
  by eight instructions: the queue-head load moves before the object header
  store, and the compiler changes the temporaries used for that update. The
  source uses the object header layout already recovered in `_isysCreateObj`
  and the existing recursive-lock/unlock bodies. A pointer-field queue view
  still differs by 12 instructions with the base flags. The additional option
  is recorded only for `src/xff/KERNEL/isysRequestDeleteObj.c` in
  `config/ee_cflags.json`; this does not establish flags for other sources.
- **Camera, life-bar, kite and list-pop source alias option:** four recovered
  GAMECORE sources match only with `-O2 -G0 -fno-strict-aliasing`. With the
  base flags they differ by:
  - `doit_camera_etc_condition`: 4 instructions
  - `playerlifebar_script`: 19 instructions
  - `nico_SmallKiteAdvertiseStart`: 4 instructions
  - the static `func_000B6A58`: 12 instructions

  The additional option is recorded only for these four files in `config/ee_cflags.json`; this does not establish flags for other sources.
- **List-transfer source alias option:** the recovered GAMECORE static
  `func_000B7220` (remove a node from one list, append it to the list at
  `w + 0x244`) matches all 62 instructions with `-O2 -G0 -fno-strict-aliasing`.
  With the base flags, the same source differs by four instructions: the
  appended list's count load moves above the node's `next` and the list's
  `tail` stores, which strict alias optimization treats as unrelated. The
  additional option is recorded only for `src/xff/GAMECORE/func_000B7220.c`
  in `config/ee_cflags.json`; this does not establish flags for other sources.
- **Worm-history source alias option:** the recovered GAMECORE
  `func_001289B8` (append a position/direction pair to a 32-entry worm
  history after a distance check) matches with `-O2 -G0 -fno-strict-aliasing`.
  With the base flags, the same source differs by 15 instructions: the
  original reloads the history index (`w + 0x604`) after storing the
  128-bit position, before storing the direction; strict alias
  optimization reuses the earlier index load and drops that reload. The additional
  option is recorded only for `src/xff/GAMECORE/func_001289B8.c` in
  `config/ee_cflags.json`; this does not establish flags for other sources.
- **Path-work and list source alias option:** the recovered GAMECORE
  `Kite_InitKitePathWork` (113 words), `func_000B1BC8` (112 words) and
  `func_000B2890` (115 words) match with `-O2 -G0 -fno-strict-aliasing`.
  With the base flags, the same sources differ by 9, 14 and 15 instructions:
  the originals reload fields after stores through differently typed
  pointers, which strict alias optimization treats as unrelated and reuses.
  The additional option is recorded only for these three sources in
  `config/ee_cflags.json`; this does not establish flags for other sources.
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

These libraries are candidates to identify by signature matching against the SDK 3.0.x libraries, rather than decompiling them by hand.

### Loader function map

`config/loader_functions.csv` (written by `tools/loader_funcs.py`) lists every Loader function with its class: Game code or SDK routine.

- KERNEL.XFF links against the Loader, so its symbol table has 845 absolute (`SHN_ABS`) function symbols naming Loader functions, with Original names and sizes, plus 67 absolute objects (`loaderThreadJumpCode`, `moduleInfo`, `__ps2_klibinfo__`, ...). They come from the Original disc, not from any Sony library file.
- Five of those names start in the middle of a splat function (`LoaderSysJumpRecoverPointNoStateSetting`, `_kExitTLBHandler`, `_kDebugException`, `sceCdInitEeCB`, `atexit`), and two Original functions end before splat's does with code after them (`func_00101AA0`, `func_0010F8DC`). The list gives each its own row: 1,045 functions against splat's 1,038.
- The Loader links its game objects first: `0x1000D0`–`0x106BC0` (`ResolveRelocation` through `PutChar`: the xff loader, `LoaderSys*`, `padSys*`, `usbSerialSys*`, the debug font and display) is Game code, 123 functions and 0x69C4 bytes counting the two-word pointer table at `0x100000`. crt0 (`_start`) sits between them.
- Everything from `RFU000_FullReset` (libkernl syscall stubs) to the end of `.text` is SDK, in contiguous library blocks: libkernl, libpkt, libgraph, libdma, libpad2, libvib, libdbc, libcdvd, libinet, libnet, libmrpc, libmc2, netcnfif, libgcc, newlib libc, then libkernl's cache routines and two libgcc helpers. Unnamed functions take the library of the block they sit in.
- **The Loader's Game code was compiled with small data (`-G8`, gcc's default), unlike the Game modules' `-G0`.** Its globals are read through `$gp` (`_gp` = `0x141D70`): `SetHeapStartPoint` stores with `sw $a0, %gp_rel(D_00139E04)($gp)`. ee-gcc 2.96 `-O2 -G8` with an `extern int` of that size gives exactly that, so `tools/ee_cc.py` builds `src/loader/` with `-O2 -G8` and assembles with `ee-as -G 8`. `SetHeapStartPoint` and `GetHeapCurrentPoint` match this way.
- Loader C is spliced by `tools/loader_splice.py`. The Loader is a linked executable, so its asm has no relocations, only symbolic operands (`jal`, `%hi`/`%lo`, `%gp_rel`). The splice checks each C relocation against the original operand's type and target address, then keeps the original line, so the build links as before.

## Counting functions in the Game modules (#2285)

A Game module's functions are its `STT_FUNC` symbols in `.text` plus the static functions that have only Placeholder names. `tools/progress.py` counts both from the Original:

- **Named symbols.** KERNEL's symbol table has 1,785 `STT_FUNC` entries, but 845 of them are absolute (`SHN_ABS`) Loader functions it imports, such as `ResolveRelocation` and `sceGsSyncV`. Only the 940 in `.text` are KERNEL's own. MANAGER has 2,277 and GAMECORE 2,755, all in `.text`.
- **Placeholder statics.** A `func_XXXXXXXX` or `T_XXXXXXXX` label counts when a section-relative relocation in the Original points at it: a `jal`, a function pointer in data or an address load. That gives 166 in KERNEL, 590 in MANAGER and 1,157 in GAMECORE. None falls inside a named symbol's extent. The labels spimdisasm makes where it splits a function at a tail call are never relocation targets, so they're left out. Only a handful of gaps between named functions (2 in KERNEL, 4 in MANAGER, 1 in GAMECORE) contain no counted label.
- **Statics only the C knows.** A static the matching C defines under another name, or at an address spimdisasm gave no function label (it reached it only by a `j`), counts too.

Before this, the README divided every spliced C function, statics included, by the named counts alone, so GAMECORE showed 2,753 of 2,755 while named functions such as `initbar` and `demo_end` had no C.

## SDK routines in KERNEL

KERNEL's `.text` ends with 39 SDK routines, from `0x30428` (asm label `func_00030460`) to the end of the section at `0x341A4`. The libraries were linked after the game's own objects, and the function just before the block (`Sg2StPcmQuit`) is Game code. They're listed with signatures in `config/sdk_routines.txt` (checked by `tools/sdk_routines.py`) and left out of the Game code totals.

| Library | Routines | Evidence |
| --- | ---: | --- |
| libc (newlib) | 4 | `mktime`, `strstr`, `div`, and `mktime.c`'s static `validate_structure` (`func_00030460`, just before `mktime`, called only by it). `mktime`, `strstr` and `div` already match as C written from newlib's source. |
| libm (newlib's float fdlibm) | 25 | Original names (`__ieee754_powf`, `__kernel_rem_pio2f`, the `sinf`/`cosf`/`floorf` family and the one-jump `acosf`-style wrappers); all match as C written from fdlibm's source. |
| libgraph | 5 | `sceGsSetDefLoadImage`, `sceGsExecLoadImage`, `sceGsPutIMR`, `sceGsGetIMR`, `isceGsPutIMR`. The first two print libgraph's own messages (`sceGsSetDefLoadImage: too big size`, `sceGsExecLoadImage: DMA Ch.2 does not terminate`); the IMR ones wrap the kernel calls `GsGetIMR`/`GsPutIMR` and `iGsGetIMR`/`iGsPutIMR`. |
| libcdvd | 5 | `sceCdRead`, `sceCdReadIOPm`, `sceCdGetError`, `sceCdStatus`, `sceCdReadClock`. All reference libcdvd's private state in the Loader (`_sceCd_ncmd_prechk`, `_sceCd_cd_ncmd`, `_sceCd_scmd_semid` and others) and call `sceSifCallRpc`. |

None of these names is also exported by the Loader: KERNEL links the library objects the Loader didn't. 28 of the libc/libm routines (all but `validate_structure`) are already Matched functions; that C stays, but no longer counts as Game code.

## SDK routines in MANAGER

MANAGER `rand` and `srand` are the newlib implementations: their 100 and 24 bytes,
respectively, and every relocation type and named target match an unmodified
rebuild of `newlib/libc/stdlib/rand.c`
from the [official newlib 1.11.0 source release](https://sourceware.org/ftp/newlib/newlib-1.11.0.tar.gz).
The reference uses the Sony `ee-gcc` 2.96 driver at `-O2 -G0`, the package's own
`ee-as`, and the same assembly preparation as the matching build.

The original release's headers supply the `_reent` layout; its random state
is at offset `0xA8`, accessed through `_impure_ptr`. The multiplication calls
`__muldi3`. The driver supplies its target ABI and endian predefines. Its
executable-only archive lacks `stddef.h`, so the reference include tree is
supplemented with the [GCC 2.95.3 standard header](https://raw.githubusercontent.com/gcc-mirror/gcc/releases/gcc-2.95.3/gcc/ginclude/stddef.h).
Neither the library source nor its layouts or generated instructions were
patched to obtain the match.

| Reference input | SHA-256 |
| --- | --- |
| `newlib-1.11.0.tar.gz` | `6ff74f1f273dbcf9f8e3eb79cac8ca5e7c98c14a27ac468eede50f1f45a7c4a1` |
| GCC 2.95.3 `stddef.h` | `23ed59b27cda4de82a312f98e85a258f29d61711beb873a42a1f8404558894ae` |

The normalized signatures are `0676307c435b6afc` for `rand` and
`d1687ebedd97b3b4` for `srand`, recorded in `config/sdk_routines.txt` and excluded
from the Game code totals. This establishes the implementation family; the exact
Sony library patch release remains unproven. Their existing Matched C stays in
the rebuild, as with KERNEL's identified library code; progress excludes both
routines from the completed and total Game code
counts. MANAGER's remaining routines and GAMECORE still need SDK sorting.

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

## AI damage-check object precondition (#490)

The Original GAMECORE `AI_CheckDamage_Impact`, `AI_CheckDamage_Sword` and
`AI_CheckDamage_Reaction` read the first word returned by `GetDamageClass`
before combining its value with the pointer's nonzero test. The reads are at
GAMECORE text offsets `0x9B5B8`, `0x9B618` and `0x9B678`, respectively.
The recovered bitwise expression `(d != 0) & (d[0] == 1)` preserves this
ordering; the apparent null test does not protect the read.

MANAGER `GetDamageClass` (`0xEB980`) first reads the object's unsigned type
byte at `object + 8`. Its supported cases resolve as follows, using
`GetCharacterClass` (`0x457E0`), `GetScriptLayoutClass` (`0x91DC8`) and
`GetScriptAnimationClass` (`0x8F5A8`):

| Object type | Damage pointer |
| --- | --- |
| `0x09` | `GetCharacterClass(object) + 0x200` = `object + 0x290` |
| `0x0B` | `GetScriptLayoutClass(object) + 0x230` = `object + 0x250` |
| `0x0D` | `GetScriptAnimationClass(object) + 0x230` = `object + 0x250` |
| `0x16` | `object + 0x290` directly |

Every other type returns zero. The three checks therefore require a live,
readable object of one of these types with readable damage storage. A null
object already fails inside `GetDamageClass`; an unsupported type reaches
the subsequent null-based damage read.

`AI_CheckDamage_Bow` and `AI_CheckDamage_SoundBow` instead short-circuit their
damage-pointer checks. Their false result is not evidence of a supported
object type: an unsupported type also returns false. For example,
`func_000A2D50` obtains the current subthread object and tries bow, sword,
sound-bow, then optionally impact. The bow call at GAMECORE `0xA2ED8` falls
through to the sword call at `0xA2EEC` when false, passing the same object.
That sequence supplies no type validation before the sword check.

These are static instruction and caller-data-flow findings. They do not
establish that an unsupported type reaches these checks during gameplay.
Keep the matching implementation unchanged. Before a Native-port correction,
trace the creation/type invariants of the current subthread and other caller
objects, then define and test the unsupported-type behavior deliberately.
[Issue #490](https://github.com/TheRealestNwah/sotc-decomp/issues/490) remains
open for that reachability and contract investigation.

## Sheet lookup missing-header contract (#492)

Original MANAGER `sheetMgrSearchSheetDataObj` (`0xE39F8`) indexes the header
pointer table `D_00139F10` using its sheet ID, then searches the selected
header's linked data objects by hash. A readable, initialized table, a valid
index and a present header are preconditions for this lookup.

The missing-header diagnostic does not safely handle an absent header:
`0xE3A1C` branches over it only when the selected header is nonzero. Otherwise
`0xE3A24` reads the descriptor at header `+0x38`, and the recovery call's delay
slot at `0xE3A34` reads the descriptor's first word as the diagnostic argument.
Both reads happen before `iosJumpRecoverPoint` can handle the error. Giving
that recovery function a nonreturning contract cannot protect argument
construction that has already dereferenced the absent header.

`sheetIdToName` (`0xE3998`) is not a safe substitute for that argument: its
loads at `0xE39A8`, `0xE39AC` and `0xE39B4` perform the same table-to-header,
header-to-descriptor and descriptor-to-name traversal without a missing-header
check. A future safe diagnostic needs information independent of the absent
header, such as the requested numeric sheet ID and hash, or a separately
validated name source.

A missing data entry is a different case. With a valid header, the search
starts from header `+0x40`, compares each entry's descriptor hash at
`entry->descriptor + 4`, and follows entry `+0x54`. Exhausting that list returns
zero through `0xE3A68`, without the missing-header diagnostic.

The two direct calls in `func_000E1270`, at MANAGER `0xE1340` and `0xE1510`,
pass sheet IDs and hashes read from request records. Those sites alone do not
establish that every requested header has been installed and remains live.
Trace request validation and header lifetime before defining a Native-port
error result. This is static instruction/data-flow evidence, without a
runtime reproduction. Preserve the original matching implementation;
[issue #492](https://github.com/TheRealestNwah/sotc-decomp/issues/492) remains
open for the missing-header contract and reachability investigation.

## Memory-card request-pool exhaustion (#1219)

Original MANAGER `initMcManager` clears two request state words in
`B_0014DB50`; each request occupies `0x30` bytes. The message queue is
initialized with capacity one. Request storage and queue capacity are separate:
the wrappers scan for a request whose state is zero before sending it.

In `mcGetInfo` (`0xCE1E0`), the scan limit is two at `0xCE220`. When both
requests are busy, `0xCE238` sets the selected request pointer to zero,
`0xCE23C` calls `LoaderSysPrintf`, then `0xCE24C` and `0xCE254` store the port
and slot through that zero pointer. The state store and message dispatch
follow. `mcGetMainDataInfo` (`0xCE2C8`) has the same scan/diagnostic shape;
its first post-diagnostic request store is at `0xCE334`.

The diagnostic is not a recovery jump. Original Loader `LoaderSysPrintf`
(`0x102CF8`) calls `vsprintf` at `0x102D48`, `printf` at `0x102D50` and
`strlen` at `0x102D58`, then returns normally at `0x102D64`. The specific
exhaustion message at MANAGER rodata address `0x140D10` is 31 bytes with no
percent directives, so the second-formatting concern in
[issue #2385](https://github.com/TheRealestNwah/sotc-decomp/issues/2385) does
not itself supply an escape from this path. Once the output calls return,
the caller continues to the null-based stores.

Successful `mcGetInfo` requests set their state, send the request, and invoke
the function pointer `B_0014DBB4` while waiting for that state to clear
(`0xCE280` through `0xCE298`). `mcReqSetWaitFunc` assigns this callback.
Before porting, audit both concurrent callers and reentrancy through the wait
callback; a synchronous wrapper alone does not establish that the two-slot
pool cannot be exhausted.

This is static instruction and data-flow evidence, without a runtime
pool-exhaustion reproduction. Preserve matching behavior. A deliberate
Native-port correction must define a pool-exhaustion result before request
stores or dispatch, with coverage for two busy slots and the wait-callback
contract. [Issue #1219](https://github.com/TheRealestNwah/sotc-decomp/issues/1219)
remains open for reachability and the eventual error-handling change.

## Subthread-status diagnostic class contract (#1240)

Original KERNEL `isysDumpSubThreadStatus` begins at XFF file offset
`0x1D030` (symbol offset `.text + 0x1CFF8`, size `0xB0`). It reads the
object's class byte at `object + 8`. Classes 6, 9, 11, 12, 13, 14, 22, 29
and 33 select the environment at `object + 0x20`; every other class selects
zero. The supported path establishes an environment location, not a check
that its saved stack pointer or the object itself is valid.

Both paths allocate two `0x100`-byte name buffers with alignment four.
At file offset `0x1D0AC`, the function unconditionally reads the selected
environment's first word as the saved stack pointer, before calling
`isysSearchModuleFuncNameByAddr`. The unsupported-class path therefore reads
through zero after those allocations. The function later frees both name
buffers. It has no unsupported-class diagnostic or early return.

A static reference audit of all 70,894 relocations in the three Original
Game modules, including their nonstandard relocated sections, found no
references to this function by name or by its section-relative address.
The function name also does not occur in their PROGBITS contents; its
KERNEL symbol is globally bound. This rules out an identified relocated
call or callback-table entry in those modules, but does not establish
runtime unreachability: dynamic symbol lookup, computed addresses and
external diagnostic invocation remain untraced. No caller-side class
filter has been established.

Preserve the exact matching implementation. Before implementing the Native
version, establish who may invoke this diagnostic and choose an explicit
result for unsupported classes before reading the environment. Test that
result alongside the nine supported classes and their saved-stack-pointer
contract. This is static binary and relocation evidence, without a runtime
reproduction. [Issue #1240](https://github.com/TheRealestNwah/sotc-decomp/issues/1240)
remains open for reachability and the deliberate port-stage behavior change.
