typedef int s128 __attribute__((mode(TI)));

extern float YUnitVector[];
extern int DldSysUndefSymbol;
extern s128 *GetCollisionDBPlane(void *);
extern void GetCollisionEdgePointerVertexPoint(int *, void *);
extern void GetQuaternionByAxisDirZY(float *, float *, float *);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, float *);
extern void func_00067068(float *, s128 *, void *, void *, char *, float, float, float, int, int, int);
extern void SetLayoutClassRootQuaternion(char *, float *);

typedef struct {
    char pad0[0xC];
    int size;
} DldType;

typedef struct {
    char pad0[0x8];
    DldType *type;
    int pad1;
    char *data;
} DldTable;

static inline void *dldElement(int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + (((unsigned int)*h >> 18) & 0xFFF) * t->type->size : 0;
}

static inline void quatMul(float *d, float *a, float *b)
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
                         "vadd.xyz vf13, vf14, vf15
"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%2)\n"
                         : : "r"(a), "r"(b), "r"(d) : "memory");
}

static inline int edgepointstab(float *q, s128 *plane, void *a2, void *a3, char *obj, float f0, float f1, float f2, int t1, int t2,
                                int useEdge, int exchange, int t3)
{
    float cross[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    int pts[2];
    char *edge = obj + 0xC0;

    if (*(int *)(edge + 0x30) != 4)
        return 0;
    if (plane != 0)
        *plane = *GetCollisionDBPlane(edge);
    if (useEdge != 0) {
        GetCollisionEdgePointerVertexPoint(pts, edge);
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(dir), "r"(pts[1]), "r"(pts[0]) : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vopmula.xyz ACC, vf5, vf6\n"
                             "vopmsub.xyz vf7, vf6, vf5\n"
                             "vsub.w vf7, vf7, vf7\n"
                             "sqc2 vf7, 0x0(%2)\n"
                             : : "r"(dir), "r"(YUnitVector), "r"(cross) : "memory");
        __asm__ __volatile__(".set noreorder\n"
                             "lqc2 vf5, 0x0(%1)\n"
                             "vmul.xyz vf7, vf5, vf5\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vrsqrt Q, vf0w, vf7w\n"
                             "vwaitq\n"
                             "vmulq.xyz vf5, vf5, Q\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             ".set reorder\n"
                             : : "r"(cross), "r"(cross) : "memory");
        GetQuaternionByAxisDirZY(q, cross, YUnitVector);
    } else {
        func_00067068(q, plane, a2, a3, obj, f0, f1, f2, t1, t2, t3);
    }
    if (exchange != 0) {
        SetQuaternionByAxisRotateVWithNoRegularize(cross, -0x8000, YUnitVector);
        quatMul(q, q, cross);
    }
    return 1;
}

static int func_000677B8(char *o, s128 *plane)
{
    float q[4] __attribute__((aligned(16)));
    char work[0xA0] __attribute__((aligned(16)));
    float aux[4] __attribute__((aligned(16)));
    unsigned int *flags;
    float s;
    int ok;

    flags = dldElement((int *)(*(char **)(o + 0x1C0) + 0xC));
    s = *(float *)(*(char **)(o + 0x1140) + 0xC4);
    if (flags != 0) {
        unsigned int v = *flags;
        ok = edgepointstab(q, plane, work, aux, o, s, s, -s, (v >> 1) & 1, v & 1, (v >> 2) & 1, (v >> 3) & 1, (v >> 4) & 1);
    } else {
        ok = edgepointstab(q, plane, work, aux, o, s, s, -s, 1, 0, 0, 0, 0);
    }
    if (ok != 0) {
        SetLayoutClassRootQuaternion(o, q);
        return 1;
    }
    return 0;
}
