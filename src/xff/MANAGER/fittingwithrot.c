typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern Vec4 YUnitVector;
extern void GetMotionNodeBasePos(Vec4 *, void *, void *, int);
extern void *ClipCollisionFinder(void *, Vec4 *, Vec4 *, void *);
extern void GetDifferencialQuaternionWithNoRegularize(Vec4 *, Vec4 *, Vec4 *, Vec4 *);
extern void GetMotionNodeParentBaseQuaternion(Vec4 *, void *, void *, int);

static inline void applyMtx(Vec4 *out, Vec4 *m, Vec4 *v)
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

static inline void addXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void subXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void scale4(Vec4 *out, Vec4 *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(v), "r"(s) : "memory");
}

static inline void normalize(Vec4 *out, Vec4 *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(v) : "memory");
}

static inline void conj(Vec4 *out, Vec4 *q)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void quatMul(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
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
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

void fittingwithrot(Vec4 *qs, Vec4 *rq, Vec4 *ofs, void *mot, int node, int idx, Vec4 *mtx, Vec4 *dir, Vec4 *range, float *h, void *opt)
{
    Vec4 base;
    Vec4 sum;
    Vec4 lo;
    Vec4 hi;
    Vec4 local;
    Vec4 col[5];
    Vec4 tmp;
    Vec4 ndir;
    Vec4 dq;
    Vec4 crq;
    Vec4 r;
    Vec4 pq;
    Vec4 cpq;

    GetMotionNodeBasePos(&base, mot, qs, node);
    applyMtx(&local, mtx, &base);
    addXYZ(&sum, ofs, &local);
    addXYZ(&hi, &sum, range);
    subXYZ(&lo, &sum, range);
    if (ClipCollisionFinder(col, &hi, &lo, opt)) {
        scale4(&tmp, dir, base.f[1] + h[1]);
        addXYZ(&col[4], &tmp, &col[4]);
        subXYZ(&col[4], &col[4], ofs);
        normalize(&col[4], &col[4]);
        normalize(&ndir, &local);
        GetDifferencialQuaternionWithNoRegularize(&dq, &col[4], &ndir, &YUnitVector);
        GetMotionNodeParentBaseQuaternion(&pq, mot, qs, idx);
        conj(&cpq, &pq);
        conj(&crq, rq);
        quatMul(&r, &cpq, &crq);
        quatMul(&r, &r, &dq);
        quatMul(&r, &r, rq);
        quatMul(&r, &r, &pq);
        quatMul(&qs[idx], &r, &qs[idx]);
    }
}
