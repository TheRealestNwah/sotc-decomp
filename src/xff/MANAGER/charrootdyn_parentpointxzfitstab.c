/*
 * charrootdyn_parentpointxzfitstab: Parked attempt, 20 differing words of 347.
 * Remaining differences:
 * - Both slope-limit fitting calls: the Original sets $f13 (mov.s from $f12)
 *   before $a3; this C sets it last.
 * - charrootdyn_getGPRelativePositionWithQ call: the Original sets $a0 before $a3.
 * - The Original keeps &mat in $a0 through the matrix/inverse blocks; this C
 *   uses $a3 (0x3C4-0x520).
 */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { char data[0x50]; } GeometryPointer;

typedef struct DldType { char pad[0xC]; int size; } DldType;
typedef struct DldTable { char pad[8]; DldType *type; char pad2[4]; char *data; } DldTable;
extern int DldSysUndefSymbol;

extern void charrootdyn_getForceNoLimitMode(void *, void *);
extern void charrootdyn_getLimitMode(void *, void *);
extern int charrootdyn_getCompleteFittingYQFromStabGPWithSlopeLimit(void *, void *, void *, void *, void *, float, float);
extern void charrootdyn_getCompleteFittingYQFromYDir(void *, void *, void *);
extern void *GetGeometryPointerSurfacePlane(void *);
extern void SetLayoutClassRootQuaternion(void *, void *);
extern void charrootdyn_getLocalOffsetFromParentGP(void *, void *, void *, void *);
extern void GetGeometryPointerPosition(void *, void *);
extern void GetGeometryPointerQuaternion(void *, void *);
extern int charrootdyn_getCyclicCollisionDetectZY(void *, void *, void *, int, void *, float);
extern void charrootdyn_getGPRelativePositionWithQ(void *, void *, void *, void *);
extern void DivQuaternion(void *, void *, void *);

static float D_00136BA0[4] __attribute__((aligned(16))) = { 0.0f, 0.0f, 0.0f, 1.0f };
static float D_00136BB0[4] __attribute__((aligned(16))) = { 0.0f, 0.0f, 0.0f, 1.0f };

static inline void *dldElement(int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + (((unsigned int)*h >> 18) & 0xFFF) * t->type->size : 0;
}

static inline void quatNormalize(Vec4 *q)
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

static inline void quatMul(Vec4 *out, Vec4 *a, Vec4 *b)
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
                         : : "r"(a), "r"(b), "r"(out) : "memory");
}

#define QUAT_MATRIX_BODY \
    "vaddw.xyz vf12, vf0, vf0w\n" \
    "lqc2 vf11, 0x0(%1)\n" \
    "vmr32.w vf14, vf0\n" \
    "vmr32.w vf15, vf0\n" \
    "vmr32.w vf16, vf0\n" \
    "vopmula.xyz ACC, vf11, vf12\n" \
    "vmadd.xyz vf11, vf0, vf0\n" \
    "vmadd.xyz vf10, vf11, vf12\n" \
    "vmul.xyz vf13, vf11, vf10\n" \
    "vopmula.xyz ACC, vf11, vf10\n" \
    "vmaddw.xyz vf15, vf10, vf11w\n" \
    "vmsubw.xyz vf16, vf10, vf11w\n" \
    "vopmula.xyz ACC, vf13, vf12\n" \
    "vmadd.xyz vf17, vf13, vf12\n" \
    "vopmula.xyz ACC, vf15, vf12\n" \
    "vmadd.xyz vf15, vf0, vf0\n" \
    "vsub.xyz vf14, vf12, vf17\n" \
    "vmove.yz vf17, vf14\n" \
    "vmove.y vf14, vf16\n" \
    "vmove.y vf16, vf15\n" \
    "vmove.y vf15, vf17\n" \
    "vmove.z vf14, vf15\n" \
    "vmove.z vf15, vf16\n" \
    "vmove.z vf16, vf17\n"

