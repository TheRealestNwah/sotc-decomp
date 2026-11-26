#include "kernel/sg2slot.h"

void Sg2SlotSetMute(int s, int on)
{
    if (on) {
        B_000DE370[s].flags |= 0x8000;
    } else {
        B_000DE370[s].flags &= ~0x8000;
    }
    B_000DE370[s].flags |= 0x1000;
}
