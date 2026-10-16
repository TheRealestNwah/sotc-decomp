extern int DldSysUndefSymbol;
extern int _gameFlagChk(int);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

int backStageCheckLoadSeg(unsigned int *h)
{
    int f = *(int *)(dldResolve(h) + 0xC);

    if (f == 0)
        return 1;
    return !_gameFlagChk(f);
}
