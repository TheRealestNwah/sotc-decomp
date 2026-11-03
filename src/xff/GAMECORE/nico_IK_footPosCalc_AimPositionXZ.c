typedef int s128 __attribute__((mode(TI)));

extern int *DldSysUndefSymbol;
extern void func_000396F0(s128 *, s128 *, void *);
extern void func_00038238(void *, int, void *, s128 *, s128 *, int);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline char *dldResolve2(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((*h >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

void nico_IK_footPosCalc_AimPositionXZ(char *ik)
{
    s128 v[2];
    s128 *dp;

    func_000396F0(v, dp = &v[1], ik);
    func_00038238(ik, 0, dldResolve2((unsigned int *)dldResolve(*(unsigned int **)(ik + 0x18))), v, dp, 1);
}
