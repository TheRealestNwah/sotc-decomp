#include "kernel/sg2slot.h"

void Sg2SlotSetTimeVolParam(int s, float a, float b)
{
    B_000DE370[s].flags |= 0x20;
    B_000DE370[s].lfoVol.tC = a;
    B_000DE370[s].lfoVol.t8 = b;
}
