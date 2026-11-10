extern int DldSysUndefSymbol;
extern char *getSCRDataCtrlWork(void *);
extern void *getPlayerColCont2(int);
extern int ColCont2_IsParentObj(void *, void *);
extern int ColCont2_IsColStatus(void *, long, long);

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

int SCRConditionKameBattleAreaEscape(void *a, int b, int c, int d, int e, int f, int g, int *h)
{
    char *w = getSCRDataCtrlWork(a);
    int *o = dldObj(h);
    int ok;

    if (o != 0) {
        ok = 0;
        if (ColCont2_IsParentObj(getPlayerColCont2(*(int *)(w + 0x4078)), o))
            ok = 1;
    } else {
        ok = dldTable(h) == 0;
    }
    if (ok) {
        if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0x1000000000000L) == 0
            && ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0x1800000000000L) == 0
            && ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0x2000000000000L) == 0
            && ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0x2800000000000L) == 0
            && ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0x3000000000000L) == 0
            && ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0x3800000000000L) == 0
            && ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0x4000000000000L) == 0
            && ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0x4800000000000L) == 0
            && ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0xA800000000000L) == 0
            && ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0xB000000000000L) == 0
            && ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x1E00000L, 0x200000L) == 0)
            return 1;
        return 0;
    }
    return 0;
}
