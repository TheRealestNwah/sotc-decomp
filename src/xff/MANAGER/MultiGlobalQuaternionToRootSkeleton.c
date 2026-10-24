typedef struct { float f[4]; } Vector;

void MultiGlobalQuaternionToRootSkeleton(void *quaternions, void *rotation, void *skeleton)
{
    int count = *(int *)((char *)skeleton + 4);
    int i = 0;
    if (count > 0) {
        Vector *current = quaternions;
        do {
            if (*(int *)(i * 64 + *(int *)((char *)skeleton + 8) + 0x38) == -1) {
                __asm__ __volatile__("lqc2 vf11, 0(%1)\n"
                                     "lqc2 vf12, 0(%2)\n"
                                     "vmul.xyzw vf13, vf11, vf12\n"
                                     "vaddy.x vf13, vf13, vf13y\n"
                                     "vaddz.x vf13, vf13, vf13z\n"
                                     "vsubx.w vf13, vf13, vf13x\n"
                                     "vmulw.xyz vf14, vf12, vf11w\n"
                                     "vmulw.xyz vf15, vf11, vf12w\n"
                                     "vopmula.xyz ACC, vf12, vf11\n"
                                     "vopmsub.xyz vf16, vf11, vf12\n"
                                     "vadd.xyz vf13, vf14, vf15\n"
                                     "vadd.xyz vf13, vf13, vf16\n"
                                     "sqc2 vf13, 0(%0)\n"
                                     : : "r"(current), "r"(rotation), "r"(current) : "memory");
            }
            ++i;
            ++current;
        } while (i < count);
    }
}
