# Matching functions that use VU0 (COP2)

Many Game functions run vector math on VU0 in macro mode (`lqc2`, `sqc2`,
`vmul`, `vopmula`, `qmfc2`, ...). m2c prints each of those instructions as
`M2C_ERROR(unknown instruction ...)` and loses the data flow, so the draft is
useless around them. The Original compiler took the same instructions from
`__asm__` blocks, so Matched C keeps every run of consecutive VU0
instructions together as **one `__asm__ __volatile__` statement** and writes
the scalar code around it in plain C.

## Workflow

1. `python tools/m2c.py <fn> --module <MODULE>` for the scalar skeleton (calls,
   loops, branches). Ignore the `M2C_ERROR` lines.
2. `python tools/vu0_lift.py <fn> --module <MODULE>` prints one ready-made asm
   statement per VU0 run. Paste each one where m2c showed the `M2C_ERROR`
   lines and replace the placeholder variables:
   - `r_s1`, `r_v1`, ... stand for the Original register that holds the address
     (`$s1`, `$v1`). Bind them to the C pointer the register holds.
   - `&sp_buf` stands for a stack buffer the run reads or writes at `$sp`
     offsets. Use a local array/struct and make sure its offsets match.
   - `f_f1` is the float result of `qmfc2.ni $v0, ...; mtc1 $v0, $f1`.
   - The VU0 text itself is final; do not edit it.
3. Iterate with `tools/try_compilers.py` as usual.

## Conventions (what the lifter emits, verified against matched files)

- VU0 registers have no `$`: `vf5`, `vf7y`, `Q`, `ACC`.
- A GPR that `qmfc2`/`cfc2` writes and `mtc1` consumes is the fixed register
  written as a number (`$2` for `$v0`) and listed as a clobber.
- Inputs are `"r"`; every run declares `"memory"`.
- Keep a value that the Original computes *before* a run (for example
  `lim * lim`) in its own local before the asm statement; gcc otherwise
  schedules it after the statement and the instruction order differs.
- Pass addresses to the asm as C expressions (`"r"(*(float **)(c + 0x134))`)
  so gcc loads them exactly where the Original does.
- gcc 2.96 allocates stack objects in an order you cannot influence by
  declaration order alone; if a stack buffer lands at the wrong offset, change
  its size/alignment or use the permuter.

- If the Original fills a `bc1f`/`bc1t` delay slot with a load from the
  branch's fall-through block and keeps the result initialization
  (`v0 = 0`) before the compare, copy that value into a local *before* the
  `if` (`cone = shape[1];`). gcc then fills the slot with the load instead of
  the initialization. This fixed `CheckEllipticalSphereVolumeShape` and
  `CheckEllipticalSphereVolumeShapeWithInverseMatrix`.
- If argument-setup instructions (`mov.s $f12, ...`, `daddu $a1, ...`) come out in a different
  order than the Original, reorder the callee's *prototype* parameters (and the call) while keeping each
  argument in its register class: `f(int, float, float, void *)` and `f(int, void *, float, float)` emit
  the moves in different orders. Try all permutations (4 parameters = 24 builds). This matched
  `ExecScriptLwsOrientClass`.
- **Quad zero store: use an `sq $0` helper.** A plain `*(s128 *)p = 0` (or a union/`memset` form) emits `por $v0, $zero, $zero; sq $v0, 0($p)` instead of `sq $zero, 0($p)`. `static inline void zero(s128 *v) { __asm__ __volatile__("sq $0, 0(%0)" : : "r"(v) : "memory"); }` gives the Original store (`motrootdyn_startchainhang`, `charrootdyn_setLandingStatus` draft).
- **Swap which operand the `lqc2` text reads.** When the Original loads the two addresses in one order but into the opposite vector registers (`lqc2 $vf5, ($a0)` after `lw $v1, 0x134($v0)`), keep the asm operand order (it decides the load order) and swap the register numbers in the text: `lqc2 vf5, 0x0(%1)` / `lqc2 vf6, 0x0(%0)` (`func_000764B0`).
- **Put the short path in the `else` branch.** `if (x == 0) { call; return; } body` puts the short path first. The Original places it last, so write `if (x != 0) { body } else { call }` (`func_000764B0`).
- **Whole-function asm with C glue (`clipByMinMaxCube`):** a function that is VU0 runs separated by `cfc2`/`and`/`beqz` flag tests becomes one asm statement per run, `r &= t` after each `cfc2` output, and the next run nested in `if (r != 0)`. gcc 2.96 emits the `and` operands as `$v1, $v0`; a one-line `__asm__("and %0, %0, %1" : "+r"(r) : "r"(t))` gives the Original order. Use `"+r"` and `"=r"`/`"=f"` outputs, never a read of an asm result through an `"r"` input.
- The permuter parses files with `__asm__` statements; run it on the C around
  the asm when only scheduling or register choice differs.

## Worked examples

- `CheckEllipticalSphereVolumeShape` and `...WithInverseMatrix` (MANAGER): four
  VU0 runs (matrix apply, scale, squared length, normalize + dot) around
  scalar comparisons.
- `ExecScriptLwsOrientClass` (MANAGER): the distance-squared test is a
  seven-instruction run that `vu0_lift.py` produces verbatim.

- Float values handed to `qmtc2` (a scale in `vf6`): don't read them back with `*(int *)&f` or a union, which gcc 2.96 turns into a store/reload through the stack (func_000479F0: 125 -> 58 diffs). Move the bits in a separate asm output: `__asm__("mfc1 %0, %1" : "=r"(bits) : "f"(f));`, then pass `bits` as an `"r"` input to the VU0 statement. Float results read with `cfc2.ni`/`mtc1` use an `"=f"` output the same way.
- A 16-byte struct copy emits `ldl/ldr/sdl/sdr` unless the type is 8-byte aligned; use a union with a `long l[2]` view (or an aligned `s128`) to get `ld/sd` or `lq/sq` (bossStatStartDemo). A 12-byte `float[3]` struct copy gives the `ldl/ldr` + `lw` pair the Original uses for Vec3.
- Put the locals a function shares with VU0 asm in one struct (`struct { Vec a; Vec b; ... } L __attribute__((aligned(16)))`): it pins the frame layout, which gcc 2.96 otherwise decides by size (func_0005BB30, func_000C1BA8, func_00037A38).
- The `vrsqrt Q, vf0w, vf7x` form is not in the assembler's table: emit `.word 0x4BA703BD` and the following `vwaitq` / `cfc2.ni $2, $vi22` as in AI_CheckSightOn.
