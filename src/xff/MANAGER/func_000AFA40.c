typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { int axis; float split; int left; int right; } Node;
typedef struct { char pad0[8]; Node *nodes; } Tree;
typedef struct { char pad0[0x14]; float scale; } Ctx;

extern int func_000AF400(void *, Vec4 *, Vec4 *, Tree *, int, Ctx *);

static inline void lerp3(Vec4 *out, Vec4 *a, Vec4 *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

static int func_000AFA40(void *obj, Vec4 *p0, Vec4 *p1, Tree *tree, Node *n, Ctx *c);

static inline int visitHi(void *obj, Vec4 *p0, Vec4 *p1, Tree *tree, Node *n, Ctx *c)
{
    int r = 0;
    float s = n->split * c->scale;
    float a = (&p0->f[0])[n->axis];
    float b = (&p1->f[0])[n->axis];
    int ia = s <= a;
    int ib = s <= b;
    if (ia || ib) {
        int child = n->right;
        if (child < 0) {
            r = func_000AF400(obj, p0, p1, tree, (child << 1) >> 1, c);
        } else if (ia && ib) {
            r = func_000AFA40(obj, p0, p1, tree, &tree->nodes[child], c);
        } else if (ia) {
            Vec4 q;
            lerp3(&q, p0, p1, (s - b) / (a - b) - 0.0f);
            r = func_000AFA40(obj, p0, &q, tree, &tree->nodes[child], c);
        } else {
            Vec4 q;
            lerp3(&q, p1, p0, (s - a) / (b - a) - 0.0f);
            r = func_000AFA40(obj, &q, p1, tree, &tree->nodes[child], c);
        }
    }
    return r;
}

static inline int visitLo(void *obj, Vec4 *p0, Vec4 *p1, Tree *tree, Node *n, Ctx *c)
{
    int r = 0;
    float s = n->split * c->scale;
    float a = (&p0->f[0])[n->axis];
    float b = (&p1->f[0])[n->axis];
    int ia = a <= s;
    int ib = b <= s;
    if (ia || ib) {
        int child = n->left;
        if (child < 0) {
            r = func_000AF400(obj, p0, p1, tree, (child << 1) >> 1, c);
        } else if (ia && ib) {
            r = func_000AFA40(obj, p0, p1, tree, &tree->nodes[child], c);
        } else if (ia) {
            Vec4 q;
            lerp3(&q, p1, p0, (s - a) / (b - a) + 0.0f);
            r = func_000AFA40(obj, p0, &q, tree, &tree->nodes[child], c);
        } else {
            Vec4 q;
            lerp3(&q, p0, p1, (s - b) / (a - b) + 0.0f);
            r = func_000AFA40(obj, &q, p1, tree, &tree->nodes[child], c);
        }
    }
    return r;
}

static int func_000AFA40(void *obj, Vec4 *p0, Vec4 *p1, Tree *tree, Node *n, Ctx *c)
{
    int hit;
    if ((&p0->f[0])[n->axis] >= (&p1->f[0])[n->axis]) {
        hit = 0;
        if (visitHi(obj, p0, p1, tree, n, c) || visitLo(obj, p0, p1, tree, n, c))
            hit = 1;
    } else {
        hit = 0;
        if (visitLo(obj, p0, p1, tree, n, c) || visitHi(obj, p0, p1, tree, n, c))
            hit = 1;
    }
    return hit;
}
