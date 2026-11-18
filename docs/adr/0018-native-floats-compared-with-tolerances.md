# Use native floats in the port and compare them with tolerances

The PS2's FPU isn't IEEE-754: it has no infinities, NaNs or denormals, it rounds toward zero and it saturates at ±max. The Native port compiles the same matched C with native IEEE floats, so float results can differ slightly from the Original and drift over many frames.

The port uses native floats by default. Reference run comparison ([ADR 0016](0016-verify-the-port-with-reference-runs.md)) is exact for integer and state fields and uses per-field tolerances for floats. Where a Reference run shows that drift changes gameplay (a different branch, state value or random roll), that spot gets targeted PS2 float emulation through helpers that the Matching build compiles out, with a regression run that covers it.

Emulating PS2 float semantics everywhere was rejected: it costs speed and readability across the whole source, and most drift doesn't matter. Pure tolerances with no emulation were rejected because some drift will cross a branch and change what the game does.
