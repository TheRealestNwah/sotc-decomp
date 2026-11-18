/* Same body as func_000272A8 with func_0002D388 as the callback; the empty asm on h keeps its addu ahead of the loop counter, as in the Original. */
typedef struct {
    unsigned int ref[2];
    int pad8[37];
} StageArea;

extern StageArea *D_0017A86C;
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

/* Starts func_0002D388 for both stage data references of area (id >> 5) & 0x3FF. */
static void func_00027418(int id)
{
    int area = (id >> 5) & 0x3FF;
    char *g;
    unsigned int *h = D_0017A86C[area].ref;
    void **gv;
    int z;
    int key = area << 5;
    int i;

    __asm__("" : "+r"(h));
    for (i = 1; i >= 0; i--, h++) {
        int n = stageIndex((StageData *)dldResolve(h));
        if (n >= 0) {
            area = 0;
            z = area;
            gv = (void **)((g = gcGlobalVar) + 0x308);
            isysAddGroupWithLinkParam(createScriptObj(func_0002D388, (n << 15) | key, *gv, 0x1000, z, 1, z, z),
                B_00188730, 0, z);
        }
    }
}
