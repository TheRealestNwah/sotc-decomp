extern int *DldSysUndefSymbol;
extern char rootPtn[];
extern void *iosMallocAlign(void *, int, int);

typedef struct { int a, b; void *data[2]; void *obj; int pad14; } ChipRow;

typedef struct {
    char pad0[8];
    ChipRow *chips;
    char pad0C[0x3C];
    int gw;
    int gh;
} CellGrid;

typedef struct {
    int x;
    int y;
    int unk8;
    int unkC;
    unsigned int sheet;
} AreaEntry;

typedef struct {
    unsigned short x;
    short pad2;
    unsigned short y;
    short pad6;
    unsigned short z;
    short padA;
} PointSrc;

typedef union {
    struct { short x, y, z, pad; } s;
    int w[2];
} Point;

typedef struct AreaGroup {
    int type;
    int x;
    int y;
    int unkC;
    int unk10;
    int count;
    Point *points;
    int unk1C;
    struct AreaGroup *next;
} AreaGroup;

extern CellGrid D_0017A340;
extern AreaGroup *D_0017A310;

static inline int *dldSheet(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return t;
}

static inline char *dldData(unsigned int *h)
{
    int *t = dldSheet(h);

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] : 0;
}

static inline int dldCount(unsigned int *h)
{
    int *t = dldSheet(h);

    return (t != 0 && t != DldSysUndefSymbol) ? t[3] : 0;
}

static inline int getChipNo(int x, int y)
{
    if (x < 0 || x >= D_0017A340.gw || y < 0 || y >= D_0017A340.gh)
        return -1;
    return y * D_0017A340.gw + x;
}

static inline AreaGroup *newGroup(void)
{
    AreaGroup *g = iosMallocAlign(rootPtn, 0x24, 0x10);

    g->x = -1;
    g->y = -1;
    g->unkC = 0;
    g->unk10 = 0;
    g->unk1C = 0;
    *(int *)&g->next = *(int *)&D_0017A310;
    D_0017A310 = g;
    return g;
}

static void func_00022CD0(AreaEntry *a)
{
    PointSrc *src = (PointSrc *)dldData(&a->sheet);
    AreaGroup *g = newGroup();
    PointSrc *p;
    Point *r;
    int i;

    g->type = 5;
    g->x = a->x;
    g->y = D_0017A340.gh - a->y - 1;
    g->unkC = a->unk8;
    g->unk10 = a->unkC;
    g->count = dldCount(&a->sheet);
    g->points = iosMallocAlign(rootPtn, g->count * 8, 0x10);
    p = src;
    r = g->points;
    for (i = 0; i < g->count; i++) {
        r->s.x = p->x;
        r->s.y = D_0017A340.gh - p->y - 1;
        r->s.z = p->z;
        p++;
        r++;
    }
    D_0017A340.chips[getChipNo(a->x, D_0017A340.gh - a->y - 1)].obj = g;
}
