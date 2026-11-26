#include "kernel/sg2slot.h"

void Sg2SlotSetBasePan(int s, int v)
{
    B_000DE370[s].basePan = v;
    if (B_000DE370[s].x68 != -1 && B_000DE370[s].x6C != -1) {
        B_000DE370[s].flags |= 0x2000;
    }
}
