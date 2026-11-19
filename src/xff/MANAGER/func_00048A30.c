typedef float Vec[4] __attribute__((aligned(16)));
typedef float Mtx[4][4] __attribute__((aligned(16)));
typedef struct { char pad0[0x10]; Vec pos; char pad20[0x10]; int parent; char pad34[0xC]; } Node;
typedef struct { int pad0; int n; Node *nodes; } Skel;

extern Vec All1Vector, YUnitVector, ZeroPoint;
extern void GetMotionMatrix(Mtx *, int, Skel *, int, float *, float *);
extern void GetMultiLocalizeMatrix(Mtx *, Mtx *, int);
extern void iosUnitCurrentMatrix(void);
extern void iosTransCurrentMatrix(float *);
extern void func_00048658(int, Vec *, Vec *, Skel *, int, int);

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
            if (nd->parent >= 0) {
                v = skel->nodes[nd->parent].pos;
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
    func_00048658(f2, a, b, skel, f3, 0);
}
