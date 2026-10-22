typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern float YUnitVector[];
extern void iosGetSinCosf(float *, float);
void RotQuaternionYExact(float *out, float *source, float angle)
{
    Vec4 rotation;
    float sc[2];
    float *local = rotation.f;
    float *axis = YUnitVector;
    iosGetSinCosf(sc, -angle * 0.5f);
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "qmtc2 %2, vf06\n"
                         "vmulx.xyzw vf05, vf05, vf06x\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(local), "r"(axis), "r"(sc[1]) : "memory");
    local[3] = sc[0];
    __asm__ __volatile__("lqc2 vf11, 0(%1)\n"
                         "lqc2 vf12, 0(%2)\n"
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
                         "sqc2 vf13, 0(%0)\n"
                         : : "r"(out), "r"(source), "r"(rotation.f) : "memory");
}
