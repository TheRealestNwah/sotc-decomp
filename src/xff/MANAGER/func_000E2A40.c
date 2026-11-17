typedef struct Sheet {
    char pad0[0x44];
    unsigned int flags;
    char pad48[4];
    struct Sheet *loadNext;
    struct Sheet *initNext;
} Sheet;

typedef struct SymEnt SymEnt;

typedef struct SegDef {
    char pad0[0x14];
    Sheet *sheet;
    int nsyms;
    SymEnt *syms;
} SegDef;

struct SymEnt {
    SegDef *seg;
    int x4;
    unsigned int flags;
};

extern Sheet *B_00151848;
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

static inline SegDef *getSym(SymEnt *e)
{
    SegDef *s = e->seg;

    if (s == 0 || s == DldSysUndefSymbol)
        return 0;
    return s;
}

/* 19 diffs: entry pointer and segment swap registers ($a3/$t0) */
#ifdef NONMATCHING
static void func_000E2A40(SegDef *seg, int depth, Sheet **table)
{
    Sheet *first;
    int res[seg->nsyms];
    int i;

    for (i = seg->nsyms - 1; i >= 0; i--) {
        SymEnt *e = &seg->syms[i];
        SegDef *s = getSym(e);
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
        }
    }
    for (i = seg->nsyms - 1; i >= 0; i--) {
        SegDef *s = getSym(&seg->syms[i]);

        if (s != 0 && res[i] == 1)
            func_000E2A40(s, depth + 1, table);
    }
}
#endif
