#include "kernel/sg2slot.h"

void Sg2SlotSetPan(int s, int v)
{
    B_000DE370[s].pan = v;
    B_000DE370[s].flags |= 0x2000;
}
