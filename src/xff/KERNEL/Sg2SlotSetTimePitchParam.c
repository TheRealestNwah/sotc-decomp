#include "kernel/sg2slot.h"

void Sg2SlotSetTimePitchParam(int s, float a, float b)
{
    B_000DE370[s].flags |= 0x10;
    B_000DE370[s].timePitch.p1 = a;
    B_000DE370[s].timePitch.p0 = b;
}
