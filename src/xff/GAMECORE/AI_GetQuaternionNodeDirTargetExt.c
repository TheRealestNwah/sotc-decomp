typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char ZUnitVector[];
extern char YUnitVector[];
extern char YUnitVectorInv[];
extern void SetQuaternionByCosineAxisRotateVWithNoRegularize(float, void *, void *);
extern int AI_GetQuaternionNodeDirTarget(void *, void *, int, int, void *);

static inline void quatRotateVector(Vec4 *out0, float *quat0, Vec4 *vec0)
{
    register Vec4 *vec __asm__("$2") = vec0;
    register Vec4 *out __asm__("$4") = out0;
    register float *quat __asm__("$3") = quat0;
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
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
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         : : "r"(vec), "r"(quat));
    __asm__ __volatile__("sqc2 vf10, 0x0(%0)\n" : : "r"(out) : "memory");
}


static inline void quatRotateVector2(Vec4 *out0, float *quat0, Vec4 *vec0)
{
    Vec4 *vec = vec0;
    register Vec4 *out __asm__("$3") = out0;
    register float *quat __asm__("$2") = quat0;
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
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
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         : : "r"(vec), "r"(quat));
    __asm__ __volatile__("sqc2 vf10, 0x0(%0)\n" : : "r"(out) : "memory");
}



int AI_GetQuaternionNodeDirTargetExt(char *outq0, char *pos0, int a20, int a30, char *dir)
{
    register char *pos __asm__("$16") = pos0;
    register char *outq __asm__("$17") = outq0;
    register char *dv __asm__("$18");
    register int a2 __asm__("$19") = a20;
    register int a3 __asm__("$20") = a30;
    char sp[0x50] __attribute__((aligned(16)));
    float d;
    int r;
    register char *p40 __asm__("$4");

    __asm__("" : "+r"(pos), "+r"(outq));
    __asm__("" : "+r"(a2), "+r"(a3));
    dv = sp + 0x20;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vsub.xyz vf5, vf5, vf6
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(dv), "r"(dir), "r"(pos) : "memory");
    p40 = sp + 0x40;
    *(s128 *)(sp + 0x40) = *(s128 *)(sp + 0x20);
    __asm__ __volatile__("" : : : "memory");
    *(int *)(sp + 0x44) = 0;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "vmul.xyz vf7, vf5, vf5
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         "vrsqrt Q, vf0w, vf7w
"
                         "vwaitq
"
                         "vmulq.xyz vf5, vf5, Q
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(p40) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vaddw.x vf7, vf0, vf0w
"
                         "vmul.xyz vf6, vf5, vf6
"
                         "vaddax.x ACC, vf0, vf6x
"
                         "vmadday.x ACC, vf7, vf6y
"
                         "vmaddz.x vf6, vf7, vf6z
"
                         "qmfc2.ni $2, vf6
"
                         "mtc1 $2, %0
"
                         : "=f"(d) : "r"(sp + 0x40), "r"(ZUnitVector) : "$2");
    if (*(float *)(sp + 0x40) <= 0.0f)
        SetQuaternionByCosineAxisRotateVWithNoRegularize(d, sp, YUnitVector);
    else
        SetQuaternionByCosineAxisRotateVWithNoRegularize(d, sp, YUnitVectorInv);
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)
"
                         "vsubw.x vf5, vf0, vf0w
"
                         "vmulx.xyz vf11, vf11, vf5x
"
                         "sqc2 vf11, 0x0(%1)
"
                         : : "r"(sp), "r"(sp + 0x10) : "memory");
    quatRotateVector2((Vec4 *)(sp + 0x30), (float *)(sp + 0x10), (Vec4 *)dv);
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "lqc2 vf6, 0x0(%1)
"
                         "vadd.xyz vf5, vf5, vf6
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(sp + 0x30), "r"(pos) : "memory");
    r = AI_GetQuaternionNodeDirTarget(outq, pos, a2, a3, sp + 0x30);
    if (r != 0) {
        __asm__ __volatile__("lqc2 vf11, 0x0(%0)
"
                             "lqc2 vf12, 0x0(%1)
"
                             "vmul.xyzw vf13, vf11, vf12
"
                             "vaddy.x vf13, vf13, vf13y
"
                             "vaddz.x vf13, vf13, vf13z
"
                             "vsubx.w vf13, vf13, vf13x
"
                             "vmulw.xyz vf14, vf12, vf11w
"
                             "vmulw.xyz vf15, vf11, vf12w
"
                             "vopmula.xyz ACC, vf12, vf11
"
                             "vopmsub.xyz vf16, vf11, vf12
"
                             "vadd.xyz vf13, vf14, vf15
"
                             "vadd.xyz vf13, vf13, vf16
"
                             "sqc2 vf13, 0x0(%1)
"
                             : : "r"(sp), "r"(outq) : "memory");
        return 1;
    }
    return 0;
}

