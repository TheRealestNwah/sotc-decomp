#include "kernel/sg2slot.h"

extern int B_000DE338[2];
extern int DIntr(void);
extern int EIntr(void);

void Sg2SlotSetDumperOff(int vab, int prog)
{
    int intr = DIntr();
    int i;

    for (i = 0; i < 48; i++) {
        if (B_000DE370[i].flags & 1) {
            if ((B_000DE370[i].flags & 8) && B_000DE370[i].slotClass == vab && B_000DE370[i].ch == prog) {
                int low;

                B_000DE370[i].flags &= ~8;
                low = i < 24;
                B_000DE338[low ? 0 : 1] |= low ? 1 << i : 1 << (i - 24);
            }
        }
    }
    if (intr) {
        EIntr();
    }
}
