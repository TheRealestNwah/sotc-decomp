extern int DldSysUndefSymbol;
extern void fsEffectSetParamSheetSeg(unsigned int *reference);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static void func_000F29C0(char *p)
{
    fsEffectSetParamSheetSeg((unsigned int *)(dldResolve(*(unsigned int **)(*(char **)(p + 0x664) + 0x14)) + 0x190));
}
