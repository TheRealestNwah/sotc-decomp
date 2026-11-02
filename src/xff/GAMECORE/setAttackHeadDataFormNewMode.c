extern int DldSysUndefSymbol;
extern char *getSCRDataCtrlWork(void *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

void setAttackHeadDataFormNewMode(void *actor)
{
    char *dst = getSCRDataCtrlWork(actor) + 0x40C0;
    char *p = dldResolve(*(unsigned int **)(getSCRDataCtrlWork(actor) + 0x40A0));

    *(char **)dst = dldResolve((unsigned int *)(p + 0x10));
    *(int *)(dst + 0x10) = 0;
}

