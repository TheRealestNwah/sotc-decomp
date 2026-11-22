/* Parked: 21 diffs, same size. BGM play-slot allocator: returns 0 while D_0017A930 is set, the entry's busy slot if it has one, else claims the first free slot of B_001887D0[3] (or, with none free, inlines bgmMinPriorityForceClose: fades out a state-6 slot or force-closes the lowest-priority one), standby-loads the BGM through bgmStandbyWithPri, fills the slot and refreshes the D_0017A938 minimum priority. Remaining: the found block's stores are scheduled differently and the Original materialises %hi(B_001887D0) before %hi(D_0017A938) in the final loop. */
#ifdef NONMATCHING
typedef struct Entry {
    unsigned int bgm;
    char p4[4];
    unsigned int handle;
    int once;
    float limit;
    char p14[0x28];
    float fade;
    int busy;
    unsigned int flags;
    char p48[8];
} Entry;

typedef struct Play {
    int state;
    int prio;
    int arg;
    char pC[8];
    int f14;
    int *hnd;
    int owner;
    void *ctx;
    float f24;
    int f28;
    int f2C;
    void (*cb)(struct Play *);
    float vol;
    long long mode;
} Play;

extern int *DldSysUndefSymbol;
extern int D_0017A930;
extern int D_0017A938;
extern long long D_0017A940[];
extern Play B_001887D0[3];
extern void adpcmCloseFadeSetVol(int, float);
extern int *bgmStandbyWithPri(char *, int, int, Play *, int);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

static inline void stopPlay(Play *p)
{
    Entry *o = (Entry *)p->owner;
    o->flags &= ~2;
    o->flags &= ~1;
    p->state = 5;
    ((Entry *)p->owner)->busy = 0;
}

static inline void minPrioClose(int prio)
{
    Play *best = 0;
    int i;

    for (i = 0; i < 3; i++) {
        Play *q = &B_001887D0[i];
        if (q->state == 6) {
            adpcmCloseFadeSetVol(*q->hnd, 100.0f);
            return;
        }
    }
    for (i = 0; i < 3; i++) {
        Play *q = &B_001887D0[i];
        if (q->state != 0 && q->prio < prio) {
            prio = q->prio;
            best = q;
        }
    }
    if (best != 0) {
        int st = best->state;
        best->f24 = 0.0f;
        if (st != 5 && st != 6)
            stopPlay(best);
        if (best->cb != 0)
            best->cb(best);
    }
}

static inline void updateMax(void)
{
    int i;
    for (i = 0; i < 3; i++) {
        if (B_001887D0[i].state == 0) {
            D_0017A938 = 0;
            return;
        }
        D_0017A938 = B_001887D0[i].prio < D_0017A938 ? B_001887D0[i].prio : D_0017A938;
    }
}

static Play *func_0002E220(Entry *e, int prio, int arg, void *ctx, int a4, void (*cb)(Play *), float vol)
{
    Play *p;
    int i;
    int *h;

    if (D_0017A930 != 0)
        return 0;
    if (e->busy != 0)
        return (Play *)e->busy;
    for (i = 0; i < 3; i++) {
        p = &B_001887D0[i];
        if (p->state == 0)
            goto found;
    }
    minPrioClose(prio);
    return 0;
found:
    h = bgmStandbyWithPri(dldResolve(&e->bgm), 0, a4, p, prio);
    p->hnd = h;
    if (h == 0)
        return 0;
    e->flags &= ~2;
    e->flags &= ~1;
    p->prio = prio;
    p->owner = (int)e;
    p->f28 = 0;
    p->f2C = 0;
    p->cb = cb;
    e->busy = (int)p;
    p->f24 = e->fade;
    p->state = 1;
    p->arg = arg;
    p->ctx = ctx;
    p->f14 = 0;
    p->mode = D_0017A940[(e->flags >> 4) & 7];
    p->vol = vol;
    updateMax();
    return p;
}
#endif
