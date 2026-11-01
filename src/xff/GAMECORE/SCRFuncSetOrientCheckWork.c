extern int *DldSysUndefSymbol;
extern char *getSCRDataCtrlWork(void *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

void SCRFuncSetOrientCheckWork(void *actor, int a1, int a2, int a3, int t0, int t1, unsigned int *h2, int t3, unsigned int *h1)
{
    char *w = getSCRDataCtrlWork(actor);

    *(int *)(w + 0x40B8) = (int)dldResolve(h1);
    *(int *)(w + 0x40BC) = (int)dldResolve(h2);
}
