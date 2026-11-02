typedef struct { char pad[0x14]; float f14; } Param;

extern int func_000FACE0(void *, void *);
extern float CalcDistancePointAnd2Point(void *, void *, void *);

extern int func_000FA610(void *, void *, void *, float);

static int func_000FA500(void *a, void *b, void *c, Param *p, void *d)
{
    if (func_000FACE0(d, a) == 0)
        return func_000FA610(c, a, b, p->f14);
    return 0;
}

static int func_000FA588(void *a, void *b, void *c, Param *p, void *d)
{
    if (func_000FACE0(d, a) == 0)
        return func_000FA610(a, c, b, p->f14);
    return 0;
}

/* Matches, but the asm has no function label at 0xFA610 for the splice
   to place it. */
#ifdef NONMATCHING
static int func_000FA610(void *a, void *b, void *c, float max)
{
    float d = CalcDistancePointAnd2Point(a, b, c);

    if (0.0f <= d && d <= max)
        return 1;
    return 0;
}
#endif

typedef struct { short h0; short h2; char pad[0x10]; float f14; } AreaLine;

extern AreaLine *getLineDataByAreaIdx(void *, int, int);
extern void *getPointDataByAreaIdx(void *, int, int);

static int func_000FA658(void *w, void *pos, int b, int area)
{
    AreaLine *l = getLineDataByAreaIdx(w, b, area);
    void *p0;
    void *p1;

    if (l != 0) {
        p0 = getPointDataByAreaIdx(w, l->h0, area);
        p1 = getPointDataByAreaIdx(w, l->h2, area);
        if (p0 != 0 && p1 != 0)
            return func_000FA610(pos, p0, p1, l->f14);
    }
    return 0;
}
