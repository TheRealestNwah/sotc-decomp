#ifdef NONMATCHING /* 110 diffs: frame/word count match (118); saved-register numbering of id/light pointers/out pointers differs. Explicit addiu-from-sp asm for 0x50/sp pointers keeps s7 out */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char *GetLayoutClass(int);
extern void GetMotionNodeQuaternionPosToolCoord(Vec4 *, Vec4 *, int, int, int, char *);

void updateLightGeo(int obj0, int obj1, int id, char *light)
{
    Vec4 buf[6];
    float *p10 = (float *)(light + 0x10);
    float *p20 = (float *)(light + 0x20);
    char *c0;
    char *c1;
    float *out134;
    float *out13c;
    float *quat;
    float *matrix;
    register float *pp __asm__("$2");
    register float *vp __asm__("$3");

    c0 = GetLayoutClass(obj0);
    out134 = *(float **)(c0 + 0x134);
    out13c = *(float **)(c0 + 0x13C);
    c1 = GetLayoutClass(obj1);
    quat = buf[4].f;
    matrix = buf[0].f;
    if (id < 0 || (id > 0 && (id & 0x10000))) {
        GetMotionNodeQuaternionPosToolCoord(&buf[4], &buf[5], obj1, id, 1, c1);
        __asm__ __volatile__("daddu %0, $29, $0" : "=r"(vp));
        __asm__ __volatile__("addiu %0, $29, 0x50" : "=r"(pp));
        __asm__ __volatile__(
            "vaddw.xyz vf12, vf0, vf0w\n"
            "lqc2 vf11, 0x0(%0)\n"
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
            "sqc2 vf14, 0x0(%1)\n"
            "sqc2 vf15, 0x10(%1)\n"
            "sqc2 vf16, 0x20(%1)\n"
            "lqc2 vf4, 0x0(%2)\n"
            "vmove.w vf4, vf0\n"
            "sqc2 vf4, 0x30(%1)\n"
            : : "r"(quat), "r"(matrix), "r"(pp), "r"(vp) : "memory");
    } else {
        matrix = (float *)(*(int *)(c1 + 0x15C) + id * 64);
        quat = (float *)(*(int *)(c1 + 0x154) + id * 16);
    }
    __asm__ __volatile__(
        "lqc2 vf11, 0x0(%0)\n"
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
        "lqc2 vf14, 0x0(%2)\n"
        "vmul.xyzw vf15, vf14, vf14\n"
        "vaddy.x vf15, vf15, vf15y\n"
        "vaddz.x vf15, vf15, vf15z\n"
        "vaddw.x vf15, vf15, vf15w\n"
        "vrsqrt Q, vf0w, vf15x\n"
        "vwaitq\n"
        "vmulq.xyzw vf15, vf14, Q\n"
        "sqc2 vf15, 0x0(%2)\n"
        : : "r"(quat), "r"(p20), "r"(out13c) : "memory");
    __asm__ __volatile__(
        "lqc2 vf8, 0x0(%1)\n"
        "lqc2 vf14, 0x0(%0)\n"
        "lqc2 vf15, 0x10(%0)\n"
        "lqc2 vf16, 0x20(%0)\n"
        "lqc2 vf17, 0x30(%0)\n"
        "vmulax.xyzw ACC, vf14, vf8x\n"
        "vmadday.xyzw ACC, vf15, vf8y\n"
        "vmaddaz.xyzw ACC, vf16, vf8z\n"
        "vmaddw.xyzw vf10, vf17, vf8w\n"
        "sqc2 vf10, 0x0(%2)\n"
        : : "r"(matrix), "r"(p10), "r"(out134) : "memory");
}
#endif
