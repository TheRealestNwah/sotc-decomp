extern char *GetSCRCharaAIWorkPtr(void *actor);
extern char *getSCRDataCtrlWork(void *actor);
extern int T_000CBF88(void *actor, int select, int argument);

static inline float distanceXZ(float *a, float *b)
{
    float distance;
    __asm__ __volatile__(
        "lqc2 vf5, 0(%1)\n" "lqc2 vf6, 0(%2)\n"
        "vsub.xyzw vf7, vf5, vf6\n"
        "vmul.xz vf7, vf7, vf7\n" "vaddz.x vf7, vf7, vf7z\n"
        "vsqrt Q, vf7x\n" "vwaitq\n" "cfc2 $2, $vi22\n"
        "mtc1 $2, %0\n"
        : "=f"(distance) : "r"(a), "r"(b) : "$2");
    return distance;
}

int SCRConditionUnagiCheckAttackLine(void *actor, int a, int b, int c,
    int d, int e, int f, int g)
{
    char *ai = GetSCRCharaAIWorkPtr(actor);
    char *control = getSCRDataCtrlWork(actor);
    char *layout;
    float distance;
    if (T_000CBF88(actor, 0, g) == 0) {
            layout = *(char **)(control + 0x407C);
        distance = distanceXZ((float *)(ai + 0x5AF0), *(float **)(layout + 0x134));
        if (distance < 7.0f) return 1;
        return 0;
    }
    return 1;
}
