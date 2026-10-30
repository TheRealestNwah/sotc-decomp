typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern int GetCrossPositionPlaneLine(float *, float *, float *, float *);

static inline void vecScale(float *out, float *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecSub(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static int func_000D5E80(int *hit, float *out, char *plane, float *start, float *end)
{
    Vec4 n;
    Vec4 cross;
    Vec4 d;
    Vec4 far;
    int ret = 0;
    int r;

    *hit = 0;
    n.q = ((Vec4 *)(plane + 0x10))->q;
    n.f[3] -= 0.01f;
    if (GetCrossPositionPlaneLine(out, n.f, start, end) == 1) {
        *hit = 1;
        ret = 1;
    } else {
        vecScale(d.f, n.f, 10000.0f);
        vecAdd(d.f, end, d.f);
        r = GetCrossPositionPlaneLine(cross.f, n.f, end, d.f);
        if (r == 1) {
            vecSub(d.f, cross.f, end);
            vecAdd(far.f, cross.f, d.f);
            ret = GetCrossPositionPlaneLine(out, n.f, start, far.f) == r;
        }
    }
    return ret;
}
