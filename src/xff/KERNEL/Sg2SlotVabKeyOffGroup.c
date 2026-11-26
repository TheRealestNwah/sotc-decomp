#include "kernel/sg2slot.h"

extern int B_000DE338[2];
extern int DIntr(void);
extern int EIntr(void);
extern int Sg2SlotSetAdsr(int, unsigned short, unsigned short);

void Sg2SlotVabKeyOffGroup(int vab, int group)
{
    int interrupt = DIntr();
    int i;
    for (i = 0; i < 48; i++) {
        if ((B_000DE370[i].flags & 1) && B_000DE370[i].vab == vab && B_000DE370[i].group == group) {
            int low;
            Sg2SlotSetAdsr(i, 0, 8);
            low = i < 24;
            B_000DE338[low ? 0 : 1] |= low ? 1 << i : 1 << (i - 24);
            B_000DE370[i].group = -1;
        }
    }
    if (interrupt)
        EIntr();
}
