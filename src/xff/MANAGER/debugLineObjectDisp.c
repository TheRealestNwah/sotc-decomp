extern int *B_00148730[];
extern int iosDlGetWorkBufId(void);
extern void iosDlChainTailCurrent(int);

void debugLineObjectDisp(int i)
{
    int *t = B_00148730[i];
    t += iosDlGetWorkBufId();
    iosDlChainTailCurrent(t[2]);
}
