extern int *DldSysUndefSymbol;
extern char rootPtn[];
extern void *iosMallocAlign(void *, int, int);

typedef union {
    struct { short x, y, w, h; int unk8; } s;
    int w[3];
} CellRect;

typedef struct {
    int unk0;
    int unk4;
    char *cells;
    char pad0C[0x3C];
    int gw;
    int gh;
} CellGrid;

typedef struct {
    int unk0;
    unsigned int sheet;
    int unk8;
    int unkC;
    int unk10;
} AreaEntry;

typedef struct {
    int unk0;
    unsigned short x;
    short pad6;
    unsigned short y;
    short padA;
    unsigned short w;
    short padE;
    unsigned short h;
    short pad12;
    int unk14;
} AreaSrc;

typedef struct AreaGroup {
    int unk0;
    char pad4[8];
    int unkC;
    int unk10;
    int count;
    CellRect *rects;
    int entry;
    struct AreaGroup *next;
} AreaGroup;

extern CellGrid D_0017A340;
extern AreaGroup *D_0017A310;
extern void func_000227C8(CellRect *, AreaGroup *);

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

static void func_00022980(AreaEntry *a)
{
    AreaSrc *src = (AreaSrc *)dldData(&a->sheet);
    AreaGroup *g = iosMallocAlign(rootPtn, 0x24, 0x10);
    AreaSrc *p;
    CellRect *r;
    int i;

    g->entry = (int)a;
    g->unkC = a->unkC;
    g->unk10 = a->unk10;
    *(int *)&g->next = *(int *)&D_0017A310;
    D_0017A310 = g;
    g->count = dldCount(&a->sheet);
    g->unk0 = a->unk8;
    g->rects = iosMallocAlign(rootPtn, g->count * 12, 0x10);
    p = src;
    r = g->rects;
    for (i = 0; i < g->count; i++) {
        r->s.x = p->x;
        r->s.y = D_0017A340.gh - p->y - p->h;
        r->s.w = p->w;
        r->s.h = p->h;
        r->s.unk8 = p->unk14;
        func_000227C8(r, g);
        p++;
        r++;
    }
}

