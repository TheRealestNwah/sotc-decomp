/* Parked: 23 diffs, same size. Appends the path from the current point to the goal onto the way list: walks the parent chain from func_000FA7E0's node to count its depth (giving up past the group's max), then fills the free way slots back to front from the chain, and appends the goal position itself when the last way is the goal point. Remaining: the order of the way-entry stores in both inlined initWay copies, and the argument registers in the final goal append; a 40-minute permuter run found nothing better. */
#ifdef NONMATCHING
typedef unsigned int u128 __attribute__((mode(TI)));

typedef struct {
    short s0;
    short area;
    short idx;
    short parent;
    short link;
    short sA;
    float cost;
    void *next;
    void *prev;
} Node;

typedef struct {
    char pad0[0x94];
    int max;
} Grp;

typedef struct {
    u128 pos;
    int x10;
    short area;
    short link;
    short x18;
    short x1A;
    int idx;
} Way;

typedef struct {
    char pad0[0x70];
    u128 pos;
    int area;
    int idx;
    char pad88[0x100 - 0x88];
    Way way[20];
    unsigned int n;
    char pad384[0x418 - 0x384];
    int busy;
    char pad41C[0x3C50 - 0x41C];
    int grp;
} PathCtrl;

typedef struct { Node node[0x380]; Grp grp[1]; } PathWork;
extern PathWork B_001A03E8;
extern int func_000F56B8(PathCtrl *, int, int, int, int);
extern int func_000FA7E0(PathCtrl *, int, int);
extern u128 *getPointDataByAreaIdx(PathCtrl *, int, int);

static inline Way *getWay(PathCtrl *g, int k)
{
    return k < 20 ? &g->way[k] : 0;
}

static inline void initWay(Way *w, u128 *pos, int area, int idx, int link)
{
    w->x1A = 1;
    w->pos = *pos;
    w->area = area;
    w->idx = idx;
    w->link = link;
    w->x10 = 0;
    w->x18 = 0;
}

static inline int setWay(PathCtrl *g, int k, u128 *pos, int area, int idx, int link)
{
    if (k < 20) {
        initWay(&g->way[k], pos, area, idx, link);
        return 1;
    }
    return 0;
}

static int func_000F4F18(PathCtrl *g)
{
    Node *nodes = B_001A03E8.node;
    Grp *gr = &B_001A03E8.grp[g->grp];
    int no;
    int depth;
    int cnt;
    int rem;
    int k;
    int area;
    int idx;
    int link;
    u128 *p;
    Way *w;

    if (g->busy != 0)
        return 1;
    g->busy = 1;
    if (g->n == 0)
        return 0;
    if (g->n >= 20)
        return 0;
    if (func_000F56B8(g, g->way[g->n - 1].area, g->way[g->n - 1].idx, g->area, g->idx) == 0) {
        g->n = 0;
        return 0;
    }
    depth = 0;
    no = func_000FA7E0(g, g->area, g->idx);
    rem = 20 - g->n;
    while (no != nodes[no].parent) {
        depth++;
        no = nodes[no].parent;
        if (gr->max < depth)
            return 0;
    }
    area = g->area;
    cnt = depth;
    depth--;
    idx = g->idx;
    no = func_000FA7E0(g, area, idx);
    for (; depth >= 0; depth--) {
        if (depth < rem) {
            k = g->n + depth;
            link = nodes[no].link;
            p = getPointDataByAreaIdx(g, area, idx);
            if (p != 0 && setWay(g, k, p, area, idx, link))
                g->way[k].x10 = 1;
        }
        no = nodes[no].parent;
        area = nodes[no].area;
        idx = nodes[no].idx;
    }
    if (cnt > 0) {
        g->n += cnt;
        if (g->n >= 20)
            g->n = 20;
    }
    if (g->n < 19 && g->area == g->way[g->n - 1].area && g->idx == g->way[g->n - 1].idx) {
        u128 *src = &g->pos;

        initWay(getWay(g, g->n), src, g->area, g->idx, -1);
        g->n++;
    }
    return 1;
}
#endif
