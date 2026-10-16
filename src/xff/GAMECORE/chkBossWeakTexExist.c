extern char gcGlobalVar[];
extern int *DldSysUndefSymbol;
extern void *SCRGetFirstObj(void *);

typedef struct {
    char pad0[0x28];
    long key;
    char pad30[0x14];
    unsigned int h;
    char pad48[0x10];
} TexEnt;

typedef struct {
    char pad0[0x10];
    TexEnt *ents;
    char pad14[0x40];
    int n;
} BossTex;

typedef struct {
    BossTex *tex;
} AIWork;

extern AIWork *GetSCRCharaAIWorkPtr(void *);

static inline int dldData(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? t[4] : 0;
}

int chkBossWeakTexExist(int n)
{
    void *p = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    BossTex *w;
    int i;

    if (p == 0)
        return 0;
    w = GetSCRCharaAIWorkPtr(p)->tex;
    for (i = 0; i < w->n; i++) {
        if (w->ents[i].key == (long)(n + 1) << 54)
            return dldData(&w->ents[i].h) != 0;
    }
    return 0;
}
