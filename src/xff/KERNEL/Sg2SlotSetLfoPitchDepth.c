#include "kernel/sg2slot.h"

void Sg2SlotSetLfoPitchDepth(int slot, int depth)
{
    int adjusted;
    if (depth != 0) {
        adjusted = depth;
        if (B_000DE370[slot].alloc == 1)
            adjusted = depth * 2;
    } else {
        adjusted = 0;
    }
    B_000DE370[slot].lfoPitchDepth = adjusted;
    if (depth != 0 && B_000DE370[slot].lfoPitchSpeed != 0)
        B_000DE370[slot].flags |= 0x400;
    else
        B_000DE370[slot].flags &= ~0x400;
}