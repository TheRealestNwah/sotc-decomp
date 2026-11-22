typedef struct Entry {
    char p0[8];
    unsigned int handle;
    int once;
    float limit;
    char p14[0x2C];
    int busy;
    unsigned int flags;
    char p48[8];
} Entry;

typedef struct Play {
    int state;
    int prio;
    char p8[0x14];
    int owner;
    char p20[8];
    float timer;
} Play;

typedef struct {
    char p0[0x180];
    float dt;
} GcGlobalVar;

extern GcGlobalVar gcGlobalVar;
extern int *DldSysUndefSymbol;
extern int execCondition(void *, void *);
extern Play *func_0002E220(Entry *, int, int, void *, int, int, float);

static inline int *dldHandle(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    return off != 0 ? *(int **)((char *)h - off) : 0;
}

static inline void stopPlay(Play *p)
{
    Entry *o = (Entry *)p->owner;
    o->flags &= ~2;
    o->flags &= ~1;
    p->state = 5;
    ((Entry *)p->owner)->busy = 0;
}

static void func_0002E510(Entry *e, int n, int prio, int skip, Play **pp, void *ctx, int t2, int t3)
{
    Play *cur = *pp;
    int i;
    int busy;

    if (cur != 0 && (cur->state == 1 || prio < cur->prio))
        return;
    for (i = 0; i < n; i++, e++) {
        if (dldHandle(&e->handle) == 0)
            continue;
        if (dldHandle(&e->handle) == DldSysUndefSymbol)
            continue;
        if (skip != 0 && skip == e->busy)
            continue;
        if (cur != 0 && (Entry *)cur->owner == e) {
            if (e->once != 0)
                break;
            if (execCondition(ctx, &e->handle) == 0) {
                cur->timer += gcGlobalVar.dt;
                if (!(e->limit < cur->timer))
                    break;
                if ((unsigned int)(cur->state - 5) >= 2) {
                    stopPlay(cur);
                }
                cur = 0;
            } else {
                cur->timer = 0.0f;
                break;
            }
        }
        busy = e->busy;
        if (!((e->flags >> 1) & 1)) {
            if (busy != 0)
                continue;
            if (execCondition(ctx, &e->handle) == 0)
                continue;
        }
        if (cur != 0 && (unsigned int)(cur->state - 5) >= 2) {
            stopPlay(cur);
        }
        cur = func_0002E220(e, prio, 1, ctx, t2, t3, 100.0f);
        if (cur != 0)
            break;
        if (e->once != 0)
            e->flags |= 2;
        break;
    }
    *pp = cur;
}
