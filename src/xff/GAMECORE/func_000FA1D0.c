typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 q;
    int i10;
    short s14;
    short s16;
    short s18;
    short s1A;
    int i1C;
} Ent;

typedef struct {
    char pad[0x100];
    Ent e[0x14];
    int count;
} Work;

extern s128 *getPointDataByAreaIdx(Work *, int, int);

static inline Ent *getEnt(Work *w, int i)
{
    if (i < 0x14)
        return &w->e[i];
    return 0;
}

static inline Ent *getEntChk(Work *w, int i)
{
    if (i < 0x14 && (unsigned)i < (unsigned)w->count)
        return &w->e[i];
    return 0;
}

static inline int addEnt(Work *w, s128 *p, int a1, int a2, int a3)
{
    Ent *e;

    if ((unsigned)w->count >= 0x13)
        return 0;
    e = getEnt(w, w->count);
    e->q = *p;
    e->s1A = 1;
    e->s14 = a1;
    e->i1C = a2;
    e->s16 = a3;
    e->s18 = 0;
    e->i10 = 0;
    w->count++;
    return 1;
}

static void func_000FA1D0(Work *w, int a1, int a2, int a3)
{
    s128 *p = getPointDataByAreaIdx(w, a1, a2);

    if (p == 0)
        return;
    if (addEnt(w, p, a1, a2, a3))
        getEntChk(w, w->count - 1)->i10 = 1;
}
