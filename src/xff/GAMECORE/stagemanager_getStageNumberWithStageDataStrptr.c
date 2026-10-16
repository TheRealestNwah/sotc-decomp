typedef struct {
    int v[5];
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

int stagemanager_getStageNumberWithStageDataStrptr(unsigned int *h)
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
