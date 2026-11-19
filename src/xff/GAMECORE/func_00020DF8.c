typedef union {
    struct { short x, y, w, h; } s;
    int i[2];
} Rect;

typedef struct {
    char pad0[0x14];
    int count;
    Rect *rects;
} Grp;

typedef struct {
    char pad0[0x10];
    Grp *grp;
    char pad14[4];
} ChipRow;

typedef struct {
    char pad0[8];
    ChipRow *chips;
    char padC[0x3C];
    int width;
    int height;
} StageMap;

typedef struct {
    int x;
    int y;
    int pad[2];
} Pt;

extern StageMap D_0017A340;
extern char rootPtn[];
extern void *iosMallocAlign(void *, int, int);
extern void iosFree(void *);
extern void func_0001FF70(void *, int, int, int, int, int, int, int, int, int);

static inline int getChipNo(int x, int y)
{
    if (x < 0 || x >= D_0017A340.width || y < 0 || y >= D_0017A340.height)
        return -1;
    return y * D_0017A340.width + x;
}

static void func_00020DF8(int a0, int a1, int x, int y)
{
    Grp *g = D_0017A340.chips[getChipNo(x, y)].grp;
    int minX = 9999;
    int maxX = -1;
    int minY = 9999;
    int maxY = -1;
    int total = 0;
    int n;
    int i;
    int k;
    Rect *r;
    Pt *buf;

    n = g->count;
    r = g->rects + n - 1;
    for (i = 0; i < n; i++) {
        total += r->s.w;
        r--;
    }
    buf = iosMallocAlign(rootPtn, total * 16, 0x10);
    r = g->rects + g->count - 1;
    k = 0;
    for (i = 0; i < g->count; i++, r--) {
        int j;

        for (j = 0; j < r->s.w; j++) {
            buf[k].x = r->s.x + j;
            buf[k].y = r->s.y;
            k++;
        }
        if (r->s.x < minX)
            minX = r->s.x;
        if (r->s.x + r->s.w > maxX)
            maxX = r->s.x + r->s.w;
        if (r->s.y < minY)
            minY = r->s.y;
        if (r->s.y > maxY)
            maxY = r->s.y;
    }
    func_0001FF70(buf, total, minX, minY, maxX - minX + 1, maxY - minY + 1, a0, a1, x, y);
    iosFree(buf);
}

