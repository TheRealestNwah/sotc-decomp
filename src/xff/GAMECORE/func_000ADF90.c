extern int *DldSysUndefSymbol;
extern char *AI_GetCurMotionKind(void *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

static inline int dldCount(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? t[3] : 0;
}

static int func_000ADF90(char *o)
{
    unsigned int *list = (unsigned int *)dldResolve((unsigned int *)(*(char **)(o + 0x20C) + 0x18));
    char *cur = AI_GetCurMotionKind(*(void **)(o + 0x44));
    int n = 0;
    int i;

    if (list != 0)
        n = dldCount((unsigned int *)(*(char **)(o + 0x20C) + 0x18));
    for (i = 0; i < n; i++) {
        if (cur == dldResolve(&list[i]))
            return 0;
    }
    return 1;
}
