typedef struct {
    int v[5];
} StageData;

extern int *DldSysUndefSymbol;
extern int SH_StageDataDEFAULT[];

typedef struct {
    int a;
    int b;
    unsigned int h[37];
} StageSlot;

typedef struct {
    unsigned int h;
    char pad[0x38];
} StageEnt;

extern StageSlot *D_0017A86C;
extern int D_0017A874;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

int getstagenumber(int id)
{
    int k = D_0017A874;
    StageSlot *sl = &D_0017A86C[(id >> 5) & 0x3FF];
    StageEnt *e = (StageEnt *)dldResolve(&sl->h[k]);
    StageData *p;

    if (e != 0) {
        p = (StageData *)dldResolve(&e[(int)((unsigned int)id << 27) >> 27].h);
        if (p != 0) {
            int *sh = DldSysUndefSymbol != SH_StageDataDEFAULT ? SH_StageDataDEFAULT : 0;
            StageData *base = 0;

            if (sh != 0)
                base = (StageData *)sh[4];
            return p - base;
        }
    }
    return -1;
}
