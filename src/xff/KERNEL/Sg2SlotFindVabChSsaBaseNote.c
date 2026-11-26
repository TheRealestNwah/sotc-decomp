#include "kernel/sg2slot.h"

int Sg2SlotFindVabChSsaBaseNote(int *out, int x, int ch, int ssa, int note)
{
    int n = 0;
    int i;
    for (i = 0; i < 48; i++) {
        if ((B_000DE370[i].flags & 1) && B_000DE370[i].vab == x && B_000DE370[i].ch == ch && B_000DE370[i].ssa == ssa && B_000DE370[i].baseNote == note) {
            *out++ = i;
            n++;
        }
    }
    return n;
}
