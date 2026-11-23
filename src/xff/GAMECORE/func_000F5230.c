/* Simplifies the start of a user path: while two or more ways remain, drops
 * the first way when a line test (func_000FA500 / func_000FA588) or the direct
 * reachability checks allow it, then resets the work position. */

typedef unsigned int u128 __attribute__((mode(TI)));

typedef union { short s; unsigned int i; } SU;

typedef struct {
    long long pos[2];
    int x10;
    short area;
    short link;
    short x18;
    short x1A;
    int idx;
} Way;

typedef struct {
    u128 x0;
    char pad10[0x30 - 0x10];
    u128 x30;
    int x40;
    char pad44[0x50 - 0x44];
    u128 x50;
    char pad60[0x70 - 0x60];
    u128 pos;
    char pad80[0x100 - 0x80];
    Way way[20];
    unsigned int n;
    int busy;
} PathCtrl;

extern int memcmp(const void *, const void *, unsigned int);
extern char *getLineDataByAreaIdx(PathCtrl *, int, int);
extern char *getPointDataByAreaIdx(PathCtrl *, int, int);
extern int func_000F7630(PathCtrl *);
extern int func_000FA500(PathCtrl *, Way *, Way *, char *, PathCtrl *);
extern int func_000FA588(PathCtrl *, Way *, Way *, char *, PathCtrl *);
extern int func_000FACE0(PathCtrl *, void *, void *);
extern int func_000FAD10(PathCtrl *, void *, void *);
extern int func_000FB160(PathCtrl *);

static inline Way *getWay(PathCtrl *g, unsigned int k)
{
    return k < g->n ? &g->way[k] : 0;
}

static inline unsigned short ptFlag(char *p)
{
    return *(unsigned short *)(p + 0x1E) & 1;
}

static inline void popWay(PathCtrl *g)
{
    unsigned int i;

    if (g->n != 0) {
        for (i = 0; i < g->n - 1; i++) {
            g->way[i] = g->way[i + 1];
            g->way[i].x18 = 0;
        }
        g->n = g->n - 1;
    }
}

static inline void resetPos(PathCtrl *g)
{
    g->x40 = -1;
    g->x50 = g->x30 = g->x0;
}

static void func_000F5230(PathCtrl *g, int flag)
{
    int cnt;
    Way *a;
    Way *b;
    char *la;
    char *lb;
    int r;
    int r2;

    if (g->busy == 0)
        return;
    if (g->n < 2)
        return;
    cnt = 0;
    if (getWay(g, 0)->x18 != 0)
        return;
    do {
        a = getWay(g, 0);
        b = getWay(g, 1);
        la = getLineDataByAreaIdx(g, a->link, a->idx);
        lb = getLineDataByAreaIdx(g, b->link, b->idx);
        if (a->x1A == 0)
            return;
        if (flag && g->n < 4) {
            char *pa = getPointDataByAreaIdx(g, a->area, a->idx);
            char *pb = getPointDataByAreaIdx(g, b->area, b->idx);

            if (pa != 0 && ptFlag(pa) && (pb == 0 || !ptFlag(pb)))
                return;
        }
        if (g->n == 2 && memcmp(&g->pos, &g->way[1], 12) == 0 && la != 0 && *(unsigned short *)(la + 0xE) > 0x80) {
            if (!func_000FA500(g, a, b, la, g))
                return;
            if (!func_000F7630(g))
                return;
            ((SU *)&b->link)->s = a->link;
            popWay(g);
            resetPos(g);
            return;
        } else if (la == 0 && lb != 0 && *(unsigned short *)(lb + 0xE) > 0x80) {
            if (!func_000FA588(g, a, b, lb, g))
                return;
            if (!func_000F7630(g))
                return;
            popWay(g);
            resetPos(g);
        } else {
            if (la != 0 && *(unsigned short *)(la + 0xE) > 0x80)
                return;
            if (lb != 0 && *(unsigned short *)(lb + 0xE) > 0x80)
                return;
            if (func_000FACE0(g, g, b)) {
                if (!func_000FB160(g))
                    return;
                r = func_000FAD10(g, g, getWay(g, 1));
                if (r)
                    return;
                r2 = func_000FACE0(g, g, getWay(g, r));
                if (r2)
                    return;
                if (!func_000FACE0(g, getWay(g, r2), getWay(g, 1)))
                    return;
            }
            if (!func_000F7630(g))
                return;
            popWay(g);
            resetPos(g);
            cnt++;
            if (g->n < 2 && cnt >= 4)
                return;
        }
    } while (g->n >= 2);
}
