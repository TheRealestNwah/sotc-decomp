#ifdef NONMATCHING
/* 92 diffs, same length (140 words). Draft from the asm: looks up the stage-map chip for (x, y) (getChipNo as in DeleteNoUseLoadAreaGroupData), sums the widths of its rects, allocates total * 16 bytes, expands every rect into one (x + j, y) point per column, tracks min/max x and y, and calls func_0001FF70 with the point list and its bounds (args 9 and 10 on the stack are x and y) before freeing the buffer. Differences: the Original runs both rect loops with a separate down-counter ($t3, bnez) and loads the count and rect pointer into $t0/$t4, while ours reuses the count register with bgtz, which moves every later register. Permuter (12 workers, 25 min): best 3175, not close. */
typedef struct {
    short x;
    short y;
    short w;
    short h;
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

void func_00020DF8(int a0, int a1, int x, int y)
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
    r = g->rects + n;
    for (i = 0; i < n; i++) {
        r--;
        total += r->w;
    }
    buf = iosMallocAlign(rootPtn, total * 16, 0x10);
    r = g->rects + g->count;
    k = 0;
    for (i = 0; i < g->count; i++) {
        int j;

        r--;
        for (j = 0; j < r->w; j++) {
            buf[k].x = r->x + j;
            buf[k].y = r->y;
            k++;
        }
        if (r->x < minX)
            minX = r->x;
        if (r->x + r->w > maxX)
            maxX = r->x + r->w;
        if (r->y < minY)
            minY = r->y;
        if (r->y > maxY)
            maxY = r->y;
    }
    func_0001FF70(buf, total, minX, minY, maxX - minX + 1, maxY - minY + 1, a0, a1, x, y);
    iosFree(buf);
}
#endif
