typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef union {
    struct {
        u_long128 q0;
        u_long128 q1;
        int tail[2];
    } s;
    char alias;
} CollisionDynamics;

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

static inline void scaleXYZW(void *out, const void *source, float scale)
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

void FilterCopyCollisionDynamics(CollisionDynamics *dst, CollisionDynamics *src)
{
    int *s;
    int *d;

    dst->s.q0 = src->s.q0;
    scaleXYZW(&dst->s.q1, &src->s.q1, 1.0f / vectorLength(&src->s.q1));
    s = src->s.tail;
    d = dst->s.tail;
    d[0] = s[0];
    d[1] = s[1];
}
