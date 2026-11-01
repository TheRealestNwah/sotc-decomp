extern void GAMEUTIL_get_divide_vector_value(float *, float *, float *, float *, float *, float *, float *);

static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void vecAdd(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

void CAM_get_mul_ratio_offset_per_axis(float *out, float *v, float *x, float *y, float *z,
    float xp, float xm, float yp, float ym, float zp, float zm)
{
    float tmp[4] __attribute__((aligned(16)));
    float r[3];

    GAMEUTIL_get_divide_vector_value(&r[0], &r[1], &r[2], v, x, y, z);
    if (r[0] >= 0.0f) r[0] *= xp; else r[0] *= xm;
    if (r[1] >= 0.0f) r[1] *= yp; else r[1] *= ym;
    if (r[2] >= 0.0f) r[2] *= zp; else r[2] *= zm;
    vecScale(out, x, r[0]);
    vecScale(tmp, y, r[1]);
    vecAdd(out, out, tmp);
    vecScale(tmp, z, r[2]);
    vecAdd(out, out, tmp);
}
