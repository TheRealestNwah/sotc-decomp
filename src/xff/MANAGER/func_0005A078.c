typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern void *GetCollisionDBPlane(void *);
extern void GetCollisionEdgePointerVertexPoint(void *, void *);
extern void CompletePlaneD(void *, void *);
extern float GetPointDistanceFromPlane(void *, void *);
extern float GetPointDistanceSquareFromUnnormalizedPlane(void *, void *);
extern void GetPlaneFittingPointForUnnormalizedPlane(void *, void *, void *);
extern int GetCollisionEdgePointerOtherSideCollisionEdge(void *, void *);
extern int ClipCollisionFinder(void *, void *, void *, int);
extern void GetGeometryPointerWithCollisionEdgeGlobalPoint(void *, void *, void *, unsigned);

static inline void subXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
        "lqc2 vf6, 0x0(%2)\n"
        "vsub.xyz vf5, vf5, vf6\n"
        "sqc2 vf5, 0x0(%0)\n" : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void sub4(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
        "lqc2 vf6, 0x0(%2)\n"
        "vsub.xyzw vf7, vf5, vf6\n"
        "sqc2 vf7, 0x0(%0)\n" : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float distSq(void *a, void *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
        "lqc2 vf6, 0x0(%2)\n"
        "vsub.xyzw vf7, vf5, vf6\n"
        "vmul.xyz vf7, vf7, vf7\n"
        "vaddy.x vf7, vf7, vf7y\n"
        "vaddz.x vf7, vf7, vf7z\n"
        "qmfc2.ni $2, vf7\n"
        "mtc1 $2, %0\n" : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline float lenSq(void *a)
{
    float d;

    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
        "vmul.xyz vf7, vf7, vf7\n"
        "vaddy.x vf7, vf7, vf7y\n"
        "vaddz.x vf7, vf7, vf7z\n"
        "qmfc2.ni $2, vf7\n"
        "mtc1 $2, %0\n" : "=f"(d) : "r"(a) : "$2");
    return d;
}

static inline void scaleXYZ(void *out, void *in, float f)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
        "qmtc2.ni %2, vf6\n"
        "vmulx.xyz vf5, vf5, vf6x\n"
        "sqc2 vf5, 0x0(%0)\n" : : "r"(out), "r"(in), "r"(f) : "memory");
}

static inline void scale4(void *out, void *in, float f)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
        "qmtc2.ni %2, vf6\n"
        "vmulx.xyzw vf5, vf5, vf6x\n"
        "sqc2 vf5, 0x0(%0)\n" : : "r"(out), "r"(in), "r"(f) : "memory");
}

static inline void cross(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
        "lqc2 vf6, 0x0(%2)\n"
        "vopmula.xyz ACC, vf5, vf6\n"
        "vopmsub.xyz vf7, vf6, vf5\n"
        "vsub.w vf7, vf7, vf7\n"
        "sqc2 vf7, 0x0(%0)\n" : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void normalizeXYZ(void *output, void *input)
{
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
        : : "r"(output), "r"(input) : "memory");
}

static inline void addXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
        "lqc2 vf6, 0x0(%2)\n"
        "vadd.xyz vf5, vf5, vf6\n"
        "sqc2 vf5, 0x0(%0)\n" : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void applyMatrix(void *out, void *m, void *v)
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
        "sqc2 vf10, 0x0(%0)\n" : : "r"(out), "r"(m), "r"(v) : "memory");
}

static int func_0005A078(char *obj, void *edge, void *db, Vec4 *pos, int arg4, void *arg5, void *mtx)
{
    Vec4 p;
    Vec4 pl2;
    Vec4 pl;
    Vec4 *e[4];
    Vec4 w[8];
    Vec4 a[5];
    void *n;
    void *n2;
    float d;
    Vec4 *v0;
    Vec4 *v1;
    Vec4 *pn;
    Vec4 *pq;
    Vec4 *pa;
    Vec4 *pb;
    Vec4 *pp;
    float s;
    Vec4 *ppl;
    Vec4 *ppl2;

    n = GetCollisionDBPlane(edge);
    GetCollisionEdgePointerVertexPoint(e, edge);
    v0 = e[0];
    v1 = e[1];
    ppl = &pl;
    subXYZ(ppl, v1, v0);
    ppl2 = &pl2;
    CompletePlaneD(ppl, v1);
    d = 0.0f;
    if (GetPointDistanceFromPlane(ppl, pos) > 0.0f) {
        d = distSq(v1, pos);
        p.q = v1->q;
    } else {
        scaleXYZ(ppl2, ppl, -1.0f);
        CompletePlaneD(ppl2, v0);
        if (GetPointDistanceFromPlane(ppl2, pos) > 0.0f) {
            d = distSq(v0, pos);
            p.q = v0->q;
        } else {
            sub4(&w[1], pos, v0);
            cross(&w[0], ppl, &w[1]);
            if (lenSq(&w[0]) < 0.001f) {
                p.q = pos->q;
            } else {
                cross(&w[0], &w[0], ppl);
                CompletePlaneD(&w[0], v0);
                d = GetPointDistanceSquareFromUnnormalizedPlane(&w[0], pos);
                GetPlaneFittingPointForUnnormalizedPlane(&p, &w[0], pos);
            }
        }
    }
    if (mtx) {
        applyMatrix(&w[0], mtx, &p);
        if (w[0].f[2] <= 0.1f)
            return 0;
    }
    if (d < *(float *)(obj + 0x98) && GetCollisionEdgePointerOtherSideCollisionEdge(&w[1], edge)) {
    n2 = GetCollisionDBPlane(&w[1]);
    pn = &w[2];
    normalizeXYZ(pn, ppl);
    pq = &w[3];
    pa = &w[4];
    pb = &w[5];
    pp = &p;
    s = 0.1f;
    addXYZ(pq, n, n2);
    normalizeXYZ(pq, pq);
    scale4(pq, pq, s);
    addXYZ(pq, pp, pq);
    cross(pa, n, pn);
    scale4(pa, pa, s);
    scale4(&w[6], n, s);
    addXYZ(pa, pa, &w[6]);
    addXYZ(pa, pp, pa);
    cross(pb, pn, n2);
    scale4(pb, pb, s);
    scale4(&w[7], n2, s);
    addXYZ(pb, pb, &w[7]);
    addXYZ(pb, pp, pb);
        if (!ClipCollisionFinder(a, pa, pq, arg4) && !ClipCollisionFinder(a, pq, pb, arg4)) {
            *(float *)(obj + 0x98) = d;
            GetGeometryPointerWithCollisionEdgeGlobalPoint(obj + 0x40, &w[1], &p, 0);
            *(int *)(obj + 0x20) = 1;
            return 1;
        }
    }
    return 0;
}
