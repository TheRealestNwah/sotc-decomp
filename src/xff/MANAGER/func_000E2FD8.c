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
    char pad0[0x38];
    SegDef *seg;
} StageDef;

extern StageDef *sheetFsGetStageTexSegTexSegDef(void);
extern void sheetFsSetStageTexSegTexSegDef(void *, int);
extern void *memset(void *, int, unsigned int);
extern void func_000E2A40(SegDef *, int, Sheet **);
extern void func_000E26D8(void);
extern Sheet *B_00151848;
extern int B_0015184C;
extern Sheet *B_00151850;
extern Sheet *B_00151854;

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

/* 14 diffs: register allocation around the segment table */
static void func_000E2FD8(void *arg)
{
    Sheet *table[0x400];
    Sheet *first;
    StageDef *def;
    int r;

    def = sheetFsGetStageTexSegTexSegDef();
    B_0015184C = 0;
    B_00151848 = 0;
    B_00151850 = 0;
    B_00151854 = 0;
    memset(table, 0, sizeof(table));
    r = addSeg(def->seg, table, &first);
    if (r == 1)
        addInit(first);
    if (r == 1)
        func_000E2A40(def->seg, 0, table);
    func_000E26D8();
    sheetFsSetStageTexSegTexSegDef(arg, 0);
}
