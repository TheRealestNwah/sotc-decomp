#include "kernel/sg2slot.h"

void Sg2SlotSetMasTune(int s, int v)
{
    B_000DE370[s].mas.b = v;
    B_000DE370[s].flags |= 0x80;
}
