#include "kernel/sg2slot.h"

void Sg2SlotFree(int s)
{
    if (B_000DE370[s].alloc > 0) B_000DE370[s].alloc = 0;
}
