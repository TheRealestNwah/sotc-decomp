extern void iosDlChainTailCurrent(int);
extern int D_00040AE4;

void iosSetRootDC(void)
{
    iosDlChainTailCurrent(D_00040AE4);
}
