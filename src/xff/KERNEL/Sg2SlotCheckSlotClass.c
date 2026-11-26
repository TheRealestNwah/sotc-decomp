#include "kernel/sg2slot.h"

int Sg2SlotCheckSlotClass(int cls)
{
    int r = 0;
    int i;
    Sg2Slot *s = B_000DE370;
    for (i = 0; i < 48; i++, s++) {
        if ((s->flags & 1) && s->slotClass == cls) {
            r = 1;
            break;
        }
    }
    return r;
}
