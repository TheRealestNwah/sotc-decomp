/* The float argument is declared before the seventh int argument here (same EABI registers as the
 * definition in scr_demo_manager.c): that gives the Original's f12-before-t2 move order in the tail call. */
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
extern void createScrEventDemoManager(int, int, int, int, int, int, float, int, int, int, int);

void SCRFuncStartEventDemo(int a0, int flag, int a2, long a3, int unused, unsigned int *ref1, unsigned int *ref2, int cond, int p6, float f0, float f1, float f2, float f3)
{

    register int lp __asm__("$22") = p6;
    if (flag != 0 && _gameFlagChk(flag) != 0)
        return;
    if (execCondition((void *)a0, cond) == 0)
        return;
    createScrEventDemoManager(a0, (int)dldBase(ref1), a2, (int)dldResolve(ref2), flag, (int)f1, f0, lp, (int)f2, (int)a3, (int)f3);
}
