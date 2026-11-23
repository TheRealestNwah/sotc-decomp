/* Parked: 5 diffs, same size. Remaining: the Original bases the segment loop pointer at part + 0x10 (ref at +4, flags at +8); gcc bases it at the flags word (part + 0x18). Same family as func_00027B70. */
#ifdef NONMATCHING
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
extern void func_0002D388(int);
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
typedef struct { char pad[0x14]; SegRef seg[4]; char pad2[0x3C - 0x34]; } Part;

/* Clears the loaded flag of the four segment references of part id, starting func_0002D388 for each that had it set and resolves to stage data. */
static void func_00027070(int id)
{
    int s = D_0017A874;
    int area = (id >> 5) & 0x3FF;
    StageArea *sl = D_0017A86C + area;
    Part *part = (Part *)dldResolve(&sl->slot[s]) + ((id << 27) >> 27);
    char *g; void **gv; int z;
    int key = ((id >> 5) & 0x3FF) << 5;
    int i;

    for (i = 0; i < 4; i++) {
        int n = stageIndex((StageData *)dldResolve(&part->seg[i].ref));
        if (n >= 0 && (part->seg[i].flags & 1)) {
            area = 0; z = area; gv = (void **)((g = gcGlobalVar) + 0x308);
            isysAddGroupWithLinkParam(createScriptObj(func_0002D388, (n << 15) | key, *gv, 0x1000, z, 1, z, z), B_00188730, 0, z);
        }
        part->seg[i].flags &= ~1;
    }
}
#endif
