/* Visibility-area builder for map chip (x, y) around centre (cx, cy): takes the draw range from D_0017A314/D_0017A318 (switching to the alternate range at D_0017A31C/D_0017A320 and updating the Z fog when D_0017A32C is set), then for group kinds 1..3 either fills the clamped square around the centre (chip +0x14 set) or the union of the group's spans, tracking the bounding box; any other kind fills the clamped square. Each cell goes into a 16-byte iosMallocAlign buffer passed to func_0001FF70 and freed. The range is copied through a temporary like the Original's unaligned struct copy. */
typedef struct { short x; short y; short w; short h; int pad; } Span;
typedef struct { int kind; int pad4[4]; int n; Span *list; } Grp;
typedef struct { int data[2]; int flags[2]; Grp *grp; int f14; } ChipRow;
typedef struct { char pad0[8]; ChipRow *chips; char padC[0x34]; float unit; char pad44[4]; int width; int height; } StageMap;
typedef struct { int x; int y; int pad[2]; } Pt;
typedef struct { int near; int far; } Range;

extern StageMap D_0017A340;
extern int D_0017A314;
extern int D_0017A318;
extern int D_0017A31C;
extern int D_0017A320;
extern int D_0017A32C;
extern int D_0017A3B4;
extern char rootPtn[];
extern void *iosMallocAlign(void *, int, int);
extern void iosFree(void *);
extern void setZFogFar(float);
extern void func_0001FF70(void *, int, int, int, int, int, int, int, int, int);

static inline int getChipNo(int x, int y)
{
    if (x < 0 || x >= D_0017A340.width || y < 0 || y >= D_0017A340.height)
        return -1;
    return y * D_0017A340.width + x;
}

static inline int getKind(int x, int y)
{
    Grp *g = D_0017A340.chips[getChipNo(x, y)].grp;

    return g != 0 ? g->kind : 0;
}

static void func_00020850(int cx, int cy, int x, int y)
{
    Range r;
    Range t;
    Grp *g;
    int minX = 9999;
    int maxX = -1;
    int minY = 9999;
    int maxY = -1;
    int total;
    int kind;
    int x0, x1, y0, y1;
    int i, j, k, n;
    Span *s;
    Pt *buf;

    t.near = D_0017A314;
    t.far = D_0017A314 + D_0017A318;
    r = t;
    g = D_0017A340.chips[getChipNo(x, y)].grp;
    if (D_0017A32C != 0) {
        D_0017A314 = D_0017A31C;
        D_0017A318 = D_0017A320;
        D_0017A3B4 = 0;
        r.near = D_0017A314;
        r.far = D_0017A314 + D_0017A318;
        setZFogFar(D_0017A340.unit * 0.5f + D_0017A340.unit * (float)(r.far - 1));
    }

    total = 0;
    kind = getKind(x, y);
    if (kind < 4) {
    if (kind > 0) {
        if (D_0017A340.chips[getChipNo(x, y)].f14 != 0) {
            y0 = cy - r.far;
            y1 = cy + r.far;
            x0 = cx - r.far;
            x1 = cx + r.far;
            if (x1 > D_0017A340.width - 1)
                x1 = D_0017A340.width - 1;
            if (y0 < 0)
                y0 = 0;
            if (y1 > D_0017A340.height - 1)
                y1 = D_0017A340.height - 1;
            if (x0 < 0)
                x0 = 0;
            minY = y0;
            minX = x0;
            maxX = x1;
            maxY = y1;
            total = (maxX - minX) * (maxY - minY);
            buf = iosMallocAlign(rootPtn, total * 16, 0x10);
            k = 0;
            for (j = minY; j < maxY; j++) {
                for (i = x0; i < x1; i++) {
                    buf[k].x = i;
                    buf[k].y = j;
                    k++;
                }
            }
        } else {
            s = g->list;
            for (i = 0; i < g->n; i++, s++) {
                x0 = s->x;
                y0 = s->y;
                x1 = s->x + s->w;
                y1 = s->y + s->h;
                if (x0 < minX)
                    minX = x0;
                if (y0 < minY)
                    minY = y0;
                if (maxX < x1)
                    maxX = x1;
                if (maxY < y1)
                    maxY = y1;
                total += (x1 - x0) * (y1 - y0);
            }
            buf = iosMallocAlign(rootPtn, total * 16, 0x10);
            k = 0;
            for (n = 0, s = g->list; n < g->n; n++, s++) {
                y0 = s->y;
                x0 = s->x;
                y1 = y0 + s->h;
                x1 = x0 + s->w;
                for (j = y0; j < y1; j++) {
                    for (i = x0; i < x1; i++) {
                        buf[k].x = i;
                        buf[k].y = j;
                        k++;
                    }
                }
            }
        }
        func_0001FF70(buf, total, minX, minY, maxX - minX + 1, maxY - minY + 1, cx, cy, x, y);
        iosFree(buf);
        return;
    }
    }
    {
        y0 = cy - r.far;
        x0 = cx - r.far;
        x1 = cx + r.far;
        y1 = cy + r.far;
        if (x1 > D_0017A340.width - 1)
            x1 = D_0017A340.width - 1;
        if (y1 > D_0017A340.height - 1)
            y1 = D_0017A340.height - 1;
        if (x0 < 0)
            x0 = 0;
        if (y0 < 0)
            y0 = 0;
        total = (x1 - x0) * (y1 - y0);
        buf = iosMallocAlign(rootPtn, total * 16, 0x10);
        k = 0;
        for (j = y0; j < y1; j++) {
            for (i = x0; i < x1; i++) {
                buf[k].x = i;
                buf[k].y = j;
                k++;
            }
        }
        func_0001FF70(buf, total, x0, y0, x1 - x0, y1 - y0, cx, cy, x, y);
        iosFree(buf);
    }
}
