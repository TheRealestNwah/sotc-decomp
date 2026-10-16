extern float iosGetACosfExact(float);
extern void iosGetSinCosf(float *, float);

static inline void quatAxis(float *out, float *q, float *sc)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(sc[1]) : "memory");
    out[3] = sc[0];
}

void GetAdjustQuaternion(float *out, float *q, float s)
{
    float sc[2];

    iosGetSinCosf(sc, iosGetACosfExact(q[3]) * 2.0f < 0.0f ? -s * 0.5f : s * 0.5f);
    quatAxis(out, q, sc);
}
