#include "kernel/sg2slot.h"

void Sg2SlotSetPoltamentParam(int slot, int target, float step)
{
    Sg2Slot *s = &B_000DE370[slot];
    int flags = s->flags;

    if (!(flags & 0x200)) {
        int note = s->note;
        s->flags = flags | 0x200;
        s->poltaTime = 0;
        s->poltaStart = note;
        s->poltaCur = note;
    }
    s->poltaTarget = target;
    if (target < s->poltaCur) {
        step = -step;
    }
    s->poltaStep = step;
}
