#include "kernel/sg2slot.h"

void Sg2SlotSetDirectPitch(int s, int v)
{
    B_000DE370[s].directPitch = v;
    B_000DE370[s].flags |= 0x80;
}
