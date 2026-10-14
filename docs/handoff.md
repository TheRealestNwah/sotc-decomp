# Matching-work handoff

A snapshot for whoever picks up the matching work next, human or agent (Codex, Claude Code). It records where things stand, how to resume safely and the techniques that have closed gaps so far. Day-to-day notes stay in the local, gitignored `OVERNIGHT.md`.

Read `CLAUDE.md` (build, matching rules, decompiling workflow) and `docs/findings.md` first.

## Where things stand (2026-10-13)

- Loader ELF and all three XFF modules rebuild with matching code, data and relocations; `ninja check` covers all of it.
- **1,539 functions** come from matching C: 891 GAMECORE, 487 MANAGER and 161 KERNEL. Of these, 60 are in `src/xff/GAMECORE/sword.c` (issue #18).
- The small-routine batch in issue #63 adds 172 GAMECORE routines with a 40-instruction candidate limit. Every retained object passed code, relocated-reference and data validation, followed by full module checks. Local experiment outputs remain under `build/auto40/GAMECORE/`.
- Issue #65 adds 49 KERNEL routines with the same candidate limit, excluding recognizable SDK and standard-library entries. All 49 passed code, data and relocation validation; 39 other candidates differed and 339 had no usable draft. Local outputs and validation results remain under `build/auto40/KERNEL/`.
- Issue #67 adds 91 MANAGER routines, also fully verified against original code, data and relocations. The pass checked 752 candidates: 91 matched, 118 differed and 543 had no usable draft. Local outputs and validation results remain under `build/auto40/MANAGER/`.
- Issue #73 checks the 41–80 instruction GAMECORE range and adds `Kite_SucceedKitePathWork`. Of 291 candidates, one matched, 49 differed and 241 had no usable draft. A conservative retry using byte-array declarations for address-only opaque globals added no matches (nine more usable drafts, all different). Local evidence remains under `build/auto80/GAMECORE/` and `build/auto80-retry/GAMECORE/`.
- Issue #75 recovers eight small GAMECORE routines from the earlier unusable drafts using byte-array declarations for address-only opaque globals. All eight passed original code, data and relocation validation. The retry checked 717 candidates: eight matched, 74 differed and 635 still had no usable draft. Local evidence remains under `build/auto40-addr/GAMECORE/`.
- Issue #76 recovers another 129 GAMECORE routines using opaque pointer types and external calls whose results are discarded. All 129 passed original code, data and relocation validation and the full build. The retry checked 635 candidates: 129 matched, 201 differed and 305 remained unresolved. Local evidence is under `build/auto40-prototypes/GAMECORE/`.
- The Windows splice command exceeded the process command-line limit at 740 GAMECORE objects containing 792 matching functions. Issue #78 / PR #79 fixes it with Ninja JSON response files; positional object arguments still work. Do not revert this fix when updating older parked branches.
- Issue #81 adds 190 MANAGER routines from 543 previously unusable drafts (190 matched, 149 differed and 204 remained unresolved). There are 186 new files; four case-distinct pointer getters share their existing value-getter files to avoid Windows filename collisions. Local evidence is under `build/auto40-prototypes/MANAGER/`; the final complete build log is `build/manager-prototypes-final-check.log`.
- Issue #83 adds 54 KERNEL routines from 339 previously unusable drafts (54 matched, 166 differed and 119 remained unresolved), retaining prior SDK/stdlib exclusions. All 54 passed original code, data and relocation validation and the full build. Local evidence is under `build/auto40-prototypes/KERNEL/`.
- Issue #85 fixes m2c's splitting of complete functions at interior plain-label twins such as `jtbl_00003A20`. The wrapper now removes redundant plain definitions and localizes both plain and `.Lxff` references. `GAMEUTIL_is_nearly_equal_zero3D` now produces one complete draft; older unresolved candidates may benefit from redrafting. Tests increased to 91.
- Issue #87 / PR #88 adds `calcFadeParam`, fully verified with the original compiler and the complete matching build. Reusing both normalized time and output-value locals preserves the original float registers. Main is at `763b094`; all 91 tests, Ruff and CI passed.
- Every remaining sword.c function has a near-match parked behind `NONMATCHING` in a draft PR:

| Function | Draft PR | Status |
| --- | --- | --- |
| `nico_swordstart` (sword thread) | #62 | +2 words: GCSE-hoisted stack addresses win callee-saved registers over two `%hi` parts and `origin` |
| `T_000C1D80`, `T_000C2620` (collision callbacks) | #53 | 5 words each: the shared ignore flag is allocated to v0 instead of v1 |
| `DispWithSwordBlur`, `DispWithTorchBlur` | #56 | 616 of 629 words: loop-invariant hoisting and constant sharing differ |
- Byte-identical `.XFF` rebuild (#8) is still open: it needs the original assembler's relocation and symbol ordering.

## Current checkpoint (2026-10-13)

Issue #117 adds `set_option_parameter_nico_sight_on`, fully verified. Restore the incoming yaw flag forwarded in a1 to the first setter; the pitch flag then occupies a2 as the original requires. The same missing-argument pattern can hide in caller drafts even when no explicit move passes the register. Evidence: `build/sight-options-final-check.log`.

Issue #115 adds `SCRFuncYamoriBDamageCheckInit`, fully verified. The recovered draft used a byte stride as an element count: `float_pointer -= 4` moved 16 bytes, while the original moved four. A one-element decrement restores the four contiguous -1.0f stores. Check typed pointer arithmetic against the original address increments. Evidence: `build/yamori-init-final-check.log`.

Issue #113 adds `SCRFuncSetNextRouteMaxAngle`, fully verified. Even the exact decimal representation of float32 0x3C8EFA35 compiled one bit low in GCC 2.96; `0.0174532925f` produces the correct constant. Exact-decimal normalization is a candidate strategy, not a guarantee: always check emitted bits. Evidence: `build/route-angle-final-check.log`.

Issue #111 retries 392 unmatched small FP candidates after the CVT decoder repair, retaining prior SDK/stdlib exclusions. Seven routines matched and passed per-object and full code/data/relocation checks: three GAMECORE and four MANAGER. Another 206 differed or failed compilation; 179 had no usable draft. Exact float32 decimal literals preserve recovered constant bits under GCC 2.96 truncation, and explicit mode(TI) types are supplied when needed. Evidence: `build/auto40-fp-retry/<MODULE>/validation.json` and `build/retry-fp-final-check.log`.

Issue #108 fixes raw `cvt.w.s` normalization in the m2c wrapper. The R5900 decoder considered the instructions valid but printed `.word`, so m2c silently omitted the conversions. A restricted CPU decode for the canonical single-precision encoding preserves the instructions; reserved encodings and double format remain raw. The real `GetStageContext` draft now uses integer casts/division rather than float-bit arithmetic. All 97 tests, Ruff and the full matching build pass; the verified function count is unchanged. Evidence: `build/stage-context-helper-fixed-m2c.log` and `build/m2c-cvt-fix-final-check.log`.

Issue #107 (`GetStageContext`) is next: the local `stage-context-helper` branch has no production source or PR yet. Resume it from updated main and use a typed context with separate 128-bit and float views of its center. The untyped draft still confuses the initial whole-vector copy with later float component writes.

Issue #105 adds `GetStageContextByPos`, `GetStageAreaNumberByPos` and `GetStageNumberByPos`, fully verified. Direct returns preserve the original return register and remove an extra move. Despite its name, `GetStageNumberByPos` reads the global position; no used position parameter was added. Evidence: `build/stage-by-pos-control.log` and `build/stage-context-queries-final-check.log`.

Issue #103 adds `GetStageName`, `GetStageAreaNumber` and `GetStageNumberNumber` using the restored local context. A volatile read of the area field preserves the original conditional load instead of if-conversion to `movn`. All three passed the original compiler and full code/data/relocation checks. Evidence: `build/stage-area-variants.log` and `build/stage-queries-final-check.log`.

Issue #101 adds `GetStageCenter`, fully verified. Restore its 0x40-byte local context, position pointer at offset 4 and 128-bit center at offset 0x30. `GetStageContext` explicitly returns 0/1 in the original; declaring it `int` instead of the discarded-result `void` placeholder preserves the original vector register. Evidence: `build/stage-context-variants.log` and `build/stage-center-final-check.log`.

Issue #99 recovers nine small routines with explicit signed/unsigned 128-bit scalar types (`mode(TI)`): five GAMECORE, three MANAGER and one KERNEL. `SetCurrentQuaternion` also needs a 128-bit destination array, matching the original 16-byte indexed store. All nine passed per-object code/data/relocation validation and the full matching build; 21 other candidates remained excluded. Evidence: `build/auto40-128/<MODULE>/validation.json` and `build/retry-128-final-check.log`.

Issue #97 adds `GAMEUTIL_constructor_move_angle`, fully verified with the original compiler and complete matching build. Precise float literals, local declaration order and selected volatile stores preserve the original constant loads, float registers and store sequence. Evidence: `build/angle-match-volatile-37.c` and `build/angle-constructor-final-check.log`.

Issue #93 adds 78 small GAMECORE script wrappers. Their drafts omitted the incoming character argument that the original forwards unchanged to `RequestCharacterMotionShiftFunc`. Restoring that argument matches all 78 with the original compiler; every separate object and the complete matching build passed code, data and relocation checks. Evidence: `build/script-wrappers-match.log`, `build/script-wrappers/validation.json` and `build/script-wrappers/final-check.log`.

Issue #89 adds `GAMEUTIL_reset_position_filter`, now verified with ee-gcc 2.96 and the full code, data and relocation checks. The source uses a union containing a three-element 128-bit word array and a struct view with two 128-bit fields followed by the count. This changes alias analysis to preserve the original copy/store order. Evidence remains in ignored `build/filter-union-11.c`, `build/filter-variants.log` and `build/filter-final-check.log`.

The documentation pause checkpoint (#90 / PR #91) merged with green CI at `c00838c`; work then resumed at the user's request. The three sword draft PRs above remain parked.

## Parked KERNEL display-list getters (#95 / draft PR #96)

The `kernel-display-list-getters` branch preserves four drafts behind `NONMATCHING` in `src/xff/KERNEL/iosDlState.c`. The original computes the 0x30-byte `B_00065018` state base separately before loading its fields; drafts fold the offsets into symbol references. Struct/union, storage, volatile, inline, return-width and control-flow probes did not match. The permuter was stopped after 4,137 iterations, with best score 60. `build/permuter/iosDlGetLayer/output-60-1/source.c` has two differing words: its load occupies the return delay slot instead of preceding it. None of these four functions is counted.

Local evidence: `build/dl-getters-*.log`, `build/permuter/iosDlGetLayer/`. Inspect existing processes before restarting a search; check useful candidates with the original compiler and full matching build. Update this old draft branch with current main before continuing. Its parked checkpoint passed the full build, all 91 tests, Ruff and CI, but remains a draft because the functions do not match.

## Resuming safely

- Start from an up-to-date `main` and a clean tree. Each unfinished function gets its own issue, branch and PR.
- An unfinished candidate can be committed behind `#ifdef NONMATCHING` (with an `#else` extern if other C calls it) and pushed as a draft PR. Never merge a draft until the function matches and `ninja check` passes.
- Permuter searches live in `build/permuter/<name>/` (gitignored). Before starting one, check for Python processes that are already running a search, so you don't run duplicates. A permuter score is a search metric, not proof of a match.
- Verify every candidate with `tools/try_compilers.py ... --only ee-gcc2.96 --flags "-O2 -G0"` and then `ninja check`.
- **The instruction diff masks relocations.** A function can show zero differing words and still reference the wrong symbol (for example `minAmbientWeak` instead of `minAmbientLineWeak`). The splice step in `ninja check` catches this, so a function isn't done until `ninja check` passes.

## Techniques that closed gaps

All of these are for Sony `ee-gcc` 2.96 at `-O2 -G0`.

| Symptom | What fixed it | Example |
| --- | --- | --- |
| Ignored helper result declared void changes the caller's vector register | Inspect the helper's return paths. Preserve a known scalar return declaration even when this caller discards it; `GetStageContext` explicitly returns 0/1. | `GetStageCenter` (#101) |
| Tail-call wrapper uses the wrong argument register and loses its stack frame | Recover the incoming argument that is forwarded unchanged, even when the draft omits it. Passing the character argument before the callback address preserves the original a0/a1 assignments and stack instructions. | `SCRArrowLoopEnd` and 77 related wrappers (#93) |
| 128-bit copies and an integer count store are reordered | Use a union view containing both a word array and the field struct to preserve the original alias relationships and instruction order. | `GAMEUTIL_reset_position_filter` (#89) |
| Float registers rotate while the instruction sequence already matches | Normalize the existing time local in place and accumulate into the existing value local. Replacing these updates with fresh expression results changed register allocation. | `calcFadeParam` (#87) |
| Function names differ only by letter case and collide as Windows filenames | Keep adjacent pointer/value getter pairs in one C file, preserving the case-sensitive function names and original order. | `getColLightDebugSts` / `GetColLightDebugSts`, `getDebPcWin*` / `GetDebPcWin*` (#81) |
| Drafts contain unknown pointed-to types or unknown external scalar results | Use `void *` for opaque pointers. A call whose result is discarded can use a `void` return declaration; do this only when every recovered use discards it. Keep other unknown scalar types unresolved and finish with full code/data/relocation validation. | small GAMECORE pass (#76) |
| Separate early returns merge into the wrong branch layout | Send both comparison arms explicitly to shared return labels. This preserves the original shared blocks and branch direction. | `GAMEUTIL_is_nearly_equal_zero` (#69), `GAMEUTIL_is_nearly_equal_zero3D` (#71) |
| Constant integer argument scheduled before a live float argument instead of in the call delay slot | Put the integer flag after the float arguments in the emitter declaration, definition and calls. The EE ABI keeps the same integer and float register assignments; source parameter order changes scheduling. | `func_000C3198` (#50) |
| Pointer offset rebased onto another register (`geometry+0x50` instead of `reaction+0x60`) | cse2 knew `reaction == geometry - 0x10` and folded the offset. Reassigning the base after its last use (`geometry = (char *)reaction;`) removes that equivalence. | `func_000C2EB0` |
| Two independent loop-preheader or increment instructions swapped | Walk the array with a source-level pointer (`int *sheet = sheets;`) and order the increments (`sheet++, i++`). Hoisted invariants are emitted before giv inits, so the insn order decides scheduler ties. | `func_000C2EB0` |
| Float registers swapped in an expression | Hold the subexpressions in locals and try every declaration order. Local allocation follows declaration order. | `func_000C2318` |
| Original reloads a global in each branch, C keeps it in a register | Store through a pointer but read the global by name (`*p = (vol) + d;`). | `func_000C0EB0` (`STEP_VOL`) |
| Store order inside a struct differs | Write through a union view of the word (`((union { int i; float f; } *)&r->target)->f = 1.0f`), or store an int field as float (`*(float *)&r->active = 0.0f`) to group it with neighbouring float stores. | `func_000C2EB0`, `func_000C2D20` |
| Macro-scheduled code differs | Plain `{ }` scopes instead of `do { } while (0)`. | glow macros |
| Branchy 0/1 flag where C gives store-flag (`sltu`) or `movz` code | Use one condition whose `x = 1`/`x = 0` blocks are shared by both arms (`if (hard ? !(a & B) : (a & B) != 0) return 1; return 0;`). Separate if/else arms get converted by the jump or if-conversion passes. | `isIgnoredSurface` (#53) |
| Float loads reordered above a 128-bit `lq/sq` copy | A `*(u_long128 *)` copy doesn't alias `float` under strict aliasing. Copy through a union of `u_long128` and a float struct. | `nico_swordstart` (#50) |
| Constants sit in callee-saved FP registers from the top of a block | The original holds them in locals initialized there (`float z0 = 0.05f;`). | blur trail (#56) |
| Unused `static inline` functions | gcc 2.96 still emits their string literals into `.rodata`, so unused helpers can be needed for `.rodata` to line up. | `getWeakIndexWeak` (#53) |

Register-allocation leftovers are the hardest residue. Our reading of gcc 2.96's global allocator (unconfirmed): it first tries registers already in use that no *conflicting* allocno prefers, and preferences of allocnos that cross calls are pruned.

To see which compiler pass rewrites an expression, run `cc1` with `-da` under WSL (copy the input to `/tmp` first, as `tools/try_compilers.py` does) and compare the per-pass RTL dumps (`*.loop`, `*.cse2`, `*.combine`, `*.sched`) for the function.
