extern int DldSysUndefSymbol;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline int *dldObj(int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? (int *)t[4] : 0;
}

extern void gStatGobjDispGflagSet(void *);

void SCRFuncSetGameFlagByGameObj(void *a, int b, int c, int d, int e, int *h)
{
    int *o = dldObj(h);

    if (o != 0 && o[2] != 0) {
        if (dldResolve((unsigned int *)(o + 4)) != 0)
            gStatGobjDispGflagSet(dldResolve((unsigned int *)(o + 4)));
    }
}
