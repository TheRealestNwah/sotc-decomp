/*
 * Parked: 11 diffs, same size.
 * Remaining: target and the 0x134 output pointer swap s3/s4; the second
 * quatMatrix loads 0x13C/0x134 into a0/v1 instead of v1/a0.
 */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { float f[4]; s128 q; } Vec4;

extern char *GetLayoutClass(void *);
extern void GetMotionNodeQuaternionPosToolCoord(Vec4 *, Vec4 *, void *, int, int);
extern void ScanAllTwoWayLink(void *, void *, int);
extern void SetQuaternionByAxisRotateVWithNoRegularize(Vec4 *, int, Vec4 *);
extern void SetGeometryPointerNodePosState(void *, void *, int, Vec4 *, Vec4 *);
extern int kickEffect(int, int, void *, int, void *);
extern int func_00091540();
extern Vec4 XUnitVector;
extern Vec4 IdentityQuaternion;
extern Vec4 ZeroPoint;

static inline void quatMatrix(void *dst0, void *q, void *t)
{
    void *dst = dst0;
    void *qq = q;
    void *tt = t;
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
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
                         : : "r"(dst0), "r"(qq) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(dst), "r"(tt) : "memory");
}
static inline void quatMul(void *dst, void *a, void *b)
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
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}
static inline void applyMatrix(void *dst, void *m, void *v)
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
                         : : "r"(dst), "r"(m), "r"(v) : "memory");
}

static inline void calcNode(Vec4 *out, void *target, int node, Vec4 *v)
{
    Vec4 m[4];
    Vec4 p;
    Vec4 q;
    Vec4 *mtx;
    char *l = GetLayoutClass(target);

    if (node > 0 && !(node & 0x10000)) {
        mtx = *(Vec4 **)(l + 0x15C) + node * 4;
    } else {
        mtx = m;
        GetMotionNodeQuaternionPosToolCoord(&q, &p, target, node, 1);
        quatMatrix(m, &q, &p);
    }
    applyMatrix(out, mtx, v);
}

static inline void setNodePos(void *gp, void *obj, Vec4 *q, Vec4 *p)
{
    Vec4 rq;
    Vec4 rot;
    Vec4 *r = &rq;

    SetQuaternionByAxisRotateVWithNoRegularize(&rot, -0x8000, &XUnitVector);
    quatMul(r, q, &rot);
    SetGeometryPointerNodePosState(gp, obj, 0, r, p);
}

void updateSEGeo(int a0, void *obj, int a2, void *target, int node, Vec4 *geo, int handle, int flag)
{
    char *lc = GetLayoutClass(obj);

    calcNode(*(Vec4 **)(lc + 0x134), target, node, geo);
    quatMatrix(*(void **)(lc + 0x158), *(void **)(lc + 0x13C), *(void **)(lc + 0x134));
    if (flag) {
        char *g = (char *)(geo + 1);
        char b0 = g[0];
        char b2 = g[2];
        if (b0 && b2)
            ScanAllTwoWayLink(lc + 0x10C, func_00091540, g[1]);
        else if (b2)
            ScanAllTwoWayLink(lc + 0x10C, func_00091540, 0);
        else if (b0)
            ScanAllTwoWayLink(lc + 0x10C, func_00091540, 1);
    } else if (((char *)geo)[0x10]) {
        char gp[0x40];

        setNodePos(gp, obj, &IdentityQuaternion, &ZeroPoint);
        kickEffect(handle, a2, target, a0, gp);
    }
}
#else
extern void updateSEGeo();
#endif
