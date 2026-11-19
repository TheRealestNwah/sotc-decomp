typedef int s128 __attribute__((mode(TI)));
typedef unsigned long long u64;
typedef union { s128 q; float f[4]; } Vec4;

extern float GetYHeightOfPlaneXZProjection(void *, void *);
extern float GetPointDistanceFromPlane(void *, void *);
extern void GetPlaneFittingPoint(void *, void *, void *);
extern void *GetCollisionDBPlane(void *);
extern int ClipCollisionFinder(void *, void *, void *, int);
extern void GetCollisionEdgePointerVertexPoint3(void *, void *);
extern int GetCollisionEdgePointerOtherSideDBData(void *, void *);
extern void CopyCollisionEdge(void *, void *);
extern void GetGeometryPointerWithCollisionEdgeGlobalPoint(void *, void *, void *, unsigned);
extern float iosGetACosfExact(float);
extern u64 *GetCollisionDBAttributeAdr(void *);
extern void GetCollisionDBSurfBoundary(void *, void *);
extern float GetPlaneSlopeDegree(void *);

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

static inline void scaleXYZ(void *v, float f)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
        "qmtc2.ni %1, vf6\n"
        "vmulx.xyz vf5, vf5, vf6x\n"
        "sqc2 vf5, 0x0(%0)\n" : : "r"(v), "r"(f) : "memory");
}

static inline void addXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
        "lqc2 vf6, 0x0(%2)\n"
        "vadd.xyz vf5, vf5, vf6\n"
        "sqc2 vf5, 0x0(%0)\n" : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float vecDot(void *a, void *b)
{
    float dot;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

static int func_00059628(char *obj, void *edge, void *db, void *db2, void *plane, unsigned flag, Vec4 *pos, void *hint, int arg8)
{
    Vec4 p;
    Vec4 nrm;
    Vec4 q;
    Vec4 a[5];
    Vec4 b;
    Vec4 c;
    Vec4 *e[4];
    float rx;
    float rz;
    float dy;
    float d;
    void *n;
    char *dbp;
    float *ang;
    void *pl;
    int ret;

    ret = 0;
    p.q = pos->q;
    rx = *(float *)(obj + 0x38);
    rz = *(float *)(obj + 0x3C);
    p.f[1] = GetYHeightOfPlaneXZProjection(db2, pos);
    dy = p.f[1] - pos->f[1];
    d = ABS(GetPointDistanceFromPlane(plane, pos));
    if (dy * dy + d * d < rx * rx + rz * rz) {
        GetPlaneFittingPoint(&p, plane, &p);
        n = GetCollisionDBPlane(edge);
        normalizeXYZ(&nrm, n);
        scaleXYZ(&nrm, 0.01f);
        addXYZ(&q, &p, &nrm);
        if (ClipCollisionFinder(a, &q, hint, arg8)) {
            GetPlaneFittingPoint(&b, n, hint);
            addXYZ(&c, &b, &nrm);
            if (ClipCollisionFinder(a, &q, &c, arg8)) {
                GetCollisionEdgePointerVertexPoint3(e, edge);
                addXYZ(&q, e[2], &nrm);
                if (ClipCollisionFinder(a, &q, &c, arg8))
                    return 0;
            }
        }
        dbp = obj + 0x84;
        if (!GetCollisionEdgePointerOtherSideDBData(dbp, edge))
            return 0;
        CopyCollisionEdge(obj + 0x24, edge);
        GetGeometryPointerWithCollisionEdgeGlobalPoint(obj + 0x40, edge, &p, flag >> 31);
        if (GetCollisionEdgePointerOtherSideDBData(dbp, edge)) {
            *(int *)(obj + 0x80) = 1;
            ang = (float *)(obj + 0x8C);
            pl = GetCollisionDBPlane(dbp);
            *ang = iosGetACosfExact(vecDot(GetCollisionDBPlane(db), pl)) * 57.29578f;
            *(u64 *)(obj + 0x90) = *GetCollisionDBAttributeAdr(dbp);
            GetCollisionDBSurfBoundary(a, db);
            if (GetPointDistanceFromPlane(pl, a) >= 0.0f)
                *ang = 6.2831852f - *ang;
            *ang = -(*ang - 90.0f);
        }
        *(s128 *)obj = pos->q;
        GetPlaneFittingPoint(obj + 0x10, plane, pos);
        *(float *)(obj + 0x38) = dy;
        *(float *)(obj + 0x3C) = d;
        *(int *)(obj + 0x20) = 1;
        ret = 1;
        *(float *)(obj + 0x34) = GetPlaneSlopeDegree(db2);
    }
    return ret;
}
