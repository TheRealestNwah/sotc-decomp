
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
extern void func_0002D198(int);
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

/* Starts func_0002D198 for each of the three stage data references of part id in the current stage slot. */
#ifdef NONMATCHING
/* Parked at 3 diffs: the Original sets the loop counter (daddu $s1, $zero, $zero) after the lui of the callback and B_00188730; ours sets it first. The two empty asms on n keep loop.c from hoisting the 0x3FFFF mask out of the loop. */
static void func_00027778(int id)
{
    int s = D_0017A874;
    int area = (id >> 5) & 0x3FF;
    StageArea *sl = D_0017A86C + area;
    char *part = dldResolve(&sl->slot[s]) + ((id << 27) >> 27) * 0x3C;
    unsigned int *h = (unsigned int *)(part + 0x34);
    char *g; void **gv; int z;
    int i;

    for (i = 0; i < 1; i++, h++) {
        int n = stageIndex((StageData *)dldResolve(h));
        __asm__("" : "+r"(n));
        __asm__("" : "+r"(n));
        if (n >= 0) {
            area = 0; z = area; gv = (void **)((g = gcGlobalVar) + 0x308);
            isysAddGroupWithLinkParam(createScriptObj(func_0002D198, n, *gv, 0x1000, z, 1, z, z), B_00188730, 0, z);
        }
    }
}
#endif
