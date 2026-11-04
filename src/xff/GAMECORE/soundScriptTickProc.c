extern int *DldSysUndefSymbol;
extern char *B_001888B8[5];
extern int B_001888D8;
extern int D_0017A934;
extern int D_0017A938;
extern void scriptNormalHook(void);
extern void func_00030578(void);
extern void func_0002E510(char *, int, int, int, int *, void *, void (*)(void), void (*)(void));
extern void func_0002E7A8(char *, int, int, int *, int *, void *, void (*)(void), void (*)(void));

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

void soundScriptTickProc(void *obj)
{
    int i;
    char *s;
    int n;
    int lvl;

    for (i = 0; i < 5; i++) {
        if (B_001888B8[i] == 0)
            continue;
        s = dldResolve((unsigned int *)(B_001888B8[i] + 4));
        lvl = 8;
        if (s == 0)
            continue;
        if (lvl < D_0017A938)
            continue;
        n = dldCount((unsigned int *)(B_001888B8[i] + 4));
        func_0002E510(s, n, lvl, B_001888D8, &D_0017A934, obj, scriptNormalHook, func_00030578);
        func_0002E7A8(s, n, lvl, &B_001888D8, &D_0017A934, obj, scriptNormalHook, func_00030578);
    }
}
