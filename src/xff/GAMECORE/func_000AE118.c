extern int *DldSysUndefSymbol;
extern char *AI_GetCurControlMode(void *);

static inline int dldCount(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? t[3] : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

static int func_000AE118(char *obj)
{
    unsigned int *list = (unsigned int *)dldResolve((unsigned int *)(*(char **)(obj + 0x20C) + 0x1C));
    char *mode = AI_GetCurControlMode(*(void **)(obj + 0x44));
    int n = 0;
    int i;

    if (mode != 0)
        n = dldCount((unsigned int *)(*(char **)(obj + 0x20C) + 0x1C));
    for (i = 0; i < n; i++) {
        if (mode == dldResolve(&list[i]))
            return 0;
    }
    return 1;
}
