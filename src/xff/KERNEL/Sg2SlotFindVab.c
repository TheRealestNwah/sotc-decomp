#include "kernel/sg2slot.h"

int Sg2SlotFindVab(int *out, int v)
{
    int n = 0;
    int i;
    for (i = 0; i < 48; i++) {
        if ((B_000DE370[i].flags & 1) && B_000DE370[i].vab == v) {
            *out++ = i;
            n++;
        }
    }
    return n;
}
