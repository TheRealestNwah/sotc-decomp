#include "kernel/sg2slot.h"

static inline void setTable(Sg2Slot *slot, int table)
{
    slot->lfoPitchTbl = table;
}

void Sg2SlotSetLfoPitchTbl(int slot, int table)
{
    if (table != 0) {
        setTable(&B_000DE370[slot], table);
        B_000DE370[slot].lfoPitchCur = table;
        B_000DE370[slot].lfoPitchEnd = table + 0x3C;
    }
}