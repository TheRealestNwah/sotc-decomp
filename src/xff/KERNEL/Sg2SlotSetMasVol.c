#include "kernel/sg2slot.h"

void Sg2SlotSetMasVol(int s, int a, int b)
{
    B_000DE370[s].mas.cur = a;
    B_000DE370[s].mas.end = b;
    if (B_000DE370[s].x68 != -1 && B_000DE370[s].x6C != -1) {
        B_000DE370[s].flags |= 0x1000;
    }
}
