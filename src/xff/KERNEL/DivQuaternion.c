void DivQuaternion(float *out, float *a, float *b)
{
    float c[4] __attribute__((aligned(16)));
    __asm__ __volatile__("lqc2 vf11, 0(%1)\n"
                         "vsubw.x vf05, vf00, vf00w\n"
                         "vmulx.xyz vf11, vf11, vf05x\n"
                         "sqc2 vf11, 0(%0)\n"
                         : : "r"(c), "r"(b) : "memory");
    __asm__ __volatile__("lqc2 vf11, 0(%2)\n"
                         "lqc2 vf12, 0(%1)\n"
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
                         : : "r"(out), "r"(a), "r"(c) : "memory");
}
