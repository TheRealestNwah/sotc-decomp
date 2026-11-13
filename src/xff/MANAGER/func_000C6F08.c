#ifdef NONMATCHING
/* Parked: 8 diffs (same length, 38 words). Only the mfc1 order and registers for the asm inputs differ: the original uses a3/t0/t1 with both muls scheduled first; ours a3/a2/t0. */
static int func_000C6F08(float *out, char *p)
{
    float a = *(float *)(p + 0x44);
    float lim = *(float *)(p + 0xA0);
    float d = *(float *)(p + 0x98);
    float rest;
    float half;

    if (a - d < lim)
        d = a - lim;
    if (0.0f < d) {
        float x = a - d;
        float sq = d * 0.5f;

        sq = sq * d;
        rest = x;
        half = sq;
        __asm__ __volatile__("lqc2 vf7, 0x0(%3)
"
                             "qmtc2.ni %0, vf4
"
                             "lqc2 vf8, 0x0(%4)
"
                             "lqc2 vf9, 0x0(%5)
"
                             "qmtc2.ni %1, vf5
"
                             "qmtc2.ni %2, vf6
"
                             "vmulx.xyz vf11, vf7, vf4x
"
                             "vaddx.xyz vf11, vf8, vf11x
"
                             "vmulx.xyz vf11, vf11, vf5x
"
                             "vsub.xyz vf10, vf9, vf11
"
                             "vmulx.xyz vf11, vf7, vf6x
"
                             "vsub.xyz vf10, vf10, vf11
"
                             "sqc2 vf10, 0x0(%6)
"
                             : : "r"(a - d), "r"(d), "r"(d * 0.5f * d), "r"(p + 0x20), "r"(p + 0x30), "r"(p), "r"(out) : "memory");
        return 1;
    }
    return 0;
}
#endif
