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
        __asm__ __volatile__("mfc1 $7, %0\n"
                             "mfc1 $8, %1\n"
                             "mfc1 $9, %2\n"
                             "lqc2 vf7, 0x0(%3)\n"
                             "qmtc2.ni $7, vf4\n"
                             "lqc2 vf8, 0x0(%4)\n"
                             "lqc2 vf9, 0x0(%5)\n"
                             "qmtc2.ni $8, vf5\n"
                             "qmtc2.ni $9, vf6\n"
                             "vmulx.xyz vf11, vf7, vf4x\n"
                             "vaddx.xyz vf11, vf8, vf11x\n"
                             "vmulx.xyz vf11, vf11, vf5x\n"
                             "vsub.xyz vf10, vf9, vf11\n"
                             "vmulx.xyz vf11, vf7, vf6x\n"
                             "vsub.xyz vf10, vf10, vf11\n"
                             "sqc2 vf10, 0x0(%6)\n"
                             : : "f"(a - d), "f"(d), "f"(d * 0.5f * d), "r"(p + 0x20), "r"(p + 0x30), "r"(p), "r"(out) : "$6", "$7", "$8", "$9", "memory");
        return 1;
    }
    return 0;
}
