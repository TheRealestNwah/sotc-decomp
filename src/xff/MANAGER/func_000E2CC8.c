typedef struct Sheet {
    char pad0[0x44];
    unsigned int flags;
    char pad48[4];
    struct Sheet *loadNext;
    struct Sheet *initNext;
} Sheet;

typedef struct {
    char pad0[0x14];
    Sheet *sheet;
} SegDef;

typedef struct {
    SegDef *seg;
    int x4;
    unsigned int flags;
} SymEnt;

typedef struct {
    char pad0[0xC];
    int stride;
    int count;
    int *offs;
} ModInfo;

typedef struct {
    char pad0[8];
    ModInfo *info;
    char padC[4];
    char *base;
} Mod;

extern void *memset(void *, int, unsigned int);
extern void func_000E2A40(SegDef *, int, Sheet **);
extern Sheet *B_00151848;
extern int B_0015184C;
extern Sheet *B_00151850;
extern Sheet *B_00151854;
extern SegDef *DldSysUndefSymbol;
extern int sheetFsLanguageCode;

static inline int addLoad(Sheet **table, Sheet *s)
{
    int h = ((int)s >> 4) & 0x3FF;

    while (table[h] != 0) {
        if (table[h] == s)
            return 1;
        h = (h + 1) & 0x3FF;
    }
    table[h] = s;
    s->loadNext = B_00151848;
    B_00151848 = s;
    return 0;
}

static inline int addSeg(SegDef *seg, Sheet **table, Sheet **out)
{
    Sheet *s = seg->sheet;

    if ((s->flags >> 19) & 1)
        return -2;
    if (addLoad(table, s))
        return -1;
    *out = s;
    return 1;
}

static inline void addInit(Sheet *p)
{
    p->initNext = 0;
    if (B_00151850 != 0)
        B_00151854->initNext = p;
    else
        B_00151850 = p;
    B_00151854 = p;
}

static inline SymEnt *getEnt(int *p)
{
    return (SymEnt *)((char *)p - (*p & 0x3FFFF));
}

static inline SegDef *getSym(int *p)
{
    SegDef *s;

    if (*p & 0x3FFFF)
        s = getEnt(p)->seg;
    else
        s = 0;

    if (s == 0 || s == DldSysUndefSymbol)
        return 0;
    return s;
}

/* 7 diffs: table pointer copy is scheduled after the skip test instead of before it */
#ifdef NONMATCHING
static void func_000E2CC8(Mod *mod, int idx)
{
    Sheet *table[0x400];
    Sheet *first;
    ModInfo *info = mod->info;
    char *base = mod->base + info->stride * idx;
    int res[info->count];
    int i;

    B_0015184C = 0;
    B_00151848 = 0;
    B_00151850 = 0;
    B_00151854 = 0;
    memset(table, 0, sizeof(table));
    for (i = info->count - 1; i >= 0; i--) {
        int *p = (int *)(base + info->offs[i]);
        SegDef *s = getSym(p);
        SymEnt *e = getEnt(p);
        int r;

        if (s != 0) {
            int skip = 0;

            if (((e->flags >> 10) & 1) || (((e->flags >> 11) & 0xF) != 0 && ((e->flags >> 11) & 0xF) != sheetFsLanguageCode))
                skip = 1;
            if (skip)
                r = -3;
            else
                r = addSeg(s, table, &first);
            if (r == 1)
                addInit(first);
            res[i] = r;
        } else {
            res[i] = 0;
        }
    }
    for (i = info->count - 1; i >= 0; i--) {
        SegDef *s = getSym((int *)(base + info->offs[i]));

        if (s != 0 && res[i] == 1)
            func_000E2A40(s, 0, table);
    }
}
#endif
