# Count only Game code toward the finish line, then clean up the source before porting

Matching is finished when every Game code function, in the Loader and in all three Game modules, is a Matched function. SDK routines only need to be identified by signature: they're Sony's code, the Native port won't use them as they are, and hand-matching them would add hundreds of functions with no use. Between matching and the Native port sits a Source cleanup phase, during which the build keeps matching byte-for-byte: functions move into one C file per Original source file (or Source group, where no name survives), and shared headers with real struct types replace the per-file redeclarations. Port work starts once those shared headers exist, because a port written against ad-hoc padded structs would have to be rewritten. Replacing Placeholder names keeps going alongside the port and doesn't block it.

Amended 2026-11-17: Handwritten asm ([ADR 0017](0017-handwritten-asm-class.md)) is also left out of the finish line. Source cleanup starts per Source group as soon as every function in that group is matched, not after all matching ends; real types in shared headers make the remaining matching easier. Each cleanup PR covers one Source group, changes no matching, and keeps `ninja check` byte-identical. File and header layout:

- The C file takes the Original name where `tools/xff_tus.py` or strings give one (`sword.c`), otherwise a descriptive name for the group.
- `include/common.h` holds base types (`s32`, `f32`, vectors, matrices).
- `include/<module>/<group>.h` holds a group's own structs and prototypes.
- A struct moves to `include/<topic>.h` once two groups need it.
