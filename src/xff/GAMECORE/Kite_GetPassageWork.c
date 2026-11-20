/* Parked attempt: 10 words differ from the Original. */
#ifdef NONMATCHING
typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef struct {
    Vec4 pos;
    int area;
    int pt;
    int idx;
    int pad;
} PassPt;

typedef struct {
    PassPt p[2];
} PassPair;

typedef struct {
    int x0;
    int x4;
    int x8[2];
    PassPair cur;
    PassPair prev;
    PassPair save;
} PassWork;

extern char *getPassageWork(void *, int);
extern char *getPointDataByAreaIdx(void *, int, int);
extern PassPt *func_000AD410(int *, int);

static inline void vecUnit(float *v)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(v) : "memory");
}

static inline int samePt(PassPt *a, PassPt *b)
{
    if (a->idx == b->idx && a->area == b->area)
        return 1;
    return 0;
}

int Kite_GetPassageWork(int unused, void *owner, int *kite, PassWork *w, int flag)
{
    char *pw0 = 0;
    char *pw1 = 0;
    PassPt a;
    PassPt b;
    char *p;
    char *q;
    PassPt *v;

    if (owner) {
        pw0 = getPassageWork(owner, 0);
        pw1 = getPassageWork(owner, 1);
    }
    vecUnit(a.pos);
    a.area = -1;
    a.pt = 0;
    a.idx = -1;
    vecUnit(b.pos);
    b.area = -1;
    b.pt = 0;
    b.idx = -1;
    if (pw0 && w->x4 >= 0) {
        p = getPointDataByAreaIdx(owner, *(short *)(pw0 + 0x14), *(int *)(pw0 + 0x1C));
        if (!p)
            return 0;
        *(u_long128 *)a.pos = *(u_long128 *)p;
        a.area = *(short *)(pw0 + 0x14);
        a.idx = *(int *)(pw0 + 0x1C);
        if (*kite == 6)
            a.pt = 0;
        else
            a.pt = *(short *)(p + 0x1C);
    } else {
        if (*kite == 6)
            return 0;
        if (flag)
            v = func_000AD410(kite, 0);
        else
            v = (PassPt *)(kite + 0x48);
        if (v)
            a = *v;
    }
    if (pw1 && w->x4 >= 0) {
        q = getPointDataByAreaIdx(owner, *(short *)(pw1 + 0x14), *(int *)(pw1 + 0x1C));
        if (!q)
            return 0;
        *(u_long128 *)b.pos = *(u_long128 *)q;
        b.area = *(short *)(pw1 + 0x14);
        b.idx = *(int *)(pw1 + 0x1C);
        if (*kite == 6)
            b.pt = 0;
        else
            b.pt = *(short *)(q + 0x1C);
    } else {
        if (flag)
            v = func_000AD410(kite, 1);
        else
            v = (PassPt *)(kite + 0x50);
        if (v)
            b = *v;
    }
    if (w->prev.p[0].area == -1)
        w->prev.p[0] = a;
    if (w->prev.p[1].area == -1)
        w->prev.p[1] = b;
    if (w->cur.p[0].area == -1)
        w->cur.p[0] = a;
    if (w->cur.p[1].area == -1)
        w->cur.p[1] = b;
    if (!flag) {
        if (!samePt(&a, &w->prev.p[0])) {
            if (samePt(&a, &w->cur.p[0]))
                w->cur.p[1] = b;
        }
        if (*(int *)((char *)w + 0xE8)) {
            if (samePt(&a, &w->cur.p[0])) {
                w->cur.p[0] = b;
            } else if (samePt(&w->cur.p[1], &a)) {
                if (!samePt(&w->cur.p[0], &w->cur.p[1])) {
                    w->cur.p[0] = a;
                    w->cur.p[1] = b;
                }
            }
        }
        if (samePt(&w->cur.p[0], &a) || samePt(&w->cur.p[0], &b) || samePt(&w->cur.p[1], &a))
            goto done;
        if (w->save.p[0].area != -1 && w->save.p[1].area != -1) {
            w->cur = w->save;
            goto done;
        }
    }
    w->cur.p[0] = a;
    w->cur.p[1] = b;
done:
    w->prev.p[0] = a;
    w->prev.p[1] = b;
    *(int *)((char *)w + 0xE8) = 0;
    *(int *)((char *)w + 0x1B8) = 0;
    return 0;
}
#endif
