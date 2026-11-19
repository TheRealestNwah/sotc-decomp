/* Checks that two vectors are nonzero and not (anti)parallel: both are normalized and their dot product must stay within 0.999 of +-1. The final returns go through shared labels, which gives the Original's branch-likely forms. */
typedef struct { float f[4]; } __attribute__((aligned(16))) V4;

static inline int isNonZero(float *v)
{
    if (v[0] < 0.0f) {
        if (!(-0.0001f < v[0]))
            goto nonzero;
    } else if (!(v[0] < 0.0001f)) {
        goto nonzero;
    }
    if (v[1] < 0.0f) {
        if (!(-0.0001f < v[1]))
            goto nonzero;
    } else if (!(v[1] < 0.0001f)) {
        goto nonzero;
    }
    if (v[2] < 0.0f) {
        if (!(-0.0001f < v[2]))
            goto nonzero;
    } else if (!(v[2] < 0.0001f)) {
        goto nonzero;
    }
    return 0;
nonzero:
    return 1;
}

static inline void vecNormalize(void *d, void *s)
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
                         : : "r"(d), "r"(s) : "memory");
}

static inline float vecDot(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

int AI_CheckNoAngleVec(float *a, float *b)
{
    V4 na, nb;

    if (!isNonZero(a) || !isNonZero(b))
        return 0;
    vecNormalize(&na, a);
    vecNormalize(&nb, b);
    if (vecDot(&na, &nb) < 0.0f) {
        if (vecDot(&na, &nb) < -0.9989999532699585f)
            goto zero;
        goto one;
    }
    if (!(vecDot(&na, &nb) > 0.9989999532699585f))
        goto one;
zero:
    return 0;
one:
    return 1;
}
