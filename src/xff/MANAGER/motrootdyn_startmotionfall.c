typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern Vec4 YUnitVector;
extern void func_0005CD18(void *, char *);
extern int GetMotionRootDirInfo(Vec4 *, int, float);
extern void GetQuaternionByAxisDirZY(Vec4 *, Vec4 *, Vec4 *);
extern void StabilizeToYRotQuaternion(Vec4 *);

void motrootdyn_startmotionfall(void *motion, char *c)
{
    Vec4 dir;
    Vec4 axis;
    char *info;

    func_0005CD18(motion, c);
    ((Vec4 *)(c + 0xB30))->q = ((Vec4 *)(c + 0x30))->q;
    info = c + 0x1C0;
    if (GetMotionRootDirInfo(&dir, *(int *)info + 0x50, *(float *)(info + 8)) != 0) {
        __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
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
            : : "r"(&axis), "r"(*(Vec4 **)(c + 0x13C)) : "memory");
        GetQuaternionByAxisDirZY((Vec4 *)(c + 0xB40), &YUnitVector, &axis);
        __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
            "vsubw.x vf5, vf0, vf0w\n"
            "vmulx.xyz vf11, vf11, vf5x\n"
            "sqc2 vf11, 0x0(%0)\n"
            : : "r"(&dir) : "memory");
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
                             : : "r"(c + 0xB40), "r"(c + 0xB40), "r"(&dir) : "memory");
    } else {
        ((Vec4 *)(c + 0xB40))->q = (*(Vec4 **)(c + 0x13C))->q;
        StabilizeToYRotQuaternion((Vec4 *)(c + 0xB40));
    }
}
