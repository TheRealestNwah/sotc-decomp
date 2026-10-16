typedef int s128 __attribute__((mode(TI)));

extern int *DldSysUndefSymbol;
extern char *GetLayoutClass(void *);
extern void GetMotionNodeQuaternionPos(void *, void *, void *, int, int);
extern int CheckPositionInsideOfJudgeVolumeObject(void *, void *, void *, void *);

static inline int *dldData(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (int *)t[4] : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

int SCRFuncVolumeCheckByGameObjForSelfPos(void *actor, int a1, int a2, int a3, int a4, int a5, int a6,
                                          unsigned int *h, unsigned int *vh)
{
    char work[0x60];
    s128 pos;
    int *o = dldData(h);

    pos = **(s128 **)(GetLayoutClass(actor) + 0x134);
    if (o != 0) {
        void *vol = (void *)o[2];

        if (vol != 0 && dldResolve(vh) != 0 && CheckPositionInsideOfJudgeVolumeObject(work, vol, vh, &pos) != 0)
            return 1;
    }
    return 0;
}
