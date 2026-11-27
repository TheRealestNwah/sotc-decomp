#ifdef NONMATCHING /* parked draft: 5 diffs (VU0 helpers as in GetMotionMatrixOfChildsFromTarget.c). Pinning scale to $s1 and idx to $s2 gives the Original's saved-register order (&q in $s0); empty asm barriers after iosCopyMatrix and the qout store keep ix live so qout[ix] uses a temporary. Left: the idx & 0x10000 test lands in $v1, and the loop copies c = ix before loading mot->nodes and tests c instead of ix */
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    float m[4][4];
} Mtx;

typedef struct {
    float v[4];
} Vec;

typedef struct {
    char pad0[0x10];
    Vec pos;
    char pad20[0x10];
    int child;
    int next;
    int parent;
    char pad3C[4];
} MotNode;

typedef struct {
    char pad0[8];
    MotNode *nodes;
} Motion;

static inline void vecMulXYZ(Vec *dst, Vec *a, Vec *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(a), "r"(b), "r"(dst) : "memory");
}

/* The asm below has no "memory" clobber: gcc 2.96's cse flushes its table at a
 * volatile asm without outputs or clobbers, so mtx[c] and qout[c] recompute c's
 * offsets like the Original instead of reusing them. */
static inline void quatPosMatrix(Mtx *dst, Vec *q, Vec *t)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%0)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "sqc2 vf14, 0x0(%1)\n"
                         "sqc2 vf15, 0x10(%1)\n"
                         "sqc2 vf16, 0x20(%1)\n"
                         : : "r"(q), "r"(dst));
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(dst), "r"(t));
}

static inline void mtxMul(Mtx *dst, Mtx *a, Mtx *b)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%0)\n"
                         "lqc2 vf15, 0x10(%0)\n"
                         "lqc2 vf16, 0x20(%0)\n"
                         "lqc2 vf17, 0x30(%0)\n"
                         "lqc2 vf24, 0x0(%1)\n"
                         "lqc2 vf25, 0x10(%1)\n"
                         "lqc2 vf26, 0x20(%1)\n"
                         "lqc2 vf27, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf24x\n"
                         "vmadday.xyzw ACC, vf15, vf24y\n"
                         "vmaddaz.xyzw ACC, vf16, vf24z\n"
                         "vmaddw.xyzw vf24, vf17, vf24w\n"
                         "vmulax.xyzw ACC, vf14, vf25x\n"
                         "vmadday.xyzw ACC, vf15, vf25y\n"
                         "vmaddaz.xyzw ACC, vf16, vf25z\n"
                         "vmaddw.xyzw vf25, vf17, vf25w\n"
                         "vmulax.xyzw ACC, vf14, vf26x\n"
                         "vmadday.xyzw ACC, vf15, vf26y\n"
                         "vmaddaz.xyzw ACC, vf16, vf26z\n"
                         "vmaddw.xyzw vf26, vf17, vf26w\n"
                         "vmulax.xyzw ACC, vf14, vf27x\n"
                         "vmadday.xyzw ACC, vf15, vf27y\n"
                         "vmaddaz.xyzw ACC, vf16, vf27z\n"
                         "vmaddw.xyzw vf27, vf17, vf27w\n"
                         "sqc2 vf24, 0x0(%2)\n"
                         "sqc2 vf25, 0x10(%2)\n"
                         "sqc2 vf26, 0x20(%2)\n"
                         "sqc2 vf27, 0x30(%2)\n"
                         : : "r"(a), "r"(b), "r"(dst));
}

static inline void quatMul(Vec *dst, Vec *a, Vec *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                         "lqc2 vf12, 0x0(%1)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%2)\n"
                         : : "r"(a), "r"(b), "r"(dst));
}

static inline void quatPosScaleMatrix(Mtx *dst, Vec *q, Vec *pos, Vec *scale)
{
    Vec t;

    vecMulXYZ(&t, pos, scale);
    t.v[3] = 1.0f;
    quatPosMatrix(dst, q, &t);
}

static inline void quatNormalize(Vec *v)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%0)
"
                         "vmul.xyzw vf15, vf14, vf14
"
                         "vaddy.x vf15, vf15, vf15y
"
                         "vaddz.x vf15, vf15, vf15z
"
                         "vaddw.x vf15, vf15, vf15w
"
                         "vrsqrt Q, vf0w, vf15x
"
                         "vwaitq
"
                         "vmulq.xyzw vf15, vf14, Q
"
                         "sqc2 vf15, 0x0(%0)
"
                         : : "r"(v));
}

extern Vec D_001365B0;
extern void iosUnitMatrix(Mtx *);
extern void iosCopyMatrix(Mtx *, Mtx *);

static inline void unitQuat(Vec *v)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)
" : : "r"(v));
}

void GetMotionMatrixOfTargetFromRoot(Mtx *mtx, Vec *qout, Motion *mot, Vec *rot, Vec *root, Vec *scale, int idx)
{
    Mtx acc;
    Vec q;
    Vec v;
    Mtx m;
    MotNode *nodes;
    MotNode *node;
    Vec *g;
    int c;
    register int ix __asm__("$18") = idx;
    register Vec *sc __asm__("$17") = scale;

    if (ix > 0 && (ix & 0x10000)) {
        return;
    }
    unitQuat(&v);
    unitQuat(&q);
    iosUnitMatrix(&acc);
    nodes = mot->nodes;
    c = ix;
    while (c != -1) {
        Vec *r = &rot[c];
        node = &nodes[c];
        quatPosScaleMatrix(&m, r, &node->pos, sc);
        mtxMul(&acc, &m, &acc);
        quatMul(&q, r, &q);
        c = node->parent;
    }
    g = &D_001365B0;
    *(s128 *)g = *(s128 *)root;
    mtxMul(&acc, (Mtx *)(g - 3), &acc);
    quatNormalize(&q);
    iosCopyMatrix(&mtx[ix], &acc);
    __asm__ __volatile__("" : "+r"(ix));
    *(s128 *)&qout[ix] = *(s128 *)&q;
    __asm__ __volatile__("" : : "r"(ix));
}
#endif
