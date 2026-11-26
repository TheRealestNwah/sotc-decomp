#include "kernel/sg2slot.h"

void Sg2SlotSetLfoVolSpeed(int slot, int val)
{
    float f;
    if (val != 0) {
        f = val;
        f = f / 6.35f;
    } else
        f = 0.0f;
    B_000DE370[slot].lfoVolSpeed = f;
    if (f != 0.0 && (float)B_000DE370[slot].lfoVolDepth != 0.0f)
        B_000DE370[slot].flags |= 0x800;
    else
        B_000DE370[slot].flags &= ~0x800;
}
