extern void iosDlLockObj(unsigned char *);
extern void iosDlChainTailCurrent(int);

void meshDisp(unsigned char *p)
{
    int *m;
    iosDlLockObj(p);
    m = (int *)(p[8] != 0x23 ? 0 : p + 0x20);
    m += m[4];
    iosDlChainTailCurrent(*m);
}
