extern int B_000DE364[];

int Sg2SlotGetSlotClassIdx(void)
{
    int *p = B_000DE364;

    return (*p)++;
}
