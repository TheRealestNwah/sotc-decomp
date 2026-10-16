extern int *DldSysUndefSymbol;
extern int *getSScriptWork(void *);
extern void *getPlayerColCont2(int);
extern int ColCont2_IsParentObj(void *, void *);
extern int ColCont2_IsEventColStatus(void *, long, long);

static inline int *dldTable(unsigned int *h)
{
    int off = *h & 0x3FFFF;

    return off != 0 ? *(int **)((char *)h - off) : 0;
}

int SCRSoundConditionPlayerParentColAttr(void *actor, int a1, int a2, int a3, long type, long val, int a6,
                                         unsigned int *h)
{
    int *w = getSScriptWork(actor);
    int *t = dldTable(h);
    void *o = (t != 0 && t != DldSysUndefSymbol) ? (void *)t[4] : 0;
    int ok;

    if (*w == 0)
        return 0;
    if (o != 0) {
        ok = 0;
        if (ColCont2_IsParentObj(getPlayerColCont2(*w), o))
            ok = 1;
    } else
        ok = dldTable(h) == 0;
    if (!ok)
        return 0;
    return ColCont2_IsEventColStatus(getPlayerColCont2(*w), type, val) != 0;
}
