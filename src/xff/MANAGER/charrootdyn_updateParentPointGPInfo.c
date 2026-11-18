typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern Vec4 ZeroPoint;
extern Vec4 ZeroVector;
extern int ClipCollisionFinderCallBack(void *, Vec4 *, Vec4 *, char *, int (*)(), int);
extern int func_00064660();
extern Vec4 D_00136B20;

static inline void quatPosToMatrix(Vec4 *m, Vec4 *qp, Vec4 *pos)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%2)\n"
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
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         "lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(m), "r"(pos), "r"(qp));
}

static inline void matrixApply(Vec4 *out, Vec4 *m, Vec4 *v)
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

static inline void quatDirZ(Vec4 *out, Vec4 *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
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
        : : "r"(out), "r"(q));
}

extern void GetGeometryPointerPosition(Vec4 *, char *);
extern Vec4 *GetGeometryPointerSurfacePlane(char *);
extern void GetGeometryPointerSurfaceAttribute(long *, char *);
extern float GetPlaneSlopeDegree(Vec4 *);
extern void GetPlaneZTopYPlaneCoordQuaternion(Vec4 *, Vec4 *);
extern float GetTurnYAngleFromGlobalDir(Vec4 *, Vec4 *);
extern int func_000599B8(void *, void *, int, void *, void *, float, float, void *);
extern void *func_00059EA0(void *, void *);

static inline int climb(char *p, void *a, int b, void *c, void *d, void *e, float x, float y, float r, float h)
{
    int found;
    void *other;
    *(float *)(p + 0x38) = y;
    *(float *)(p + 0x3C) = x;
    *(int *)(p + 0x20) = 0;
    *(int *)(p + 0x80) = 0;
    *(float *)(p + 0x8C) = h;
    found = func_000599B8(p, a, b, c, d, r, h, e);
    if (found == 0) {
        other = func_00059EA0(a, e);
        if (other != 0)
            found = func_000599B8(p, other, b, c, d, r, h, e);
    }
    return found;
}

void charrootdyn_updateParentPointGPInfo(char *o)
{
    Vec4 hit[5]; Vec4 v; Vec4 from; Vec4 to; Vec4 off; Vec4 matrix[4];
    Vec4 gpPos; Vec4 q; Vec4 dir; Vec4 pos; long attr;
    char *gp = o + 0xC0;
    Vec4 *hp = hit;
    Vec4 *plane;
    Vec4 *qp;
    Vec4 *src;
    Vec4 *base = *(Vec4 **)(o + 0x138);
    Vec4 *cur = *(Vec4 **)(o + 0x134);
    Vec4 *rot = *(Vec4 **)(o + 0x13C);
    register Vec4 *mp __asm__("$3") = matrix;
    quatPosToMatrix(mp, rot, cur);
    { register Vec4 *dp __asm__("$2") = &D_00136B20;
    dp->f[0] = 0.0f;
    dp->f[2] = 0.0f;
    matrixApply(&off, matrix, dp); }
    addXYZ(&from, base, &off);
    v.q = ZeroPoint.q;
    v.f[1] = -*(float *)(o + 0xE34);
    matrixApply(&to, matrix, &v);
    addXYZ(&to, &to, &off);
    if (ClipCollisionFinderCallBack(hp, &from, &to, o + 0xE20, func_00064660, 0)) {
        GetGeometryPointerPosition(&gpPos, gp);
        if (hit[4].f[1] > gpPos.f[1])
            gp = (char *)hit;
    }
    plane = GetGeometryPointerSurfacePlane(gp);
    GetGeometryPointerSurfaceAttribute(&attr, gp);
    *(long *)(o + 0x690) = attr;
    *(long *)(o + 0x698) = attr;
    *(float *)(o + 0x6B4) = GetPlaneSlopeDegree(plane);
    qp = *(Vec4 **)(o + 0x13C);
    *(s128 *)(o + 0x6A0) = plane->q;
    GetPlaneZTopYPlaneCoordQuaternion(&q, plane);
    { Vec4 *dp = &dir; quatDirZ(dp, qp);
    *(float *)(o + 0x6BC) = GetTurnYAngleFromGlobalDir(&q, dp); }
    src = *(Vec4 **)(o + 0x134);
    pos.q = src->q;
    climb(o + 0x5F0, gp, 1, &pos, src, o + 0xE20, 100.0f, *(float *)(o + 0xE34), 0.5f, 0.0f);
}
