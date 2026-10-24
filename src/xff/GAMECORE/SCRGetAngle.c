extern void iosGetStabXZVector(float *out, float *v);
extern float iosGetACosfExact(float x);

static inline void vecSubXYZW(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float vecDot(float *a, float *b)
{
    float dot;
    float result;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

static inline void vecCross(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

float SCRGetAngle(float *from, float *dir, float *to)
{
    float d[4] __attribute__((aligned(16)));
    float cross[4] __attribute__((aligned(16)));
    float angle;

    float dot;
    float result;

    vecSubXYZW(d, to, from);
    iosGetStabXZVector(d, d);
    dot = vecDot(d, dir);
    vecCross(cross, d, dir);
    angle = iosGetACosfExact(dot);
    result = -angle;
    if (cross[1] < 0.0f) {
        result = angle;
    }
    return result;
}
