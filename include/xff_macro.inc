# Assembly macros for the XFF modules. Same as macro.inc, but labels are local
# by default: the original objects reference local symbols as section+offset,
# and only symbols that are global in the original symbol table get .globl.
# .ent/.end are dropped: they only feed .mdebug/.pdr, which the originals leave empty.

# Evaluate this file only once in case it's included more than once
.ifndef _XFF_MACRO_INC_GUARD
.internal _XFF_MACRO_INC_GUARD
.set _XFF_MACRO_INC_GUARD, 1

# A function symbol.
.macro glabel label, visibility=local
    .\visibility "\label"
    .type "\label", @function
    "\label":
.endm

# The end of a function symbol.
.macro endlabel label
    .size "\label", . - "\label"
.endm

# An alternative entry to a function.
.macro alabel label, visibility=local
    .\visibility "\label"
    .type "\label", @function
    "\label":
.endm

# A label referenced by an error handler table.
.macro ehlabel label, visibility=local
    .\visibility "\label"
    "\label":
.endm


# A label referenced by a jumptable.
.macro jlabel label, visibility=local
    .\visibility "\label"
    "\label":
.endm


# A data symbol.
.macro dlabel label, visibility=local
    .\visibility "\label"
    .type "\label", @object
    "\label":
.endm

# End of a data symbol.
.macro enddlabel label
    .size "\label", . - "\label"
.endm


# Label to signal the symbol haven't been matched yet.
.macro nonmatching label, size=1
    .global "\label\().NON_MATCHING"
    .type "\label\().NON_MATCHING", @object
    .size "\label\().NON_MATCHING", \size
    "\label\().NON_MATCHING":
.endm

.endif
