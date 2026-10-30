static inline float vectorLength(const void *vector)
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

#define ABS(x) ((x) < 0 ? -(x) : (x))

static void func_0004BAA0(float *v)
{
    float len = vectorLength(v);

    if (ABS(v[0]) > ABS(v[1]) && ABS(v[0]) > ABS(v[2])) {
        v[0] = v[0] < 0 ? -len : len;
        v[1] = v[2] = 0;
    } else if (ABS(v[1]) > ABS(v[0]) && ABS(v[1]) > ABS(v[2])) {
        v[1] = v[1] < 0 ? -len : len;
        v[0] = v[2] = 0;
    } else {
        v[2] = v[2] < 0 ? -len : len;
        v[0] = v[1] = 0;
    }
}
