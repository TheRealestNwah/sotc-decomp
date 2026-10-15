extern void iosDlChainTailCurrent(void *);

void iosSetDC(char *dc)
{
    iosDlChainTailCurrent(dc);
    if (*(int *)(dc + 0x170) & 1)
        iosDlChainTailCurrent(dc + 0xD0);
}
