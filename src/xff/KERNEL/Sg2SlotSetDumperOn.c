#include "kernel/sg2slot.h"

void Sg2SlotSetDumperOn(int slot)
{
    B_000DE370[slot].flags |= 8;
}
