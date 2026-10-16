extern int *DldSysUndefSymbol;
extern char *getSCRDataCtrlWork(void *);

static inline int dldData(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? t[4] : 0;
}

static inline int dldCount(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? t[3] : 0;
}

void createHintWork(void *actor, unsigned int *h)
{
    int *w = (int *)(getSCRDataCtrlWork(actor) + 0x40E0);

    w[0] = dldData(h);
    w[1] = dldCount(h);
    w[2] = 0;
    w[3] = 0;
}
