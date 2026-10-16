extern int DldSysUndefSymbol;
extern char *getSCRDataCtrlWork(void *);
extern void *getPlayerColCont2(int);
extern int ColCont2_IsParentObj(void *, void *);
extern int ColCont2_IsColStatus(void *, int, int);

static inline int *dldTable(int *h)
{
    int off = *h & 0x3FFFF;

    return off != 0 ? *(int **)((char *)h - off) : 0;
}

static inline int *dldObj(int *h)
{
    int *t = dldTable(h);

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? (int *)t[4] : 0;
}

int SCRConditionPlayerParentColAttr(void *a, int b, int c, int d, int e, int f, int g, int *h)
{
    char *w = getSCRDataCtrlWork(a);
    int *o = dldObj(h);
    int ok;
    int r;

    if (o != 0 && o[2] != 0) {
        ok = 0;
        if (ColCont2_IsParentObj(getPlayerColCont2(*(int *)(w + 0x4078)), o))
            ok = 1;
    } else {
        ok = dldTable(h) == 0;
    }
    r = 0;
    if (ok)
        r = ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), e, f) != 0;
    return r;
}
