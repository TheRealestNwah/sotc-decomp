typedef int s128 __attribute__((mode(TI)));

extern float iosGetACosfExact(float);
extern void iosGetSinCosf(float *, float);

int GetLimitationQuaternion(float *out, float *q, float limit)
{
    float sc[2] __attribute__((aligned(16)));
    float a = iosGetACosfExact(q[3]);
    float t = a + a;
    int r = 0;

    if (t < 0.0f) {
        if (!(limit < -t))
            goto copy;
    } else {
        if (!(limit < t))
            goto copy;
    }
    iosGetSinCosf(sc, (t < 0.0f ? -limit : limit) * 0.5f);
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%1)\n"
                         : : "r"(q), "r"(out) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(sc[1]) : "memory");
    out[3] = sc[0];
    return 1;
copy:
    *(s128 *)out = *(s128 *)q;
    return r;
}
