extern char *GetSCRCharaAIWorkPtr(void *);
extern void *getSCRDataCtrlWork(void *);
extern void setAttainmentPosAndDir(void *, float *, float *);
extern void setAttainmentPosAndDirPosAndLock(void *, float *, float *);
extern void setAttainmentPos(void *, float *);

void SCRFuncUnageSetAttackPos(void *actor, int idx)
{
    char *ai = GetSCRCharaAIWorkPtr(actor);
    void *data = getSCRDataCtrlWork(actor);
    float d[4] __attribute__((aligned(16)));

    if (idx < 5) {
    if ((unsigned int)idx < 2) {
        setAttainmentPosAndDir(data, (float *)(ai + 0x5AD0 + idx * 16), (float *)(ai + 0x5B20));
    } else if (idx == 2) {
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyzw vf7, vf5, vf6\n"
                             "sqc2 vf7, 0x0(%0)\n"
                             : : "r"(d), "r"(ai + 0x5AF0), "r"(ai + 0x5AE0) : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "vmul.xyz vf7, vf5, vf5\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vrsqrt Q, vf0w, vf7w\n"
                             "vwaitq\n"
                             "vmulq.xyz vf5, vf5, Q\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(d) : "memory");
        d[3] = 1.0f;
        setAttainmentPosAndDirPosAndLock(data, (float *)(ai + 0x5AF0), d);
    } else {
        setAttainmentPos(data, (float *)(ai + 0x5AD0 + idx * 16));
    }
    }
}
