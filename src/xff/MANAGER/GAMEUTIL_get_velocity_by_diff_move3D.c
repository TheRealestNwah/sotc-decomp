typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

static inline float distanceXYZ(const Vec4 *to, const Vec4 *from)
{
    float length;
    __asm__ __volatile__(
        "lqc2 vf5, 0(%1)\n"
        "lqc2 vf6, 0(%2)\n"
        "vsub.xyzw vf7, vf5, vf6\n"
        "vmul.xyz vf7, vf7, vf7\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vsqrt Q, vf7w\n"
        "vwaitq\n"
        "cfc2 $2, $vi22\n"
        "mtc1 $2, %0\n"
        : "=f"(length) : "r"(to), "r"(from) : "$2");
    return length;
}

float GAMEUTIL_get_velocity_by_diff_move3D(const Vec4 *to, const Vec4 *from,
                                           float fallback, float time)
{
    if (time == 0.0f)
        return fallback;
    return distanceXYZ(to, from) / time;
}
