typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

static inline float vectorLength(const Vec4 *vector)
{
    float length;
    __asm__ __volatile__(
        "lqc2 vf7, 0(%1)\n"
        "vmul.xyz vf7, vf7, vf7\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vsqrt Q, vf7w\n"
        "vwaitq\n"
        "cfc2 $2, $vi22\n"
        "mtc1 $2, %0\n"
        : "=f"(length) : "r"(vector) : "$2");
    return length;
}

static inline void scaleXYZW(Vec4 *out, const Vec4 *source, float scale)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 vf05, 0(%1)\n"
        "qmtc2.ni %2, vf06\n"
        "vmulx.xyzw vf05, vf05, vf06x\n"
        "sqc2 vf05, 0(%0)\n"
        ".set reorder\n"
        : : "r"(out), "r"(source), "r"(scale) : "memory");
}

void GetNormalPlane(Vec4 *out, const Vec4 *vector)
{
    scaleXYZW(out, vector, 1.0f / vectorLength(vector));
}
