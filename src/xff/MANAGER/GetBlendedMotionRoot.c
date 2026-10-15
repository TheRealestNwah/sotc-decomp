void GetBlendedMotionRoot(float *out, float *a, float *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2 $8, vf07\n"
                         "lqc2 vf05, 0x0(%1)\n"
                         "lqc2 vf06, 0x0(%2)\n"
                         "vsubx.w vf08, vf00, vf07x\n"
                         "vmulax.xyz ACC, vf05, vf07x\n"
                         "vmaddw.xyz vf05, vf06, vf08w\n"
                         "sqc2 vf05, 0x0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(t) : "memory", "$8");
}
