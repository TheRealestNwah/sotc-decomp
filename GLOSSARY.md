# sotc-decomp

A matching decompilation of Shadow of the Colossus (PS2, NTSC-U `SCUS-97472`): C that rebuilds the original game files byte-for-byte, as the base for a later native port.

## Language

### The disc

**Original**:
The bytes from the owner's own disc that every build is compared against.
_Avoid_: Baserom, retail, vanilla

**Loader**:
The boot executable `SCUS_974.72`, which loads the Game modules at runtime.
_Avoid_: Main ELF, main executable, boot ELF

**Game module**:
One of the three files `KERNEL.XFF`, `MANAGER.XFF` and `GAMECORE.XFF`, which hold almost all game code. "xff2" names their file format, not the files.
_Avoid_: Overlay, XFF (for the files themselves)

**Game code**:
Code written by the game's developers, as opposed to SDK routines. The part of the disc that gets decompiled.

**SDK routine**:
Code from Sony's SDK libraries linked into the Loader or a Game module. Identified by signature, never decompiled by hand.
_Avoid_: Library function (unqualified)

### Matching progress

**Matched function**:
A function, in the Loader or a Game module, whose C compiles to exactly the Original bytes and passes the full local check. The only state that counts as done.
_Avoid_: Recovered, decompiled, done (as status words)

**Parked attempt**:
A recorded attempt at a function that doesn't match yet, either as C kept behind `NONMATCHING` or as notes in a closed issue. It never counts toward progress.
_Avoid_: Partial match, WIP match

### Source structure

**Original source file**:
A `.c` file from the original developers' build, such as `sword.c`.

**Source group**:
A run of adjacent functions that relocation evidence ties to one Original source file. A lower bound: one Original source file can span several Source groups.
_Avoid_: TU, translation unit

**Original name**:
A function or variable name that survives in a Game module's symbol table, such as `nico_swordstart`. Never replaced.

**Placeholder name**:
An address-based label for something with no Original name, such as `func_000C5468`. May be replaced by a descriptive name once its purpose is known.
_Avoid_: Auto name, unnamed

### The port

**Native port**:
The future PC build of the game made from the matched source, which loads its assets from the owner's disc. Extra features such as new input methods or higher frame rates are port features, not part of the port itself.
_Avoid_: PC version, remaster, recomp
