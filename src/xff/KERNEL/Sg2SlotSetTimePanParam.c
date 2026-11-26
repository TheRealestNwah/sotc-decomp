#include "kernel/sg2slot.h"

void Sg2SlotSetTimePanParam(int s, float a, float b)
{
    B_000DE370[s].flags |= 0x40;
    B_000DE370[s].timePan.t8 = a;
    B_000DE370[s].timePan.t4 = b;
}
