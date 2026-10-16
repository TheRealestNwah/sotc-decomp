int AI_CheckInAnimalLayout(float *layout, float *pos)
{
    float d[4] __attribute__((aligned(16)));
    float len;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(pos), "r"(layout) : "memory");
    {
        float h = layout[5];

        if (d[1] < 0.0f ? h < -d[1] : h < d[1])
            return 0;
    }
    d[1] = 0.0f;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(d) : "$2");
    if (layout[4] < len)
        return 0;
    return 1;
}
