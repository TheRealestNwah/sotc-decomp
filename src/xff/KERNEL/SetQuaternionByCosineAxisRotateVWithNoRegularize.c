static inline float sqrtf(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

void SetQuaternionByCosineAxisRotateVWithNoRegularize(float *q, float *axis, float c)
{
    float w = sqrtf((c + 1.0f) * 0.5f);
    float s = sqrtf((1.0f - c) * 0.5f);

    __asm__ __volatile__("mfc1 $2, %2\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni $2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(q), "r"(axis), "f"(s) : "$2", "memory");
    q[3] = w;
}
