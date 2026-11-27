typedef struct {
    int pad0[2];
    unsigned int slot[37];
} StageArea;

extern StageArea *D_0017A86C;
extern int D_0017A874;
extern int *DldSysUndefSymbol;
extern char SH_StageDataDEFAULT[];
extern char gcGlobalVar[];
extern char B_00188730[];
extern void func_0002D260(int);
extern int backStageCheckLoadSeg(unsigned int *);
extern void *createScriptObj(void (*)(int), int, void *, int, int, int, int, int);
extern int isysAddGroupWithLinkParam(void *, void *, int, int);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

typedef struct { int v[5]; } StageData;

static inline int stageIndex(StageData *e)
{
    char *t;
    StageData *b;

    if (e == 0)
        goto none;
    t = SH_StageDataDEFAULT != (char *)DldSysUndefSymbol ? SH_StageDataDEFAULT : 0;
    b = 0;
    if (t != 0)
        b = *(StageData **)(t + 0x10);
    return e - b;
none:
    return -1;
}

typedef struct { unsigned int ref; unsigned int flags; } SegRef;

/* Clears the loaded flag of the four segment references of part id in the current stage slot, then starts func_0002D260 and sets the flag for each one whose segment is loaded. */
static void func_00026E38(int id)
{
    int s = D_0017A874;
    int area = (id >> 5) & 0x3FF;
    StageArea *sl = D_0017A86C + area;
    char *part = dldResolve(&sl->slot[s]) + ((id << 27) >> 27) * 0x3C;
    SegRef *e = (SegRef *)(part + 0x14);
    char *g; void **gv; int z;
    int key = ((id >> 5) & 0x3FF) << 5;
    int i;

    /* Indexing e[i] through a per-iteration pointer, not walking e, sets the loop counter after the
       func_0002D260 and B_00188730 addresses like the Original. */
    for (i = 0; i < 4; i++) {
        SegRef *f = &e[i];
        int n = stageIndex((StageData *)dldResolve(&f->ref));
        f->flags &= ~1;
        if (n >= 0 && backStageCheckLoadSeg(&f->ref)) {
            area = 0; z = area; gv = (void **)((g = gcGlobalVar) + 0x308);
            isysAddGroupWithLinkParam(createScriptObj(func_0002D260, (n << 15) | key, *gv, 0x1000, z, 1, z, z), B_00188730, 0, z);
            f->flags |= 1;
        }
    }
}
