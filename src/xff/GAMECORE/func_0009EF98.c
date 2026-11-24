typedef struct { char pad[8]; float v8; } Lim;

#ifdef NONMATCHING /* 11 diffs: logic matches; the Original cross-jumps the mode 8 tail and the 0x580 == 0 tail into the shared `jr ra` (v0 = 1 in delay slots, bc1fl v0 = 0), where ours materializes the compare in v1. The 0.5f threshold is a local so it is loaded before the 0x5B4/0x594 loads like the Original */
static inline float distXYZ(char *a, char *b)
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

static int func_0009EF98(char *c)
{
    float f0;
    float f4;
    int v;

    int mode = *(int *)c;

    if (mode == 8) {
        if (*(float *)(c + 0x290) > 5.0f)
            return 1;
        if (*(float *)(c + 0x150) < 15.0f)
            return 1;
        return *(float *)(c + 0x158) < (*(Lim **)(c + 0x20))->v8;
    }
    if (mode == 6) {
        f0 = *(float *)(c + 0x58C);
        if (f0 > 0.0f)
            f0 = 0.0f;
        if (*(float *)(c + 0x218) < (*(Lim **)(c + 0x20))->v8 * (1.0f - f0))
            return 1;
        if (*(float *)(c + 0x2F0) < 0.5f)
            return 1;
        return 0;
    }
    if (*(int *)(c + 0x580) != 0) {
        f4 = *(float *)(c + 0x1B0);
        if (f4 < 50.0f) {
            float d = distXYZ(c + 0x5B0, c + 0x590);
            float h = 0.5f;

            v = (*(float *)(c + 0x5B4) - *(float *)(c + 0x594)) / d > h;
            if (v != 0)
                return 1;
        }
        if (*(float *)(c + 0x2E8) < 5.0f)
            return 1;
        if (*(float *)(c + 0x218) < (*(Lim **)(c + 0x20))->v8)
            return 1;
        if (*(float *)(c + 0x1B8) < 0.0f)
            return 1;
        if (f4 < 15.0f)
            return 1;
        if (*(float *)(c + 0x2F0) < 0.5f)
            return 1;
        return 0;
    }
    if (*(float *)(c + 0x158) < (*(Lim **)(c + 0x20))->v8)
        return 1;
    return 0;
}
#endif
