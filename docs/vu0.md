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
- The permuter parses files with `__asm__` statements; run it on the C around
  the asm when only scheduling or register choice differs.

## Worked examples

- `CheckEllipticalSphereVolumeShape` and `...WithInverseMatrix` (MANAGER): four
  VU0 runs (matrix apply, scale, squared length, normalize + dot) around
  scalar comparisons.
- `ExecScriptLwsOrientClass` (MANAGER): the distance-squared test is a
  seven-instruction run that `vu0_lift.py` produces verbatim.
