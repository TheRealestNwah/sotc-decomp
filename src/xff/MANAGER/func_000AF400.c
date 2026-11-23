#ifdef NONMATCHING
/* Parked: 12 diffs, same size. Remaining: in each of the three cases the key build loads 0x80000000 into $a0 and ORs into $v1 (the Original uses $v1 for the constant and reuses $v0 for the result). */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { int a; int b; } Key;
typedef struct { int count; int start; } Leaf;
typedef struct { int *idx; Leaf *leaves; } Tree;
typedef struct {
    int id;
    void *layout;
    float height;
    Vec4 *mtx;
    Vec4 *mtx2;
    float scale;
    int mode;
    int (*filter)(Vec4 *, Vec4 *, int);
    int (*filter2)(Key *, int);
    int arg;
} Ctx;
typedef struct { Key key; char pad8[0x38]; Vec4 pos; } Hit;

extern Vec4 *getLayoutClassCollisionIndepSurfBoundary(void *, int, int);
extern int ClipCollisionDB(Hit *, Vec4 *, Vec4 *, Key *);

static inline void xform(Vec4 *out, Vec4 *m, Vec4 *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

static inline void xform2(Vec4 *v, Vec4 *m, Vec4 *out)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

static inline int inCylinder(Vec4 *v, float r, float h)
{
    int in = 0;
    if (v->f[0] * v->f[0] + v->f[1] * v->f[1] < r * r && -r < v->f[2] && v->f[2] < h + r)
        in = 1;
    return in;
}

static int func_000AF400(Hit *hit, Vec4 *p0, Vec4 *p1, Tree *tree, int leafNo, Ctx *c)
{
    Vec4 q0, q1, bnd, loc;
    Key key;
    Key t0, t1, t2;
    Leaf *leaf = &tree->leaves[leafNo];
    int *ip = &tree->idx[leaf->start];
    int found;
    int i;
    Vec4 *m;
    float h, r;
    int n;

    switch (c->mode) {
    case 0:
    default:
        n = leaf->count;
        found = 0;
        if (n == 0)
            break;
        xform(&q0, c->mtx, p0);
        xform(&q1, c->mtx, p1);
        if (n > 0) { i = n; do {
            Vec4 *b = getLayoutClassCollisionIndepSurfBoundary(c->layout, 0, *ip);
            bnd.q = b->q;
            bnd.f[3] = 1.0f;
            m = c->mtx2;
            h = c->height;
            r = b->f[3];
            xform2(&bnd, m, &loc);
            if (!inCylinder(&loc, r, h))
                continue;
            if (c->filter && !c->filter(&bnd, c->mtx2, c->arg))
                continue;
            t0.a = c->id; t0.b = *ip | 0x80000000; key = t0;
            if (c->filter2 && !c->filter2(&key, c->arg))
                continue;
            if (ClipCollisionDB(hit, &q0, &q1, &key)) {
                found = 1;
                hit->key.a = key.a;
                hit->key.b = key.b;
                q1.q = hit->pos.q;
            }
        } while (ip++, --i); }
        break;
    case 1:
        n = leaf->count;
        found = 0;
        if (n == 0)
            break;
        xform(&q0, c->mtx, p0);
        xform(&q1, c->mtx, p1);
        if (n > 0) { i = n; do {
            Vec4 *b = getLayoutClassCollisionIndepSurfBoundary(c->layout, 0, *ip);
            bnd.q = b->q;
            bnd.f[3] = 1.0f;
            m = c->mtx2;
            h = c->height;
            r = b->f[3];
            xform2(&bnd, m, &loc);
            if (!inCylinder(&loc, r, h))
                continue;
            if (c->filter && !c->filter(&bnd, c->mtx2, c->arg))
                continue;
            t1.a = c->id; t1.b = *ip | 0x80000000; key = t1;
            if (c->filter2 && !c->filter2(&key, c->arg))
                continue;
            if (ClipCollisionDB(hit, &q0, &q1, &key) || ClipCollisionDB(hit, &q1, &q0, &key)) {
                found = 1;
                hit->key.a = key.a;
                hit->key.b = key.b;
                q1.q = hit->pos.q;
            }
        } while (ip++, --i); }
        break;
    case 2:
        n = leaf->count;
        found = 0;
        if (n == 0)
            break;
        xform(&q0, c->mtx, p0);
        xform(&q1, c->mtx, p1);
        if (n > 0) { i = n; do {
            Vec4 *b = getLayoutClassCollisionIndepSurfBoundary(c->layout, 0, *ip);
            bnd.q = b->q;
            bnd.f[3] = 1.0f;
            m = c->mtx2;
            h = c->height;
            r = b->f[3];
            xform2(&bnd, m, &loc);
            if (!inCylinder(&loc, r, h))
                continue;
            if (c->filter && !c->filter(&bnd, c->mtx2, c->arg))
                continue;
            t2.a = c->id; t2.b = *ip | 0x80000000; key = t2;
            if (c->filter2 && !c->filter2(&key, c->arg))
                continue;
            if (ClipCollisionDB(hit, &q1, &q0, &key)) {
                found = 1;
                hit->key.a = key.a;
                hit->key.b = key.b;
                q1.q = hit->pos.q;
            }
        } while (ip++, --i); }
        break;
    }
    return found;
}
#else
static int func_000AF400();
#endif
