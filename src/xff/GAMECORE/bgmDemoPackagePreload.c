extern int *DldSysUndefSymbol;
extern void demoNormalHook(void);
extern void func_000305D8(void);
extern void func_0002E220(char *, int, int, int, void (*)(void), void (*)(void), float);

static inline int *dldBase(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    return off != 0 ? *(int **)((char *)h - off) : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline int dldCount(unsigned int *h)
{
    int *t = dldBase(h);

    return (t != 0 && t != DldSysUndefSymbol) ? t[3] : 0;
}

int bgmDemoPackagePreload(char *pkg)
{
    int n = dldCount((unsigned int *)(pkg + 4));
    char *base = dldResolve((unsigned int *)(pkg + 4));
    int ok = 1;
    char *e;
    int i;

    e = base;
    for (i = 0; i < n; i++, e += 0x50) {
        if (*(int *)(e + 0x40) == 0) {
            ok = 0;
            func_0002E220(e, 5, 1, 0, demoNormalHook, func_000305D8, 100.0f);
        }
    }
    if (!ok)
        return 0;
    e = base;
    for (i = 0; i < n; i++, e += 0x50) {
        if (**(int **)(e + 0x40) != 2)
            return 0;
    }
    return 1;
}
