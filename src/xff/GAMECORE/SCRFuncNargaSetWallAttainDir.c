extern void *GetSCRCharaAIWorkPtr(void *);
extern void *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
static inline void subtractVectors(float *output, const float *a, const float *b)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%1)\n"
        "lqc2 vf6, 0x0(%2)\n"
        "vsub.xyzw vf7, vf5, vf6\n"
        "sqc2 vf7, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(output), "r"(a), "r"(b) : "memory");
}
static inline void normalizeXYZ(float *output, const float *input)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%1)\n"
        "vmul.xyz vf7, vf5, vf5\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vrsqrt Q, vf0w, vf7w\n"
        "vwaitq\n"
        "vmulq.xyz vf5, vf5, Q\n"
        "sqc2 vf5, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(output), "r"(input) : "memory");
}
void SCRFuncNargaSetWallAttainDir(void *actor)
{
    char *ai = GetSCRCharaAIWorkPtr(actor);
    char *control = getSCRDataCtrlWork(actor);
    char *layout = GetLayoutClass(actor);
    char *target = *(char **)(control + 0x407C);
    float *direction = (float *)(ai + 0x5A90);
    subtractVectors(direction, *(float **)(target + 0x134), *(float **)(layout + 0x134));
    *(float *)(ai + 0x5A94) = 0.0f;
    normalizeXYZ(direction, direction);
}
