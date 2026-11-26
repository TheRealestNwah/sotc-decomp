#include "kernel/sg2slot.h"

void Sg2SlotSetLoop(int slot)
{
    B_000DE370[slot].flags |= 4;
}
