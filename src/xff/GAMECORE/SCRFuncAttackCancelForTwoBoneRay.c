typedef int s128 __attribute__((mode(TI)));

extern int *DldSysUndefSymbol;
extern char gcGlobalVar[];
extern void func_00119338(void);
extern int _SCRGetCollisionTwoBoneRay(void *, int, int, void *, void *, void (*)(void), long *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);

static inline char *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

void SCRFuncAttackCancelForTwoBoneRay(void *actor, int a1, int a2, long p0, long p1, int a5, unsigned int *from, unsigned int *to,
                                      unsigned int *h)
{
    char work[0x40];
    char *e;
    long param[2] = { p0, p1 };


    if (_SCRGetCollisionTwoBoneRay(work, *(int *)(dldElem(from) + 8), *(int *)(dldElem(to) + 8), gcGlobalVar + 0x238, actor,
                                   func_00119338, param)) {
        e = dldElem(h);
        if (e != 0)
            CharaCtrlSetScriptCtrlStatus(actor, *(int *)(e + 4));
    }
}
