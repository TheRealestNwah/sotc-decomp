static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void vecAdd(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void vecSub(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

void AI_GetAccelB3XYZ(float *out, float *a, float *b, float *c, float *d, float *e, float t)
{
    float tmp[4] __attribute__((aligned(16)));
    float t2;

    if (t < 0.033366699f)
        t = 0.033366699f;
    t2 = t * t;
    vecSub(tmp, d, c);
    vecScale(out, tmp, 4.0f / t);
    vecSub(out, out, b);
    vecScale(tmp, a, 3.0f);
    vecSub(out, out, tmp);
    vecScale(tmp, e, t);
    vecSub(out, out, tmp);
    vecScale(out, out, 6.0f / t2);
}
