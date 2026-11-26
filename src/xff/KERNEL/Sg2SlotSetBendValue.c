#include "kernel/sg2slot.h"

void Sg2SlotSetBendValue(int s, int v)
{
    B_000DE370[s].bend = v;
    B_000DE370[s].flags |= 0x80;
}
