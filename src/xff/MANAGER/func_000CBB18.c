#ifdef NONMATCHING /* 60 diffs: out is copied to a3 instead of a3 holding the constant 1 for the type test */
typedef struct { float x, y, z, w; } __attribute__((aligned(8))) F4;
typedef int s128 __attribute__((mode(TI)));

extern s128 ZeroVector;

static inline float sqrtF(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

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

static inline void scaleXYZ(void *out, const void *src, float s)
{
    __asm__ __volatile__(
        "lqc2 vf5, 0x0(%1)\n"
        "qmtc2 %2, vf6\n"
        "vmulx.xyz vf5, vf5, vf6x\n"
        "sqc2 vf5, 0x0(%0)\n"
        : : "r"(out), "r"(src), "r"(s) : "memory");
}

static void func_000CBB18(s128 *out, char *obj, float *v, float a, float b)
{
    int type = *(int *)(*(char **)(obj + 4) + 4);

    if (type == 0) {
        *out = *(s128 *)(obj + 0xE0);
    } else if (type == 4) {
        *out = ZeroVector;
    } else {
        a *= *(float *)(obj + 0xD0);
        if (type == 1) {
            scaleXYZ(out, obj + 0xC0, a);
        } else if (type == 2) {
            scaleXYZ(out, v, a / sqrtF(b));
        } else {
            F4 t = { v[0], 0.0f, v[2], 0.0f };
            F4 c = t;
            scaleXYZ(out, &c, a / vectorLength(&c));
        }
    }
}
#endif
