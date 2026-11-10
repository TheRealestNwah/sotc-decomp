#ifdef NONMATCHING
/* 9 diffs, same length (123 words): only the callee-saved assignment differs. Draft from the asm; sibling of SCRFuncStartEventDemoGameModeCheck (same createScrEventDemoManager call, float args through cvt.w.s, tail-called). The ninth parameter is the stack argument p6 (read at 0x80($sp)) that is passed straight on as the call argument. The Original holds the long a3 in $s5 and p6 in $s6; ours swaps them, which moves the sign-extend (dsll32) and the final register shuffle. Tried: int n = (int)a3 first, temporaries for the casts, a permuter run (12 workers, 15 min: best 140). */
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

extern int _gameFlagChk(int);
extern int execCondition(void *, int);
extern void createScrEventDemoManager(int, int, int, int, int, int, int, int, float, int, int);

void SCRFuncStartEventDemo(int a0, int flag, int a2, long a3, int unused, unsigned int *ref1, unsigned int *ref2, int cond, int p6, float f0, float f1, float f2, float f3)
{
    int n = (int)a3;

    if (flag != 0 && _gameFlagChk(flag) != 0)
        return;
    if (execCondition((void *)a0, cond) == 0)
        return;
    createScrEventDemoManager(a0, (int)dldBase(ref1), a2, (int)dldResolve(ref2), flag, (int)f1, p6, (int)f2, f0, n, (int)f3);
}
#endif
