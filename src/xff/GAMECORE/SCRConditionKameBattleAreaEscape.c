#ifdef NONMATCHING
/* 19 diffs, 2 words short (161 vs 163), all stemming from one place. Draft from the asm; sibling of SCRConditionPlayerParentColAttr (same dld ref decoding and parent-object test), followed by eleven ColCont2_IsColStatus checks on the player collision controller (bail with 0 if any of them is set), then success. The Original ends with `bnel v0, zero, end; daddu v0, zero, zero; addiu v0, zero, 1` for the last check; gcc folds ours into `sltiu v0, v0, 1` instead (two words fewer), whichever way the final test is written (== 0 return 1, else, temp var, r = 1 / r = 0). Permuter (12 workers, 15 min): 400 -> 200 with a cosmetic change only. */
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
        if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0x1000000000000L) != 0)
            return 0;
        if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0x1800000000000L) != 0)
            return 0;
        if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0x2000000000000L) != 0)
            return 0;
        if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0x2800000000000L) != 0)
            return 0;
        if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0x3000000000000L) != 0)
            return 0;
        if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0x3800000000000L) != 0)
            return 0;
        if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0x4000000000000L) != 0)
            return 0;
        if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0x4800000000000L) != 0)
            return 0;
        if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0xA800000000000L) != 0)
            return 0;
        if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x3F800000000000L, 0xB000000000000L) != 0)
            return 0;
        if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), 0x1E00000L, 0x200000L) != 0)
            return 0;
        return 1;
    }
    return 0;
}
#endif
