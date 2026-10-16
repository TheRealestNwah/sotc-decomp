extern char *GetSCRCharaAIWorkPtr(void *);
extern char *GetLayoutClass(void *);

void getPlayerPosAfterXSeconds(void *obj, float *out, float t)
{
    char *w = GetSCRCharaAIWorkPtr(obj);

    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "mfc1 $8, %2\n"
                         "qmtc2.ni $8, vf5\n"
                         "vmulx.xyzw vf6, vf4, vf5x\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(w + 0x1940), "f"(t) : "$8", "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "vadd.xyz vf6, vf4, vf5\n"
                         "vmove.w vf6, vf0\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(out), "r"(*(float **)(GetLayoutClass(obj) + 0x134)) : "memory");
}
