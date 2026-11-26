#include "kernel/sg2slot.h"

extern int B_000DE360;

#ifdef NONMATCHING
/* Parked: 18 words differ (register allocation only after the q->d pointer form) */
void Sg2SlotBlock(int owner, int slot)
{
    int seq = B_000DE360++;
    Sg2Slot *q = &B_000DE370[slot];

    B_000DE370[slot].flags = 0;
    B_000DE370[slot].alloc = owner;
    B_000DE370[slot].x18 = -1;
    B_000DE370[slot].ch = -1;
    q->slotClass = -1;
    B_000DE370[slot].serial = seq;
}
#endif
