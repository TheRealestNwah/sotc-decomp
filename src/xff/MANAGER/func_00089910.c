typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char *GetCharacterClass(int);
extern char *GetLayoutClass(int);
extern int ClipCollisionVariableXZSurface(Vec4 *, void *, void *, void *);
extern int ClipCollisionDirectCallBack(Vec4 *, void *, void *, void *, int, int, int, int (*)(), int);
extern void SetQuaternionByAxisRotateVWithNoRegularize(Vec4 *, int, float *);
extern void *GetGeometryPointerSurfacePlane(Vec4 *);
extern void GetPlaneFittingVector(Vec4 *, void *, Vec4 *);
extern void GetQuaternionByAxisDirZY(Vec4 *, void *, Vec4 *);
extern void GetGeometryPointerPosition(Vec4 *, Vec4 *);
extern void SetGeometryPointerNodePosState(Vec4 *, int, int, float *, float *);
extern void ForceParentLayoutObj(int, Vec4 *);
extern void ExecEff(int, int, int, int, Vec4 *);
extern void ForceDeleteLayoutObjChildLink(int);
extern int func_00091500();
extern float XUnitVector[4];
extern float IdentityQuaternion[4];
extern float ZeroPoint[4];

static inline void quatPosMatrix(void *m, void *q, void *p)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf00, vf00w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf00\n"
                         "vmr32.w vf15, vf00\n"
                         "vmr32.w vf16, vf00\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf00, vf00\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf00, vf00\n"
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
                         "lqc2 vf4, 0x0(%2)\n"
                         "vmove.w vf4, vf00\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(m), "r"(q), "r"(p) : "memory");
}

static inline void quatMul(void *out, void *a, void *b)
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

static inline void localDirX(void *out, void *quaternion)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)
"
        "vmul.xyzw vf5, vf4, vf4
"
        "vmr32.xyzw vf6, vf4
"
        "vmul.xyzw vf7, vf6, vf4
"
        "vmr32.xyzw vf6, vf6
"
        "vmul.xyzw vf8, vf6, vf4
"
        "vsubz.x vf6, vf7, vf7z
"
        "vaddx.y vf6, vf0, vf6x
"
        "vsuby.x vf6, vf0, vf5y
"
        "vsubz.x vf6, vf6, vf5z
"
        "vaddw.z vf6, vf8, vf8w
"
        "vsub.w vf6, vf6, vf6
"
        "vsub.w vf6, vf0, vf0
"
        "vadd.w vf5, vf0, vf0
"
        "vmulw.xyz vf6, vf6, vf5w
"
        "vaddw.x vf6, vf6, vf0w
"
        "sqc2 vf6, 0x0(%0)
"
        : : "r"(out), "r"(quaternion) : "memory");
}

/* Parked: 3 diffs, same size. Empty asms order the call setup: XUnitVector
 * and 0x4000 first, then IdentityQuaternion (tied to n so it isn't loaded
 * earlier), then &tq. The rotation pointer is read before
 * SetQuaternionByAxisRotateVWithNoRegularize so it lives in s1, as the Original does.
 * Remaining: the Original's lui of IdentityQuaternion comes after the
 * geo store's sq; ours is hoisted above addiu a2 / a1 = 0x4000. */
#ifdef NONMATCHING
static int func_00089910(int e0, int e1, int chr, int layout, int e2, int flag, void *coll, Vec4 *quat, void *gp, float r)
{
    Vec4 geo[5];
    Vec4 tq;
    Vec4 gp2[4];
    char *cc;
    char *lc;
    float *st;
    void *surf;
    void *plane;
    Vec4 *rot;
    int hit;

    cc = GetCharacterClass(chr);
    if (cc != 0) {
        hit = 0;
        lc = GetLayoutClass(layout);
        st = (float *)(lc + 0x90);
        if (r > 9.99999902e-05f) {
            surf = *(char **)(cc + 0xE38) + *(short *)(cc + 0x372) * 4;
            if (ClipCollisionVariableXZSurface(geo, coll, gp, surf)) {
                (*(Vec4 **)(lc + 0x134))->q = geo[4].q;
                {
                    float *iq;
                    Vec4 *t = &tq;
                    void *xa = XUnitVector;
                    int n = 0x4000;
                    __asm__ ("" : "+r"(xa), "+r"(n));
                    iq = IdentityQuaternion;
                    __asm__ ("" : "+r"(iq) : "r"(n));
                    __asm__ ("" : "+r"(t) : "r"(iq));
                    rot = *(Vec4 **)(lc + 0x13C);
                    SetQuaternionByAxisRotateVWithNoRegularize(t, n, xa);
                    quatMul(rot, iq, &tq);
                }
                hit = 1;
            } else if (flag == 0) {
                if (ClipCollisionDirectCallBack(geo, coll, gp, surf, 0, 0, 0, func_00091500, 0)) {
                    plane = GetGeometryPointerSurfacePlane(geo);
                    localDirX(&tq, quat);
                    hit = 1;
                    GetPlaneFittingVector(&tq, plane, &tq);
                    GetQuaternionByAxisDirZY(*(Vec4 **)(lc + 0x13C), plane, &tq);
                    GetGeometryPointerPosition(*(Vec4 **)(lc + 0x134), geo);
                }
            }
        }
        if (hit) {
            quatPosMatrix(*(Vec4 **)(lc + 0x158), *(Vec4 **)(lc + 0x13C), *(Vec4 **)(lc + 0x134));
            if (*st != 1.0f) {
                SetGeometryPointerNodePosState(gp2, layout, 0, IdentityQuaternion, ZeroPoint);
                ForceParentLayoutObj(layout, geo);
                ExecEff(e1, layout, e2, e0, gp2);
                *st = 1.0f;
            }
        } else if (*st == 1.0f) {
            ForceDeleteLayoutObjChildLink(layout);
            *st = 0.0f;
        }
    }
    return 0;
}
#endif
