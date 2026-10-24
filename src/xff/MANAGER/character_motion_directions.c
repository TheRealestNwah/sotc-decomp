typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern void GetMotionNodeBaseQuaternion(float *, char *, int, int);
static inline void motionBaseQuaternion(float *out, char *c)
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

void GetCharacterClassMotionTopDirection(void *out, char *character)
{
    Vec4 quaternion;
    motionBaseQuaternion(quaternion.f, character);
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf4, 0x0(%1)\n"
        "vmul.xyzw vf5, vf4, vf4\n"
        "vmr32.xyzw vf6, vf4\n"
        "vmul.xyzw vf7, vf6, vf4\n"
        "vaddy.z vf6, vf0, vf7y\n"
        "vsubw.z vf6, vf6, vf7w\n"
        "vsubx.y vf6, vf0, vf5x\n"
        "vsubz.y vf6, vf6, vf5z\n"
        "vaddz.x vf6, vf7, vf7z\n"
        "vsub.w vf6, vf0, vf0\n"
        "vadd.w vf5, vf0, vf0\n"
        "vmulw.xyz vf6, vf6, vf5w\n"
        "vaddw.y vf6, vf6, vf0w\n"
        "sqc2 vf6, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(out), "r"(quaternion.f) : "memory");
}

void GetCharacterClassMotionFrontDirection(void *out, char *character)
{
    Vec4 quaternion;
    motionBaseQuaternion(quaternion.f, character);
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf4, 0x0(%0)\n"
        "vmul.xyzw vf5, vf4, vf4\n"
        "vmr32.xyzw vf6, vf4\n"
        "vmul.xyzw vf7, vf6, vf4\n"
        "vmr32.xyzw vf6, vf6\n"
        "vmul.xyzw vf8, vf6, vf4\n"
        "vsubx.z vf6, vf0, vf5x\n"
        "vsuby.z vf6, vf6, vf5y\n"
        "vaddw.y vf6, vf7, vf7w\n"
        "vsuby.x vf6, vf8, vf8y\n"
        "vsub.w vf6, vf0, vf0\n"
        "vadd.w vf5, vf0, vf0\n"
        "vmulw.xyz vf6, vf6, vf5w\n"
        "vaddw.z vf6, vf6, vf0w\n"
        "sqc2 vf6, 0x0(%1)\n"
        ".set reorder\n"
        : : "r"(quaternion.f), "r"(out) : "memory");
}
