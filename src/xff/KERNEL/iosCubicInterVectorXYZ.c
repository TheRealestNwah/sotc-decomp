static inline float cubicBezier(float *coefficients, float t)
{
    float u = 1.0f - t;
    return u * u * coefficients[0] + 2.0f * u * t * coefficients[1] + t * t * coefficients[2];
}

void iosCubicInterVectorXYZ(float *out, float *a, float *b, float *coefficients, float t)
{
    float alpha = cubicBezier(coefficients, t);
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         ".set reorder\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(alpha) : "memory", "$8");
}
