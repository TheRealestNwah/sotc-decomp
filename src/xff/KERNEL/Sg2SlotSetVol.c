#include "kernel/sg2slot.h"

void Sg2SlotSetVol(int s, int v)
{
    B_000DE370[s].mix.vol = v;
    B_000DE370[s].flags |= 0x1000;
}
