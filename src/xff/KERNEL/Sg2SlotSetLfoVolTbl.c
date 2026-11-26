#include "kernel/sg2slot.h"

void Sg2SlotSetLfoVolTbl(int s, int t)
{
    if (t != 0) {
        B_000DE370[s].lfoVolTbl = t;
        B_000DE370[s].lfoVol.cur = t;
        B_000DE370[s].lfoVol.end = t + 0x3C;
    }
}
