typedef int s128 __attribute__((mode(TI)));

extern int DldSysUndefSymbol;
extern char SH_StageDataDEFAULT[];
extern char rootPtn[];
extern s128 ZeroPoint;
extern s128 B_001885D0;
extern s128 B_001885E0;
extern int D_0017A2C4;
extern int D_0017A2C8;
extern void sheetMgrLoadSegmentIndex(void *, int, int *);
extern void scrRun(void);
extern char *gcGetStageData(int);
extern void func_0001BB48(char *, char *, int, int);

static inline char *DldGetTable(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    return off != 0 ? *(char **)((char *)h - off) : 0;
}

static inline char *DldGetPtr(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline void setUnitVector(s128 *v)
{
    __asm__ volatile("sqc2 vf0, 0(%0)\n" : : "r"(v) : "memory");
}

int commonDataLoad(int *out)
{
    float pos[4];
    float unit[4];
    int res;
    int ok;
    int st;
    int loaded;
    char *p;
    char *sh;
    char *ptn;

    loaded = 1;
    sh = SH_StageDataDEFAULT;
    res = -loaded;
    sheetMgrLoadSegmentIndex(sh, 0, &st);
    while ((unsigned int)(st - 0xDEAF) >= 2) {
        scrRun();
    }
    ok = DldGetTable((unsigned int *)(*(char **)(sh + 0x10) + 0x1C)) != 0;
    ptn = rootPtn;
    p = DldGetPtr((unsigned int *)(gcGetStageData(0) + 4));
    if (p != 0) {
        func_0001BB48(p, ptn, 0, 4);
    }
    *(s128 *)pos = ZeroPoint;
    setUnitVector((s128 *)unit);
    D_0017A2C4 = loaded;
    B_001885D0 = *(s128 *)pos;
    B_001885E0 = *(s128 *)unit;
    D_0017A2C8 = res;
    *out = res;
    return ok;
}
