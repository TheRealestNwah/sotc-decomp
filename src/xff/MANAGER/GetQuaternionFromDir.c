typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern float iosGetACosf(float);
extern float iosGetACosfExact(float);
extern void iosGetArbitraryUpVectorElement(float *, float *);
extern void SetQuaternionByAxisRotateV(void *, short, float *);
#define VU_OUTER_PRODUCT(dst, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "lqc2 vf06, 0x0(%2)\n" \
                         "vopmula.xyz ACC, vf05, vf06\n" \
                         "vopmsub.xyz vf07, vf06, vf05\n" \
                         "vsub.w vf07, vf07, vf07\n" \
                         "sqc2 vf07, 0x0(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")

void GetQuaternionFromDir(float *out, float *from, float *to, int mode)
{
    Vec4 axis;
    float d;
    float angle;
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vaddw.x vf07, vf00, vf00w\n"
                         "vmul.xyz vf06, vf05, vf06\n"
                         "vaddax.x ACC, vf00, vf06x\n"
                         "vmadday.x ACC, vf07, vf06y\n"
                         "vmaddz.x vf06, vf07, vf06z\n"
                         "qmfc2 %0, vf06\n"
                         : "=r"(d) : "r"(to), "r"(from));

    if (1.0f <= d) {
        __asm__ __volatile__("sqc2 vf0, 0(%0)\n" : : "r"(out) : "memory");
        return;
    }
    if (d <= -1.0f) {
        angle = 3.1415926f;
        iosGetArbitraryUpVectorElement(axis.f, from);
    } else {
        if (mode) angle = iosGetACosf(d);
        else angle = iosGetACosfExact(d);
        VU_OUTER_PRODUCT(axis.f, from, to);
    }
    SetQuaternionByAxisRotateV(out, -(int)((angle * 32768.0f) / 3.1415926f), axis.f);
}
