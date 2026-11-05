extern int DldSysUndefSymbol;
extern void *GetSCRCharaAIWorkPtr(void *);
extern void *getPlayerColCont2(int);
extern int ColCont2_IsParentObj(void *, void *);
extern int ColCont2_IsColStatus(void *, long, long);
extern int execCondition(void *, void *);

static inline int *dldTable(int *h)
{
    int off = *h & 0x3FFFF;

    return off != 0 ? *(int **)((char *)h - off) : 0;
}

static inline int dldObj(int *h)
{
    int *t = dldTable(h);

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t[4] : 0;
}

static inline int dldCount(int *h)
{
    int *t = dldTable(h);

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t[3] : 0;
}

int getDPGroupID(void *a0, int *h)
{
    char *w = (char *)(((int)GetSCRCharaAIWorkPtr(a0) + 0x13) & ~0xF);
    int *t;
    char *e;
    int n;
    int i;

    e = (char *)dldObj(h);
    if (e != 0) {
    n = dldCount(h);
    for (i = 0; i < n; i++, e += 0x20) {
        int *h2 = (int *)(e + 0x18);
        int ok = 1;
        int par;
        char *o;

        t = dldTable(h2);
        if (t != 0 && t != (int *)DldSysUndefSymbol)
            o = (char *)t[4] + ((*(unsigned *)h2 >> 18) & 0xFFF) * ((int *)t[2])[3];
        else
            o = 0;
        if (*(long *)(e + 8) != -1)
            ok = ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), *(long *)(e + 8), *(long *)(e + 0x10));
        if (o != 0) {
            par = 0;
            if (ColCont2_IsParentObj(getPlayerColCont2(*(int *)(w + 0x4078)), o))
                par = 1;
        } else {
            par = dldTable(h2) == 0;
        }
        if (ok && par && execCondition(a0, e + 0x1C))
            return *(int *)e;
    }
    }
    return -1;
}
