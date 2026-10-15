void GetMotionNodeBaseQuaternion(float *out, char *m, int q, int i)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(out) : "memory");
    while (i != -1) {
        __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                             "lqc2 vf12, 0x0(%0)\n"
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
                             : : "r"(out), "r"(i * 16 + q) : "memory");
        i = *(int *)(*(char **)(m + 8) + i * 64 + 0x38);
    }
}
