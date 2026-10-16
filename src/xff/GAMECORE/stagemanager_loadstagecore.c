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

extern void sheetMgrLoadSegmentIndex(void *, int, int *);
extern void sheetMgrNopSegmentIndex(int);
extern long initstage(int, int, int, int, int, int);
extern void scrRun(void);

long stagemanager_loadstagecore(int a, int n, int c, int d)
{
    StageData *s = stageData(n);
    int st;

    if (++s->cnt == 1) {
        sheetMgrLoadSegmentIndex(SH_StageDataDEFAULT, n, &st);
        sheetMgrNopSegmentIndex(0);
        while ((unsigned int)(st - 0xDEAF) >= 2)
            scrRun();
        if (st != 0xDEB0)
            return initstage(a, n, c, -1, d, 0);
    }
}
