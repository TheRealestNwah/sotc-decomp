typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern void GetMotionNodeBaseQuaternion(float *, char *, int, int);
void GetCharacterClassMotionBaseQ(float *out, char *c)
{
    Vec4 temp;
    float *selected;
    char *motion = *(char **)(c + 0x358);
    int node = *(int *)(c + 0x378);
    int quaternions = *(int *)(c + 0x154);
    if (!motion || *(int *)(*(char **)(motion + 8) + node * 64 + 0x38) == -1) {
        selected = (float *)(quaternions + node * 16);
    } else {
        selected = temp.f;
        GetMotionNodeBaseQuaternion(selected, motion, quaternions, node);
    }
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
                         : : "r"(out), "r"(selected), "r"(c + 0x380) : "memory");
}
