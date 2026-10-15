extern int DldSysUndefSymbol;
extern char *getSCRDataCtrlWork(void *);

void createAngryWork(void *a, int *h)
{
    int *w = (int *)(getSCRDataCtrlWork(a) + 0x40F4);
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    int g = (t != 0 && t != (int *)DldSysUndefSymbol) ? t[4] : 0;
    w[0] = g;
    w[1] = 0;
}
