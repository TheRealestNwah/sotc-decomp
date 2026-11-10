#ifdef NONMATCHING
/* 132 diffs, 4 words short (147 vs 151). Draft from the asm; dld helper from func_000AE758. Counts the attack-work timer down by the frame time (clamped at 0), bails unless the work block has a ref at +0x409C that resolves, an active attack list and no invisibility cloak, then registers a motion-shift callback entry (func_00114A48) for every 0x54-byte list entry whose ref at +0x24 resolves, and tail-calls func_00114170 once the timer is up. The Original computes the clamp through one zero register (mov.s $f1, $f0 after a swc1) and loads w[0x409C] into $a0 before the ref decode; ours reloads and splits the null test differently, so the whole function shifts by four words. */
extern int *DldSysUndefSymbol;


static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

extern char gcGlobalVar[];
extern char *getSCRDataCtrlWork(void *);
extern int equipmentInvisibilityCloak(void);
extern void SetCharacterObjMotionShiftCallBackEntry(void *, int, void *, int, void (*)(void), void *);
extern void func_00114A48(void);
extern void func_00114170(void *, void *);

void updateAttackWork2(void *obj, void *arg)
{
    char *w = getSCRDataCtrlWork(obj);
    char *aw = w + 0x40C0;
    float z = 0.0f;
    float t = *(float *)(aw + 0x14);
    char *p;
    int i;

    if (z < t) {
        float d = t - *(float *)(gcGlobalVar + 0x190);

        *(float *)(aw + 0x14) = d;
        if (!(d <= z))
            z = d;
        *(float *)(aw + 0x14) = z;
    }
    if (*(unsigned int **)(w + 0x409C) == 0)
        return;
    if (dldResolve(*(unsigned int **)(w + 0x409C)) == 0)
        return;
    if (*(int *)aw == 0)
        return;
    if (equipmentInvisibilityCloak() != 0)
        return;
    p = *(char **)aw;
    i = 0;
    while (dldResolve((unsigned int *)(p + 0x24)) != 0) {
        SetCharacterObjMotionShiftCallBackEntry(obj, i, dldResolve((unsigned int *)(p + 0x3C)), 0, func_00114A48, p);
        i++;
        p += 0x54;
    }
    if (0.0f < *(float *)(aw + 0x14))
        return;
    func_00114170(obj, arg);
}
#endif
