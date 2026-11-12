typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char ZUnitVectorInv[];
extern float iosGetACosfExact(float);
extern void RotQuaternionXExact(float *, float *, float);
extern void GetDifferencialQuaternionWithNoRegularize(float *, float *, void *, void *);

static inline void quatRotateVector(Vec4 *out0, float *quat0, Vec4 *vec0)
{
    register Vec4 *vec __asm__("$4") = vec0;
    register Vec4 *out __asm__("$2") = out0;
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

static inline float sqrts(float x)
{
    float r;
    __asm__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

static inline float lenSq3(void *v)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(v) : "$2");
    return r;
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

#ifdef NONMATCHING /* 15 diffs: v0/v1 numbering of the (idx<<N)+base address temps, $f0 vs $f1 for the sd*sb product, and 0.0f/$f21 init order */
float func_00091CE0(char *o, s128 *tgt, char *unused, char *a, char *b, int flip)
{
    Vec4 d __attribute__((aligned(16)));
    Vec4 n __attribute__((aligned(16)));
    Vec4 r __attribute__((aligned(16)));
    Vec4 c __attribute__((aligned(16)));
    float q[4] __attribute__((aligned(16)));
    register float la __asm__("$f23");
    register float lb __asm__("$f24");
    register float ld __asm__("$f22");
    register float sa __asm__("$f26");
    register float sb __asm__("$f1");
    register float sd __asm__("$f20");
    register float ang1 __asm__("$f21");
    register float ang2 __asm__("$f25");
    char *pos = (*(int *)(o + 0x14) << 6) + *(char **)(o + 8) + 0x30;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&d), "r"(tgt), "r"(pos) : "memory");
    la = lenSq3(a);
    sa = sqrts(la);
    lb = lenSq3(b);
    sb = sqrts(lb);
    ld = lenSq3(&d);
    sd = sqrts(ld);
    ang1 = 0.0f;
    ang2 = ang1;
    if (sd < sa + sb) {
        float x1, x2;
        sd = sd + sd;
        x1 = (ld + lb - la) / (sd * sb);
        sd = sd * sa;
        ang1 = iosGetACosfExact(x1);
        x2 = (ld + la - lb) / sd;
        ang2 = iosGetACosfExact(x2);
        ang1 = ang2 + ang1;
        if (flip) {
            ang2 = -ang2;
            ang1 = -ang1;
        }
    }
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%1)\n"
                         : : "r"(&d), "r"(&n) : "memory");
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%0)\n"
                         : : "r"(&c), "r"((*(int *)(o + 0x14) << 4) + *(char **)(o + 0xC)) : "memory");
    quatRotateVector(&r, (float *)&c, &n);
    GetDifferencialQuaternionWithNoRegularize(q, (float *)&r, ZUnitVectorInv, o + 0x20);
    quatMul((*(int *)(o + 0x14) << 4) + *(char **)(o + 4), (*(int *)(o + 0x14) << 4) + *(char **)(o + 4), q);
    RotQuaternionXExact((float *)((*(int *)(o + 0x14) << 4) + *(char **)(o + 4)),
                        (float *)((*(int *)(o + 0x14) << 4) + *(char **)(o + 4)), ang2);
    return ang1;
}
#endif
