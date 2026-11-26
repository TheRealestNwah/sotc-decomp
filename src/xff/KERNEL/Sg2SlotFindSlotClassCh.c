#include "kernel/sg2slot.h"

int Sg2SlotFindSlotClassCh(int *out, int cls, int ch)
{
    int n = 0;
    int i;
    for (i = 0; i < 48; i++) {
        if ((B_000DE370[i].flags & 1) && B_000DE370[i].slotClass == cls && B_000DE370[i].ch == ch) {
            *out++ = i;
            n++;
        }
    }
    return n;
}
