extern char padManagerData[];
extern float B_001A5A50[4];
extern char *iosgluGetCameraContext(void);

static void func_00107CA0(void)
{
    char *cam;

    if (*(int *)(padManagerData + 8) & 0x20) {
        cam = iosgluGetCameraContext();
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "qmtc2.ni %2, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(B_001A5A50), "r"(cam + 0x150), "r"(15.0f) : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(B_001A5A50), "r"(cam + 0x140), "r"(B_001A5A50) : "memory");
        B_001A5A50[3] = 1.0f;
    }
}
