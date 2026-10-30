extern int DldSysUndefSymbol;
extern char *bossStatGetActiveBoss(void);
extern char *GetLayoutClass(void *);
extern int CheckPositionInsideOfJudgeVolumeObject(void *, void *, void *, void *);

static inline int *dldObj(int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? (int *)t[4] : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static int func_00075BA0(void *obj)
{
    char work[0x60];
    char *boss = bossStatGetActiveBoss();

    if (boss != 0 && dldObj((int *)(boss + 0xE0)) != 0) {
        int *vol = dldObj((int *)(boss + 0xE0));

        if (vol[2] != 0 && dldResolve((unsigned int *)(boss + 0xE4)) != 0)
            return CheckPositionInsideOfJudgeVolumeObject(work, (void *)vol[2], boss + 0xE4,
                                                          *(void **)(GetLayoutClass(obj) + 0x134));
    }
    return 0;
}
