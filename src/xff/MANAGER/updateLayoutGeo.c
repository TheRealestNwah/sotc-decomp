/* Parked: 21 diffs. The quaternion temporaries and the position pointer land in swapped callee-saved registers ($fp/$s7), and the matrix stores use $sp instead of a copied base register. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { float f[4]; s128 q; } Vec4;

extern char *GetLayoutClass(void *);
extern void GetMotionNodeQuaternionPosToolCoord(Vec4 *, Vec4 *, void *, int, int);
extern void UpdateLayoutClassPastSimpleGeometry(char *);
extern void UpdateLayoutClassSimpleGeometry(char *, float);
extern void SetLayoutClassScaleElem(char *, Vec4 *, int);

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

static inline void normalize(void *v)
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
                         : : "r"(v) : "memory");
}
static inline void scaleMul(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void getNode(Vec4 *m, Vec4 *q, Vec4 *p, void *target, int node)
{
    GetMotionNodeQuaternionPosToolCoord(q, p, target, node, 1);
    quatMatrix(m, q, p);
}

void updateLayoutGeo(char *lc0, void *target, int node, Vec4 *geo, float f)
{
    register char *lc asm("$21") = lc0;
    Vec4 m[4];
    Vec4 q;
    Vec4 p;
    Vec4 s;
    register Vec4 *pos1 asm("$19") = geo + 1;
    Vec4 *rot2 = geo + 2;
    register Vec4 *rq asm("$18");
    Vec4 *pos;
    Vec4 *mtx;
    char *l;

    UpdateLayoutClassPastSimpleGeometry(lc);
    rq = *(Vec4 **)(lc + 0x13C);
    pos = *(Vec4 **)(lc + 0x134);
    l = GetLayoutClass(target);
    geo = &q;
    mtx = m;
    if (node >= 0 && (node <= 0 || !(node & 0x10000))) {
        geo = *(Vec4 **)(l + 0x154) + node;
        mtx = *(Vec4 **)(l + 0x15C) + node * 4;
    } else {
        getNode(mtx, geo, &p, target, node);
    }
    quatMul(rq, geo, rot2);
    normalize(rq);
    applyMatrix(pos, mtx, pos1);
    scaleMul(&s, GetLayoutClass(target) + 0x90, pos1 + 2);
    SetLayoutClassScaleElem(lc, &s, 1);
    UpdateLayoutClassSimpleGeometry(lc, f);
}
#endif
