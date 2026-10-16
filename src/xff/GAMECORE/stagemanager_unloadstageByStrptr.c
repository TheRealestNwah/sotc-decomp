typedef struct {
    int v[4];
    unsigned short cnt;
    short pad;
} StageData;

extern int *DldSysUndefSymbol;
extern int SH_StageDataDEFAULT[];

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline int stageNum(unsigned int *h)
{
    StageData *p = (StageData *)dldResolve(h);

    if (p != 0) {
        int *sh = DldSysUndefSymbol != SH_StageDataDEFAULT ? SH_StageDataDEFAULT : 0;
        StageData *base = 0;

        if (sh != 0)
            base = (StageData *)sh[4];
        return p - base;
    }
    return -1;
}

static inline StageData *stageData(int n)
{
    int *sh = DldSysUndefSymbol != SH_StageDataDEFAULT ? SH_StageDataDEFAULT : 0;

    return sh != 0 ? (StageData *)sh[4] + n : 0;
}

extern char gcGlobalVar[];
extern void func_0002D680(void);
extern int createScriptObj(void (*)(void), int, int, int, int, int, int, int);

long stagemanager_unloadstageByStrptr(unsigned int *h)
{
    return createScriptObj(func_0002D680, stageNum(h), *(int *)(gcGlobalVar + 0x308), 0x1000, 0, 1, 0, 0);
}
