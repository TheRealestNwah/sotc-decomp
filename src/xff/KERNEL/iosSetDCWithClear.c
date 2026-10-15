extern void iosDlChainTailCurrent(char *);

void iosSetDCWithClear(char *dc, int clear)
{
    iosDlChainTailCurrent(dc);
    if ((*(int *)(dc + 0x170) & 1) && clear)
        iosDlChainTailCurrent(dc + 0xD0);
}
