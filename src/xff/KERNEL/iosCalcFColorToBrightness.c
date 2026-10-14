extern char RO_00042F70[];

float iosCalcFColorToBrightness(float *c)
{
    float t[4] __attribute__((aligned(16)));
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vmul.xyzw vf05, vf05, vf06\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(t), "r"(c), "r"(RO_00042F70) : "memory");
    return t[0] + t[1] + t[2];
}
