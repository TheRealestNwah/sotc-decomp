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

extern CellGrid D_0017A340;

static inline int cellIdx(int x, int y)
{
    if (x >= 0 && x < D_0017A340.gw && y >= 0 && y < D_0017A340.gh)
        return y * D_0017A340.gw + x;
    return -1;
}

static void func_000227C8(CellRect *r, int val)
{
    int y, x;

    for (y = r->s.y; y < r->s.y + r->s.h; y++) {
        for (x = r->s.x; x < r->s.x + r->s.w; x++) {
            if (*(int *)(D_0017A340.cells + cellIdx(x, y) * 24 + 0x10) == 0) {
                *(int *)(D_0017A340.cells + cellIdx(x, y) * 24 + 0x10) = val;
                *(int *)(D_0017A340.cells + cellIdx(x, y) * 24 + 0x14) = r->s.unk8;
            }
        }
    }
}
