# Matching-work handoff

A snapshot for whoever picks up the matching work next, human or agent (Codex, Claude Code). It records where things stand, how to resume safely and the techniques that have closed gaps so far. Day-to-day notes stay in the local, gitignored `OVERNIGHT.md`.

Read `CLAUDE.md` (build, matching rules, decompiling workflow) and `docs/findings.md` first.

## Where things stand (2026-10-13)

- Loader ELF and all three XFF modules rebuild with matching code, data and relocations; `ninja check` covers all of it.
- **59 GAMECORE functions** come from matching C, all in `src/xff/GAMECORE/sword.c` (issue #18). Nothing is parked behind `NONMATCHING` any more.
- Left in sword.c: `func_000C3198`, `nico_swordstart`, `T_000C1D80`, `T_000C2620`, `DispWithSwordBlur`, `DispWithTorchBlur`.
- Byte-identical `.XFF` rebuild (#8) is still open: it needs the original assembler's relocation and symbol ordering.

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
| Pointer offset rebased onto another register (`geometry+0x50` instead of `reaction+0x60`) | cse2 knew `reaction == geometry - 0x10` and folded the offset. Reassigning the base after its last use (`geometry = (char *)reaction;`) removes that equivalence. | `func_000C2EB0` |
| Two independent loop-preheader or increment instructions swapped | Walk the array with a source-level pointer (`int *sheet = sheets;`) and order the increments (`sheet++, i++`). Hoisted invariants are emitted before giv inits, so the insn order decides scheduler ties. | `func_000C2EB0` |
| Float registers swapped in an expression | Hold the subexpressions in locals and try every declaration order. Local allocation follows declaration order. | `func_000C2318` |
| Original reloads a global in each branch, C keeps it in a register | Store through a pointer but read the global by name (`*p = (vol) + d;`). | `func_000C0EB0` (`STEP_VOL`) |
| Store order inside a struct differs | Write through a union view of the word (`((union { int i; float f; } *)&r->target)->f = 1.0f`), or store an int field as float (`*(float *)&r->active = 0.0f`) to group it with neighbouring float stores. | `func_000C2EB0`, `func_000C2D20` |
| Macro-scheduled code differs | Plain `{ }` scopes instead of `do { } while (0)`. | glow macros |

To see which compiler pass rewrites an expression, run `cc1` with `-da` under WSL (copy the input to `/tmp` first, as `tools/try_compilers.py` does) and compare the per-pass RTL dumps (`*.loop`, `*.cse2`, `*.combine`, `*.sched`) for the function.
