typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern s128 YUnitVector;
extern s128 ZUnitVector;
extern float iosGetACosfExact(float);

static inline float getPlaneAngle(float *normal)
{
    float y = normal[1];

    if (y >= 1.0f)
        return 0.0f;
    if (y <= -1.0f)
        return 180.0f;
    return iosGetACosfExact(y) * 57.29578f;
}

static inline void outerProduct(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void normalize(void *out, void *in)
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
                         : : "r"(out), "r"(in) : "memory");
}

void GetPlaneTopDir(s128 *out, float *normal)
{
    Vec4 side;

    if (getPlaneAngle(normal) != 0.0f) {
        outerProduct(side.f, normal, &YUnitVector);
        outerProduct(out, side.f, normal);
        normalize(out, out);
    } else {
        *out = ZUnitVector;
    }
}
