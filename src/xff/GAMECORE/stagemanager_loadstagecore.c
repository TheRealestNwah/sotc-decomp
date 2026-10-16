typedef struct Ptn Ptn;
typedef struct {
    int v[4];
    unsigned short cnt;
    short pad;
} StageData;

extern int *DldSysUndefSymbol;
extern int SH_StageDataDEFAULT[];

static inline StageData *stageData(int n)
{
    int *sh = DldSysUndefSymbol != SH_StageDataDEFAULT ? SH_StageDataDEFAULT : 0;

    return sh != 0 ? (StageData *)sh[4] + n : 0;
}

extern void sheetMgrLoadSegmentIndex(void *, int, int *);
extern void sheetMgrNopSegmentIndex(int);
extern int initstage(Ptn *, int, int, int, int, int);
extern void scrRun(void);

void stagemanager_loadstagecore(Ptn *a, int n, int c, int d)
{
    StageData *s = stageData(n);
    int st;

    if (++s->cnt == 1) {
        sheetMgrLoadSegmentIndex(SH_StageDataDEFAULT, n, &st);
        sheetMgrNopSegmentIndex(0);
        while ((unsigned int)(st - 0xDEAF) >= 2)
            scrRun();
        if (st != 0xDEB0)
            initstage(a, n, c, -1, d, 0);
    }
}
