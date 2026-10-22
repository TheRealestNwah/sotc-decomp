extern float iosGetACosfExact(float);

static float func_000DA5D8(void *a, void *b)
{
    float dot;

    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni %0, vf6\n"
                         ".set reorder\n"
                         : "=r"(dot) : "r"(a), "r"(b));
    return (1.5707963f - iosGetACosfExact(dot)) / 1.5707963f;
}

