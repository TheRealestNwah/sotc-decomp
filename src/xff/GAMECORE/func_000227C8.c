typedef struct {
    short x, y, w, h;
    int unk8;
} CellRect;

typedef struct {
    int unk0;
    int unk4;
    char *cells;
    char pad0C[0x3C];
    int gw;
    int gh;
} CellGrid;

extern CellGrid D_0017A340;

static inline int cellIdx(int x, int y)
{
    if (x >= 0 && x < D_0017A340.gw && y >= 0 && y < D_0017A340.gh)
        return y * D_0017A340.gw + x;
    return -1;
}

#ifdef NONMATCHING /* 99 diffs, same word count: loop-invariant hoisting and inlined bounds checks */
static void func_000227C8(CellRect *r, int val)
{
    int y, x;

    for (y = r->y; y < r->y + r->h; y++) {
        for (x = r->x; x < r->x + r->w; x++) {
            int i = cellIdx(x, y);
            if (*(int *)(D_0017A340.cells + i * 24 + 0x10) == 0) {
                *(int *)(D_0017A340.cells + cellIdx(x, y) * 24 + 0x10) = val;
                *(int *)(D_0017A340.cells + cellIdx(x, y) * 24 + 0x14) = r->unk8;
            }
        }
    }
}
#endif
