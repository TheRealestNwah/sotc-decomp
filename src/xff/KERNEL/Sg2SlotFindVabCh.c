#include "kernel/sg2slot.h"

int Sg2SlotFindVabCh(int *out, int vab, int ch)
{
    int n = 0;
    int i;
    for (i = 0; i < 48; i++) {
        if ((B_000DE370[i].flags & 1) && B_000DE370[i].vab == vab && B_000DE370[i].ch == ch) {
            *out++ = i;
            n++;
        }
    }
    return n;
}
