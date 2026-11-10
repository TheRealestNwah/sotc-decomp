#ifdef NONMATCHING
/* 39 diffs, same length (117 words). Draft from the asm; the dld ref helpers are copied from func_000AE758. Skips unless the game is not cleared, not hard mode, not time attack, the optional flag is unset and execCondition passes, then resolves the two refs and calls createScrEventDemoManager (the float args go through cvt.w.s). The only real difference is the frame: the Original reserves 0x20 bytes of outgoing args (frame 0x80, saves at 0x20) while ours reserves 0x10 (frame 0x70); every later offset follows from that. The s0/s1 pair for flag/ref1 is also swapped. Permuter (12 workers, 15 min): best score 50 (from 95), no frame fix found. */
extern int *DldSysUndefSymbol;

static inline char *dldBase(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

extern int getGameClearCnt(void);
extern int getGameHardMode(void);
extern int gstatTimeAttackMode;
extern int _gameFlagChk(int);
extern int execCondition(void *, int);
extern void createScrEventDemoManager(int, int, int, int, int, int, int, int, float, int, int);

void SCRFuncStartEventDemoGameModeCheck(int a0, int flag, int a2, long a3, int unused, unsigned int *ref1, unsigned int *ref2, int cond, float f0, float f1, float f2, float f3)
{
    if (getGameClearCnt() > 0)
        return;
    if (getGameHardMode() != 0)
        return;
    if (gstatTimeAttackMode != 0)
        return;
    if (flag != 0 && _gameFlagChk(flag) != 0)
        return;
    if (execCondition((void *)a0, cond) == 0)
        return;
    createScrEventDemoManager(a0, (int)dldBase(ref1), a2, (int)dldResolve(ref2), flag, (int)f1, cond, (int)f2, f0, (int)a3, (int)f3);
}
#endif
