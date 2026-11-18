# Classify handwritten assembly instead of matching it from C

Some Original functions were written in assembly by hand: gcc 2.96 could not have produced their shape. They become a third class beside Game code and SDK routines, Handwritten asm, and leave the matching totals just as SDK routines do.

A function is Handwritten asm only when its overall shape is one gcc 2.96 never emits: a missing or nonstandard prologue and epilogue, registers used against gcc's conventions, hand-laid `di`/`ei` or `sync.p` sequences, or delay slots filled in ways gcc never fills them. VU0 macro instructions alone don't qualify: the game uses them through inline `asm` inside ordinary C, so a function with gcc's shape and VU0 instructions stays Game code and is matched as C with inline asm.

Each classified function is listed in `config/handwritten_asm.txt` with its module, name, size, a signature and the evidence (names and evidence only, never the code). The functions stay in the build as the generated asm, which `ninja check` already verifies byte for byte, so no game code enters git. `tools/handwritten_asm.py` checks that each entry's size and signature (computed as for SDK routines) still name the Original's code. The Native port reimplements them in C or with intrinsics, as [ADR 0011](0011-replace-sdk-routines-not-hardware.md) does for SDK routines.

Matching every function from C, with inline asm for the hand-written ones, was rejected: it would put assembly into C files only to satisfy a counter, and it would hide which code needs a port-side replacement.

Amended 2026-11-17: extracting the functions into `build/` and splicing them back was dropped before it was built. The generated asm already reassembles to the Original, so a splice would compare the asm with itself; the signature check guards the list instead.
