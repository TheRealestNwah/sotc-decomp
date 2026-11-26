#include "kernel/sg2slot.h"

void Sg2SlotSetVolPhase(int s, int a, int b)
{
    B_000DE370[s].volPhase[0] = a;
    B_000DE370[s].volPhase[1] = b;
    B_000DE370[s].flags |= 0x100;
}
