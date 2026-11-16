typedef struct {
    int pad0[2];
    unsigned int slot[37];
} StageArea;

extern StageArea *D_0017A86C;
extern int *DldSysUndefSymbol;
extern char SH_StageDataDEFAULT[];
extern void sheetMgrUnloadSegmentIndex(void *, int, int *);
extern void scrRun(void);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

/* Releases one stage part: clears its busy flags and drops the stage data segment reference, unloading it when the count reaches zero. */
static void func_00026CA8(int id)
{
    StageArea *sl = &D_0017A86C[(id >> 5) & 0x3FF];
    char *part = dldResolve(&sl->slot[0]) + ((id << 27) >> 27) * 0x3C;
    int idx;
    char *t;
    char *e;
    int status;

    *(int *)(part + 4) &= ~4;
    t = SH_StageDataDEFAULT != (char *)DldSysUndefSymbol ? SH_StageDataDEFAULT : 0;
    idx = (id >> 15) & 0x3FFF;
    e = t != 0 ? *(char **)(t + 0x10) + idx * 20 : 0;
    if (--*(unsigned short *)(e + 0x10) == 0) {
        sheetMgrUnloadSegmentIndex(SH_StageDataDEFAULT, idx, &status);
        while ((unsigned int)(status - 0xDEAF) >= 2)
            scrRun();
    }
    *(int *)(part + 4) &= ~3;
}
