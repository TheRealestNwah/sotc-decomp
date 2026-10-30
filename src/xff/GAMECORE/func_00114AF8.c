extern int DldSysUndefSymbol;
extern int execCondition(void *, unsigned int *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static int func_00114AF8(void *ctx, char *p)
{
    if (dldResolve((unsigned int *)(p + 0x28)) != 0 && dldResolve((unsigned int *)(p + 0x2C)) != 0 &&
        execCondition(ctx, (unsigned int *)(p + 0x2C)) != 0)
        return 1;
    return 0;
}
