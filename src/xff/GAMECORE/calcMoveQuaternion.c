typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char IdentityQuaternion[];
extern float getRatioFromInterp(float, float);

static inline float dot4(Vec4 *a, Vec4 *b)
{
    register float r __asm__("$f1");
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x0(%2)\n"
                         "vmul.xyzw vf15, vf14, vf15\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "qmfc2.ni %0, vf15\n"
                         : "=r"(r) : "r"(a), "r"(b));
    return r;
}

static inline void negate4(Vec4 *v)
{
    int m = 0xBF800000;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "r"(m) : "memory");
}

static inline void lerpNorm(Vec4 *out, Vec4 *a, Vec4 *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf5, vf7x\n"
                         "vmaddw.xyzw vf9, vf6, vf8w\n"
                         "sqc2 vf9, 0x0(%0)\n"
                         "lqc2 vf14, 0x0(%0)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

static inline void quatMul(Vec4 *out, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
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
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(out), "r"(b) : "memory");
}

#ifdef NONMATCHING /* 77 diffs: address-register CSE of the sp+0x20/0x30 slots and Identity pointer ($t1-$t5 in the original) */
void calcMoveQuaternion(Vec4 *out, Vec4 *cur, Vec4 *tgt, float rate)
{
    Vec4 a, b, c, d;
    register float ratio __asm__("$f0");
    float s40, s44;

    ratio = getRatioFromInterp(rate, 0.06666667f);
    a.q = tgt->q;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(out) : "memory");
    if (rate >= 0.06666667f && dot4(cur, &a) < 0.9993908f) {
        do {
            c.q = *(s128 *)IdentityQuaternion;
            *(volatile float *)&s40 = dot4(&a, &c);
            if (*(volatile int *)&s40 < 0) negate4(&c);
            lerpNorm(&b, &a, &c, 0.06666667f);
            quatMul(out, &b);
            d.q = a.q;
            *(volatile float *)&s44 = dot4(cur, &d);
            if (*(volatile int *)&s44 < 0) negate4(&d);
            lerpNorm(&a, cur, &d, ratio);
        } while (dot4(cur, &a) < 0.9993908f);
    }
}
#endif
