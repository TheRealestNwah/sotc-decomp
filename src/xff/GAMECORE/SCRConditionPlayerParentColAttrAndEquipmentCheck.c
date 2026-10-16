extern int *DldSysUndefSymbol;
extern char *getSCRDataCtrlWork(void *);
extern int equipmentInvisibilityCloak(void);
extern void *getPlayerColCont2(int);
extern int ColCont2_IsParentObj(void *, void *);
extern int ColCont2_IsColStatus(void *, long, long);

static inline int *dldTable(unsigned int *h)
{
    int off = *h & 0x3FFFF;

    return off != 0 ? *(int **)((char *)h - off) : 0;
}

int SCRConditionPlayerParentColAttrAndEquipmentCheck(void *actor, int a1, int a2, int a3, long type, long val,
                                                     int a6, unsigned int *h)
{
    char *w;
    int *t;
    int *o;
    int ok;

    if (equipmentInvisibilityCloak())
        return 0;
    w = getSCRDataCtrlWork(actor);
    t = dldTable(h);
    o = (t != 0 && t != DldSysUndefSymbol) ? (int *)t[4] : 0;
    if (o != 0 && o[2] != 0) {
        ok = 0;
        if (ColCont2_IsParentObj(getPlayerColCont2(*(int *)(w + 0x4078)), o))
            ok = 1;
    } else {
        ok = dldTable(h) == 0;
    }
    if (!ok)
        return 0;
    return ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), type, val) != 0;
}
