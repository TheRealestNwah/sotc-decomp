typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

static inline void subtractXYZ(Vec4 *out, const Vec4 *to, const Vec4 *from)
{
    __asm__ __volatile__(
        "lqc2 vf05, 0(%1)\n"
        "lqc2 vf06, 0(%2)\n"
        "vsub.xyz vf05, vf05, vf06\n"
        "sqc2 vf05, 0(%0)\n"
        : : "r"(out), "r"(to), "r"(from) : "memory");
}

static inline void scaleXYZ(Vec4 *out, const Vec4 *source, float scale)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 vf05, 0(%1)\n"
        "qmtc2.ni %2, vf06\n"
        "vmulx.xyz vf05, vf05, vf06x\n"
        "sqc2 vf05, 0(%0)\n"
        ".set reorder\n"
        : : "r"(out), "r"(source), "r"(scale) : "memory");
}

void GAMEUTIL_get_vector_velocity_by_diff_move3D(Vec4 *out, const Vec4 *fallback,
                                               const Vec4 *from, const Vec4 *to,
                                               float time)
{
    if (time <= 0.0f) {
        out->q = fallback->q;
    } else {
        subtractXYZ(out, to, from);
        scaleXYZ(out, out, 1.0f / time);
    }
}

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

static inline int nearlyZero(float value, float tolerance)
{
    if (value < 0.0f) {
        if (-value <= tolerance)
            goto nearZero;
        else
            goto notNearZero;
    } else {
        if (value <= tolerance)
            goto nearZero;
        else
            goto notNearZero;
    }
nearZero:
    return 1;
notNearZero:
    return 0;
}

int GAMEUTIL_check_and_get_normalize_vector(Vec4 *out, float *magnitude,
                                           const Vec4 *vector)
{
    float length = vectorLength(vector);

    if (magnitude)
        *magnitude = length;
    if (!nearlyZero(length, 0.0001f)) {
        scaleXYZ(out, vector, 1.0f / length);
        return 1;
    }
    return 0;
}
