typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { float split; unsigned int flags; } Node;
typedef struct { void *idx; void *leaves; Node *nodes; } Tree;
typedef struct { int pad[5]; float scale; } Ctx;
typedef struct Hit Hit;
extern int func_000B0BC8(Hit *, Vec4 *, Vec4 *, Tree *, int, Ctx *);
extern int func_000B69F0(Hit *, Vec4 *, Vec4 *, Tree *, Node *, Ctx *);

static inline void lerp(Vec4 *out, Vec4 *a, Vec4 *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         :
                         : "r"(out), "r"(a), "r"(b), "f"(t)
                         : "$8", "memory");
}

#define RIGHT(f) (((f) >> 17) & 0x3FFF)
static int func_000B1380(Hit *hit, Vec4 *p0, Vec4 *p1, Tree *tree, Node *node, Ctx *c)
{
    int r = 0;
    Vec4 q1, q0;
    unsigned int f = node->flags;
    int ax = f & 3;
    float s = node->split * c->scale;
    float a = *(p0->f + ax);
    float b = *(p1->f + ax);
    int i0 = s <= a;
    int i1 = s <= b;
    if (i0 || i1) {
        if ((int)f < 0) {
            r = func_000B0BC8(hit, p0, p1, tree, RIGHT(f), c);
        } else if (i0) {
            if (i1) {
                r = func_000B69F0(hit, p0, p1, tree, &tree->nodes[RIGHT(f)], c);
            } else {
                lerp(&q1, p0, p1, (s - b) / (a - b) - 0.0f);
                r = func_000B69F0(hit, p0, &q1, tree, &tree->nodes[RIGHT(f)], c);
            }
        } else {
            lerp(&q0, p1, p0, (s - a) / (b - a) - 0.0f);
            r = func_000B69F0(hit, &q0, p1, tree, &tree->nodes[RIGHT(f)], c);
        }
    }
    return r;
}
