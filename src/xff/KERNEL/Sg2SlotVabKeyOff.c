#include "kernel/sg2slot.h"

extern int B_000DE338[2];
extern int DIntr(void);
extern int EIntr(void);

void Sg2SlotVabKeyOff(int vab, int ch, int note)
{
    int intr = DIntr();
    int i;
    for (i = 0; i < 48; i++) {
        if ((B_000DE370[i].flags & 1) && B_000DE370[i].vab == vab && B_000DE370[i].ch == ch &&
            B_000DE370[i].note == note) {
            int low;
            B_000DE370[i].flags &= ~8;
            low = i < 24;
            B_000DE338[low ? 0 : 1] |= low ? 1 << i : 1 << (i - 24);
        }
    }
    if (intr)
        EIntr();
}
