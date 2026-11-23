typedef int s128 __attribute__((mode(TI)));
typedef union { float f[4]; s128 q; } Vec4;

extern char *GetLayoutClass(void *);
extern void GetMotionNodeQuaternionPosToolCoord(Vec4 *, Vec4 *, void *, int, int);

static inline int isExtendId(int id)
{
    int ret = 0;
    if (id > 0) {
        if (id & 0x10000) ret = 1;
    }
    return ret;
}

static inline void vecMul(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void quatMatrix(void *dst0, void *q, void *t)
{
    register void *dst __asm__("$3") = dst0;
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
                         : : "r"(dst0), "r"(q) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(dst), "r"(t) : "memory");
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

static inline void quatNormalize(void *dst, void *a)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(dst), "r"(a) : "memory");
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

static inline void calcNodeCoord(Vec4 *offv, Vec4 *pos, Vec4 *rot, void *target, int node, void *offq, Vec4 *dst, Vec4 *src)
{
    Vec4 m[4];
    Vec4 q;
    Vec4 p;
    Vec4 *mtx;
    Vec4 *quat;
    char *l = GetLayoutClass(target);

    if (node >= 0 && (node <= 0 || !(node & 0x10000))) {
        quat = *(Vec4 **)(l + 0x154) + node;
        mtx = *(Vec4 **)(l + 0x15C) + node * 4;
    } else {
        quat = &q;
        GetMotionNodeQuaternionPosToolCoord(&q, &p, target, node, 1);
        mtx = m;
        quatMatrix(mtx, &q, &p);
    }
    quatMul(rot, quat, offq);
    quatNormalize(rot, rot);
    applyMatrix(pos, mtx, offv);
    dst->q = src->q;
}

void update_camera_region_geometry(void *obj, void *target, int node, char *param, int type)
{
    Vec4 v;
    Vec4 s;
    Vec4 scale = {{1.0f, 1.0f, 1.0f, 1.0f}};
    char *lc;

    lc = GetLayoutClass(obj);
    if (target != 0) {
        char *l = GetLayoutClass(target);
        if (l != 0)
            scale.q = ((Vec4 *)(l + 0x90))->q;
    }
    switch (type) {
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2A:
        v.q = ((Vec4 *)(param + 0x10))->q;
        vecMul(&s, param + 0x30, &scale);
        calcNodeCoord(&v, *(Vec4 **)(lc + 0x134), *(Vec4 **)(lc + 0x13C), target, node, param + 0x20, (Vec4 *)(lc + 0x90), &s);
        break;
    }
}
