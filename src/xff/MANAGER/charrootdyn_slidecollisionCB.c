/* Parked: 15 diffs. Slides a two-point segment (pos, pos2) along delta: a clip query finds the first hit, the delta is projected onto the hit plane, then a 4D slide query (with or without the filter callback) resolves the final position, which is pushed back out of the plane when behind it. Copies the hit layout/normal, clamps the two class limits and takes the slide's boss DB info if none was set. The float arguments are declared first in the SlideCollisionFinder4D prototypes only to get the Original argument setup order and register allocation. Remaining: the 64-byte boss DB info copy, which the Original schedules as alternating ld/sd pairs through v0/v1 and gcc here loads into eight registers before storing. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct { int a; int b; } Pair;
typedef struct {
    long long d0[6];
    int flag;
    int pad34;
    long long d38;
} SlideSub;

typedef struct {
    Vec4 p;
    Vec4 normal;
    Pair layout;
    char pad28[0x28];
} GeomHit;

typedef struct {
    Vec4 p;
    char pad10[0x20];
    SlideSub sub;
    int lo;
    int hi;
    char pad78[8];
} SlideRes;

typedef struct {
    Vec4 a;
    Vec4 b;
    Pair layout;
    char pad28[8];
    Vec4 normal;
    SlideSub sub;
    int hi;
    int lo;
} SlideOut;

extern int ClipCollisionFinderWithKeep4DSlopeLimit(GeomHit *, Vec4 *, Vec4 *, void *, void *);
extern int ClipCollisionFinderWithKeep4DSlopeLimitCB(GeomHit *, Vec4 *, Vec4 *, void *, void *, void *, int);
extern int SlideCollisionFinder4D(SlideRes *, Vec4 *, Vec4 *, float, float, void *, void *);
extern int SlideCollisionFinder4DCB(SlideRes *, Vec4 *, Vec4 *, float, float, void *, void *, void *, void *);
extern char *GetLayoutClass(int);
extern void getBossDBInfo(SlideSub *, GeomHit *);
extern float GetPointDistanceFromPlane(Vec4 *, Vec4 *);

static inline void vecAdd(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float dotXYZ(Vec4 *a, Vec4 *b)
{
    float dot;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

static inline float lengthSquareXYZ(Vec4 *v)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(v) : "$2");
    return r;
}

static inline void scaleXYZ(Vec4 *out, Vec4 *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(s) : "memory");
}

int charrootdyn_slidecollisionCB(SlideOut *out, Vec4 *pos, Vec4 *pos2, Vec4 *delta, void *db, void *e, void *cb,
                                 void *flags, float f0, float f1)
{
    Vec4 end[2];
    GeomHit hit;
    Vec4 seg[2];
    Vec4 proj;
    SlideRes res;
    Vec4 tmp;
    int r;
    int r0;
    SlideSub *sub = &out->sub;

    sub->flag = 0;
    {
        s128 *pq = &pos->q;
        seg[0].q = *pq;
    }
    seg[1].q = pos2->q;
    vecAdd(&end[0], &seg[1], delta);
    vecAdd(&end[1], pos, delta);
    if (cb != 0)
        r0 = ClipCollisionFinderWithKeep4DSlopeLimitCB(&hit, seg, end, db, e, cb, 0);
    else
        r0 = ClipCollisionFinderWithKeep4DSlopeLimit(&hit, seg, end, db, e);
    if (r0 != 0) {
        float s = dotXYZ(&hit.normal, delta) / lengthSquareXYZ(&hit.normal);
        int v;

        scaleXYZ(&proj, &hit.normal, s);
        vecAdd(&end[0], pos2, &proj);
        vecAdd(&end[1], pos, &proj);
        v = *(int *)(*(char **)(GetLayoutClass(hit.layout.a) + 0x174) + 0x20);
        out->lo = out->hi = v;
        getBossDBInfo(sub, &hit);
        if (cb != 0)
            r = SlideCollisionFinder4DCB(&res, pos, end, f0, f1, db, e, cb, flags);
        else
            r = SlideCollisionFinder4D(&res, pos, end, f0, f1, db, e);
        if (r != 0) {
            float d = GetPointDistanceFromPlane(&hit.normal, pos);

            if (d < 0.0f) {
                scaleXYZ(&tmp, &hit.normal, -(d / lengthSquareXYZ(&hit.normal)));
                vecAdd(&out->b, pos, &tmp);
                vecAdd(&out->b, &out->b, &proj);
            } else {
                vecAdd(&out->b, pos, &proj);
            }
            out->a.q = res.p.q;
            {
                Pair *dp = &out->layout;
                dp->a = hit.layout.a;
                dp->b = hit.layout.b;
            }
            out->lo = res.lo < out->lo ? res.lo : out->lo;
            out->normal.q = hit.normal.q;
            out->hi = out->hi < res.hi ? res.hi : out->hi;
            if (sub->flag == 0 && res.sub.flag != 0)
                *sub = res.sub;
            return r;
        }
    }
    out->b.q = end[1].q;
    out->a.q = end[0].q;
    return 0;
}
#endif
