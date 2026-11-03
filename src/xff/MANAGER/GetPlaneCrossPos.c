#ifdef NONMATCHING /* logic matches; target copies out/p0/p1 to t1/v1/a2 and &tmp into a0 */
typedef float Vec4[4] __attribute__((aligned(16)));

static inline float planeDist(float *plane, float *p)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "vaddw.x vf6, vf6, vf5w\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(plane), "r"(p) : "$2");
    return d;
}

static inline void vecLerp(float *dst, float *a, float *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

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

static inline float absf(float x)
{
    if (x < 0.0f) {
        x = -x;
    }
    return x;
}

static inline void project(float *out, float *plane, float *p)
{
    Vec4 tmp;

    vecScale(tmp, plane, -planeDist(plane, p));
    tmp[3] = 0.0f;
    vecAdd(out, p, tmp);
}

int GetPlaneCrossPos(float *out, float *plane, float *p0, float *p1)
{
    float d0 = planeDist(plane, p0);
    float d1 = planeDist(plane, p1);
    float *p;

    if (d0 * d1 < 0.0f && d1 - d0 != 0.0f) {
        vecLerp(out, p0, p1, d1 / (d1 - d0));
        return 1;
    }
    p = p0;
    if (!(absf(d0) < (d1 < 0.0f ? -d1 : d1))) {
        p = p1;
    }
    project(out, plane, p);
    return 0;
}
#endif
