typedef float Vec4[4] __attribute__((aligned(16)));

static inline void scale(float *d, float *s, float k)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(s), "r"(k) : "memory");
}

static inline void add(float *d, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

void iosCubicBezierVectorXYZ(float *out, Vec4 *p, float t)
{
    Vec4 tmp;
    float u = 1.0f - t;

    scale(out, p[0], u * u);
    scale(tmp, p[1], (u + u) * t);
    add(out, out, tmp);
    scale(tmp, p[2], t * t);
    add(out, out, tmp);
}
