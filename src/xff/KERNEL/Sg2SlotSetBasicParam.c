#include "kernel/sg2slot.h"

extern int B_000DE360;
extern void Sg2SlotSetReverbOffBit(int hi, int bit);
extern void Sg2SlotSetNoiseOffBit(int hi, int bit);

void Sg2SlotSetBasicParam(int a, int i, int b, int c, int d, int e)
{
    int serial = B_000DE360;
    B_000DE360 = serial + 1;
    { register int *fp __asm__("$13") = &B_000DE370[i].flags; *fp = 1; }
    B_000DE370[i].alloc = a;
    B_000DE370[i].slotClass = b;
    B_000DE370[i].vab = c;
    B_000DE370[i].ch = d;
    B_000DE370[i].x18 = e;
    B_000DE370[i].serial = serial;
    Sg2SlotSetReverbOffBit(i >= 24, i < 24 ? 1 << i : 1 << (i - 24));
    Sg2SlotSetNoiseOffBit(i >= 24, i < 24 ? 1 << i : 1 << (i - 24));
}