static inline void quatRotate(Vec4 *out, Vec4 *q, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n" : : "r"(v));
    __asm__ __volatile__(QUAT_MATRIX_BODY
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void vecAdd(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatPosMatrix(Vec4 *out, Vec4 *q, Vec4 *pos)
{
    __asm__ __volatile__(QUAT_MATRIX_BODY
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(out), "r"(pos) : "memory");
}

#define VU_INVERSE_MATRIX(dst, src) \
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n" \
                         "vsubw.x vf25, vf0, vf0w\n" \
                         "vmulx.xyz vf28, vf24, vf25x\n" \
                         "vsub.w vf28, vf28, vf28\n" \
                         "lq $8, 0x0(%1)\n" \
                         "lq $9, 0x10(%1)\n" \
                         "lq $10, 0x20(%1)\n" \
                         "qmfc2 $11, vf0\n" \
                         "pextlw $12, $9, $8\n" \
                         "pextuw $13, $9, $8\n" \
                         "pextlw $14, $11, $10\n" \
                         "pextuw $15, $11, $10\n" \
                         "pcpyld $8, $14, $12\n" \
                         "pcpyud $9, $12, $14\n" \
                         "pcpyld $10, $15, $13\n" \
                         "pcpyud $11, $13, $15\n" \
                         "qmtc2 $8, vf24\n" \
                         "qmtc2 $9, vf25\n" \
                         "qmtc2 $10, vf26\n" \
                         "vmulax.xyzw ACC, vf24, vf28x\n" \
                         "vmadday.xyzw ACC, vf25, vf28y\n" \
                         "vmaddaz.xyzw ACC, vf26, vf28z\n" \
                         "vmaddw.xyzw vf29, vf0, vf28w\n" \
                         "vsub.w vf29, vf29, vf29\n" \
                         "vadd.w vf29, vf29, vf0\n" \
                         "sqc2 vf24, 0x0(%0)\n" \
                         "sqc2 vf25, 0x10(%0)\n" \
                         "sqc2 vf26, 0x20(%0)\n" \
                         "sqc2 vf29, 0x30(%0)\n" \
                         : : "r"(dst), "r"(src) \
                         : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory")

static inline void matApply(Vec4 *out, Vec4 *m, Vec4 *v)
{
    __asm__ __volatile__("lqc2 vf8, 0(%2)\n"
                         "lqc2 vf14, 0(%1)\n"
                         "lqc2 vf15, 16(%1)\n"
                         "lqc2 vf16, 32(%1)\n"
                         "lqc2 vf17, 48(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0(%0)\n"
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

static void charrootdyn_parentpointxzfitstab(char *cls, char *node, Vec4 *keep)
{
    Vec4 q;
    int lim[4];
    GeometryPointer g;
    Vec4 pos;
    Vec4 gq;
    Vec4 off;
    Vec4 mat[4];
    Vec4 rel;
    Vec4 inv[4];
    unsigned int *attr;
    char *gp;
    Vec4 *bq;
    float slope;
    float y;
    int (*fn)(void *);

    gp = cls + 0xC0;
    slope = *(float *)(cls + 0x40C);
    attr = dldElement((int *)(node + 0xC));
    if (attr != 0 && (*attr >> 2) & 1) {
        charrootdyn_getForceNoLimitMode(lim, cls);
    } else {
        charrootdyn_getLimitMode(lim, cls);
    }
    q.q = (*(Vec4 **)(cls + 0x13C))->q;
    if (attr != 0) {
        if (*attr & 1) {
            charrootdyn_getCompleteFittingYQFromStabGPWithSlopeLimit(&q, gp, cls + 0xE20, &q, lim, slope, slope);
            goto normalize;
        }
        if ((*attr >> 1) & 1) {
            charrootdyn_getCompleteFittingYQFromYDir(&q, GetGeometryPointerSurfacePlane(gp), &q);
        normalize:
            quatNormalize(&q);
            SetLayoutClassRootQuaternion(cls, &q);
            if (keep != 0) {
                charrootdyn_getLocalOffsetFromParentGP(cls + 0x6D0, &q, *(void **)(cls + 0x134), gp);
            }
            return;
        }
    }
    GetGeometryPointerPosition(&pos, gp);
    bq = (Vec4 *)(cls + 0xB40);
    GetGeometryPointerQuaternion(&gq, gp);
    if (keep != 0) {
        ((Vec4 *)(cls + 0x6D0))->q = keep->q;
    } else {
        quatMul(&q, &gq, bq);
    }
    D_00136BA0[0] = *(float *)(cls + 0x6D0);
    quatRotate(&off, &q, D_00136BA0);
    vecAdd(&pos, &pos, &off);
    if (!charrootdyn_getCyclicCollisionDetectZY(&g, &pos, &q, 4, cls + 0xE20, *(float *)(cls + 0x6D8))) {
        return;
    }
    if (attr != 0 && (*attr >> 3) & 1) {
        fn = *(int (**)(void *))(cls + 0xC30);
        if (fn != 0 && !fn(&g)) {
            charrootdyn_getForceNoLimitMode(lim, cls);
        }
    }
    charrootdyn_getCompleteFittingYQFromYDir(&q, GetGeometryPointerSurfacePlane(&g), &q);
    charrootdyn_getCompleteFittingYQFromStabGPWithSlopeLimit(&q, &g, cls + 0xE20, &q, lim, slope, slope);
    quatNormalize(&q);
    SetLayoutClassRootQuaternion(cls, &q);
    {
        float m = 0.01f;
        y = *(float *)(cls + 0x6D4);
        if (!(m < y)) {
            y = m;
        }
    }
    *(float *)(cls + 0x6D4) = y;
    D_00136BB0[1] = y;
    charrootdyn_getGPRelativePositionWithQ(&rel, &g, &q, D_00136BB0);
    quatPosMatrix(mat, &q, &rel);
    if (keep != 0) {
        VU_INVERSE_MATRIX(inv, mat);
        matApply((Vec4 *)(cls + 0xB30), inv, *(Vec4 **)(cls + 0x134));
        DivQuaternion(bq, &q, &gq);
    } else {
        matApply(*(Vec4 **)(cls + 0x134), mat, (Vec4 *)(cls + 0xB30));
    }
}

#endif
