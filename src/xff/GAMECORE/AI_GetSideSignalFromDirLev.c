int AI_GetSideSignalFromDirLev(float *a, float *b)
{
    float t[4] __attribute__((aligned(16)));
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vopmula.xyz ACC, vf05, vf06\n"
                         "vopmsub.xyz vf07, vf06, vf05\n"
                         "vsub.w vf07, vf07, vf07\n"
                         "sqc2 vf07, 0(%0)\n"
                         : : "r"(t), "r"(a), "r"(b) : "memory");
    if (0.0f <= t[1])
        return -1;
    return 1;
}
