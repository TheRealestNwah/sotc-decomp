void ExchangeLWVector(float *out, float *in)
{
    float s = -1.0f;

    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n"
                         "qmtc2 %2, vf06\n"
                         "vmulx.xyz vf05, vf05, vf06x\n"
                         "sqc2 vf05, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
    out[1] = -out[1];
}
