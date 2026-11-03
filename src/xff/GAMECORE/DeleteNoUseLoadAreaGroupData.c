typedef struct Grp { int type; char pad[0x1C]; struct Grp *next; } Grp;
typedef struct { char pad0[0x10]; Grp *grp; char pad14[4]; } Cell;
typedef struct { char pad0[8]; Cell *cells; char padC[0x3C]; int nx; int ny; } StageMap;

extern StageMap D_0017A340;
extern Grp *D_0017A310;
extern void iosFree(void *);

static inline int cellIndex(int x, int y)
{
    if (x < 0 || x >= D_0017A340.nx || y < 0 || y >= D_0017A340.ny)
        return -1;
    return y * D_0017A340.nx + x;
}

static inline Grp *cellGroup(int x, int y)
{
    return D_0017A340.cells[cellIndex(x, y)].grp;
}

static inline int groupType(Grp *g)
{
    return g != 0 ? g->type : 0;
}

void DeleteNoUseLoadAreaGroupData(Grp *g)
{
    int x, y;

    for (y = 0; y < D_0017A340.ny; y++) {
        for (x = 0; x < D_0017A340.nx; x++) {
            if (groupType(cellGroup(x, y)) == 5 && cellGroup(x, y) == g)
                return;
        }
    }
    {
        Grp **h = &D_0017A310;
        Grp *p = *h;
        if (p == g) {
            *h = g->next;
            iosFree(g);
            g = 0;
            return;
        }
        while (p != 0) {
            if (p->next == g) {
                p->next = g->next;
                iosFree(g);
                g = 0;
                break;
            }
            p = p->next;
        }
    }
}
