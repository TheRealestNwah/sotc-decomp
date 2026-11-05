typedef int s128 __attribute__((mode(TI)));

typedef union {
    float f[4];
    s128 q;
} V4;

extern float *getGoalPointDataByAreaIdx(char *, int, int);

static inline float dist(float *a, float *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static int func_000FC4B8(char *w, char *lay, char *lay2, int g1, int g2)
{
    float *a = getGoalPointDataByAreaIdx(w, g1, *(int *)(w + 0x3C8C));
    float *b = getGoalPointDataByAreaIdx(w, g2, *(int *)(w + 0x3C8C));
    V4 pos;

    if (a == 0)
        return 1;
    if (*(int *)(w + 0x3C78) == 0)
        pos.q = **(s128 **)(lay + 0x134);
    else
        pos.q = **(s128 **)(lay2 + 0x134);
    if (dist(pos.f, a) - dist(pos.f, b) > 0.5f)
        return 1;
    return 0;
}
