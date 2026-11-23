typedef float Vec[4] __attribute__((aligned(16)));
typedef float Mtx[4][4] __attribute__((aligned(16)));
typedef int s128 __attribute__((mode(TI)));
typedef struct { char pad0[0x10]; Vec pos; char pad20[0x10]; int child; int sib; char pad38[0x8]; } Node;
typedef struct { int pad0; int n; Node *nodes; } Skel;

extern Vec All1Vector, YUnitVector, ZUnitVector, ZeroPoint;
extern void GetMotionMatrix(Mtx *, int, Skel *, int, float *, float *);
extern void GetMultiLocalizeMatrix(Mtx *, Mtx *, int);
extern void iosUnitCurrentMatrix(void);
extern void iosPushCurrentMatrix(void);
extern void iosPopCurrentMatrix(void);
extern void iosTransCurrentMatrix(float *);
extern void iosMulCurrentMatrixR(float *);
extern void iosGetCurrentMatrix(float *);
extern void GetDifferencialQuaternionWithNoRegularize(float *, float *, float *, float *);
extern void GetQuaternionByAxisDirZY(float *, float *, float *);

/* The Original computes element addresses as index offset + base. */
#define VEC_AT(arr, i) ((void *)((i) * 16 + (int)(arr)))
#define MTX_AT(arr, i) ((void *)((i) * 64 + (int)(arr)))

#define XFORM(v, m, d)                                          \
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"                  \
                         "lqc2 vf14, 0x0(%1)\n"                 \
                         "lqc2 vf15, 0x10(%1)\n"                \
                         "lqc2 vf16, 0x20(%1)\n"                \
                         "lqc2 vf17, 0x30(%1)\n"                \
                         "vmulax.xyzw ACC, vf14, vf8x\n"        \
                         "vmadday.xyzw ACC, vf15, vf8y\n"       \
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"       \
                         "vmaddw.xyzw vf10, vf17, vf8w\n"       \
                         "sqc2 vf10, 0x0(%2)\n"                 \
                         :                                      \
                         : "r"(v), "r"(m), "r"(d)               \
                         : "memory")

static inline void quat2mtx(Vec *m, float *q)
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
        : : "r"(q), "r"(m));
    m += 3;
    __asm__ __volatile__("sqc2 vf0, 0(%0)" : : "r"(m) : "memory");
}

static inline void mtxinv(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2 $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2 $8, vf24\n"
                         "qmtc2 $9, vf25\n"
                         "qmtc2 $10, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf29, 0x30(%0)\n"
                         : : "r"(dst), "r"(src) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

static inline void xform(float *d, float *m, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%2)\n"
                         : : "r"(v), "r"(m), "r"(d) : "memory");
}

static inline void norm3(float *d, float *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
        "vmul.xyz vf7, vf5, vf5\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vrsqrt Q, vf0w, vf7w\n"
        "vwaitq\n"
        "vmulq.xyz vf5, vf5, Q\n"
        "sqc2 vf5, 0x0(%1)\n"
        : : "r"(v), "r"(d) : "memory");
}

static inline void quatyaxis(float *d, float *q)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf4, 0x0(%1)\n"
        "vmul.xyzw vf5, vf4, vf4\n"
        "vmr32.xyzw vf6, vf4\n"
        "vmul.xyzw vf7, vf6, vf4\n"
        "vmr32.xyzw vf6, vf6\n"
        "vmul.xyzw vf8, vf6, vf4\n"
        "vsubx.z vf6, vf0, vf5x\n"
        "vsuby.z vf6, vf6, vf5y\n"
        "vaddw.y vf6, vf7, vf7w\n"
        "vsuby.x vf6, vf8, vf8y\n"
        "vsub.w vf6, vf0, vf0\n"
        "vadd.w vf5, vf0, vf0\n"
        "vmulw.xyz vf6, vf6, vf5w\n"
        "vaddw.z vf6, vf6, vf0w\n"
        "sqc2 vf6, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(d), "r"(q) : "memory");
}

static inline void quatnorm(float *q)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%0)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(q) : "memory");
}

static void func_00048658(Vec *q, Vec *a, Vec *b, Skel *sk, Vec *rq, int i)
{
    Vec m[4];
    Mtx inv;
    Vec va;
    Vec vb;
    Vec dir;
    Vec yax;
    int sib;
    int child;
    Node *n;
    float *qi;

    sib = ((Node *)(i * 64 + (int)sk->nodes))->sib;
    iosPushCurrentMatrix();
    n = (Node *)(i * 64 + (int)sk->nodes);
    child = n->child;
    iosTransCurrentMatrix(n->pos);
    quat2mtx(m, VEC_AT(rq, i));
    iosMulCurrentMatrixR((float *)m);
    iosGetCurrentMatrix((float *)m);
    mtxinv((float *)inv, (float *)m);
    xform(va, (float *)inv, VEC_AT(a, i));
    xform(vb, (float *)inv, VEC_AT(b, i));
    norm3(va, va);
    if (child < 0) {
        *(s128 *)dir = *(s128 *)ZUnitVector;
    } else {
        norm3(dir, sk->nodes[child].pos);
    }
    qi = *(q + i);
    GetDifferencialQuaternionWithNoRegularize(qi, va, dir, YUnitVector);
    quatyaxis(yax, qi);
    GetQuaternionByAxisDirZY(qi, yax, vb);
    quatnorm(qi);
    quat2mtx(m, qi);
    iosMulCurrentMatrixR((float *)m);
    if (child != -1) {
        func_00048658(q, a, b, sk, rq, child);
    }
    iosPopCurrentMatrix();
    if (sib != -1) {
        func_00048658(q, a, b, sk, rq, sib);
    }
}

static void func_00048A30(Skel *skel, int f1, int f2, float *pos, int f3)
{
    int n = skel->n;
    Vec a[n];
    Vec b[n];
    int i;
    {
        Mtx m[n];
        Mtx *mm = m;
        GetMotionMatrix(m, 0, skel, f2, pos, All1Vector);
        for (i = 0; i < n; i++) {
            static const Vec dflt = { 0.0f, 0.0f, 100.0f, 1.0f };
            const float *v;
            Node *nd = MTX_AT(skel->nodes, i);
            if (nd->child >= 0) {
                v = skel->nodes[nd->child].pos;
            } else {
                v = dflt;
            }
            XFORM(v, MTX_AT(mm, i), VEC_AT(a, i));
            XFORM(YUnitVector, MTX_AT(mm, i), VEC_AT(b, i));
        }
        GetMotionMatrix(m, 0, skel, f1, ZeroPoint, All1Vector);
        GetMultiLocalizeMatrix(m, m, n);
        for (i = 0; i < n; i++) {
            XFORM(VEC_AT(a, i), MTX_AT(m, i), VEC_AT(a, i));
            XFORM(VEC_AT(b, i), MTX_AT(m, i), VEC_AT(b, i));
        }
        GetMotionMatrix(m, 0, skel, f3, ZeroPoint, All1Vector);
        for (i = 0; i < n; i++) {
            XFORM(VEC_AT(a, i), MTX_AT(m, i), VEC_AT(a, i));
        }
        XFORM(VEC_AT(b, i), MTX_AT(m, i), VEC_AT(b, i));
        pos[3] = 1.0f;
    }
    iosUnitCurrentMatrix();
    iosTransCurrentMatrix(pos);
    func_00048658((Vec *)f2, a, b, skel, (Vec *)f3, 0);
}
