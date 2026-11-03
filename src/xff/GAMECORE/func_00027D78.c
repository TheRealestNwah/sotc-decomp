typedef struct {
    int pad0[2];
    unsigned int slot[37];
} StageArea;

typedef struct {
    int pad0[2];
    unsigned int slot[3];
    char pad14[0x28];
} StagePart;

extern StageArea *D_0017A86C;
extern int D_0017A874;
extern int *DldSysUndefSymbol;

static inline int *dldPtr(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    return off != 0 ? *(int **)((char *)h - off) : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static int func_00027D78(int id)
{
    int k = D_0017A874;
    StageArea *sl = &D_0017A86C[(id >> 5) & 0x3FF];
    StagePart *p = (StagePart *)dldResolve(&sl->slot[k]);
    int i;

    p += (id << 27) >> 27;
    for (i = 0; i < 3; i++) {
        if (dldPtr(&p->slot[i]) != 0 && dldPtr(&p->slot[i]) == DldSysUndefSymbol)
            return 0;
    }
    return 1;
}
