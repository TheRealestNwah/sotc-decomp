extern void iosDlChainTailCurrent(int);
extern int D_00040AE0;

void iosSetCurrentDC(void)
{
    iosDlChainTailCurrent(D_00040AE0);
}
