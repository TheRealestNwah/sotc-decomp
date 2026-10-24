extern char *iosgluGetCameraContext(void);

int clipBySphere(void *sphere)
{
    char *context = iosgluGetCameraContext();
    int flags;

    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 vf27, 0(%1)\n"
        "lqc2 vf28, 0(%2)\n"
        "lqc2 vf29, 0x10(%2)\n"
        "lqc2 vf30, 0x20(%2)\n"
        "vaddw.x vf26, vf0, vf27w\n"
        "lqc2 vf31, 0x30(%2)\n"
        "vmove.yzw vf26, vf0\n"
        "vmulax.xyzw ACC, vf28, vf26x\n"
        "vmadday.xyzw ACC, vf29, vf26y\n"
        "vmaddaz.xyzw ACC, vf30, vf26z\n"
        "vmaddw.xyzw vf26, vf31, vf26w\n"
        "lqc2 vf28, 0(%3)\n"
        "lqc2 vf29, 0x10(%3)\n"
        "lqc2 vf30, 0x20(%3)\n"
        "lqc2 vf31, 0x30(%3)\n"
        "vmulax.xyzw ACC, vf28, vf27x\n"
        "vmadday.xyzw ACC, vf29, vf27y\n"
        "vmaddaz.xyzw ACC, vf30, vf27z\n"
        "vmaddw.xyzw vf27, vf31, vf0w\n"
        "vaddx.w vf27, vf27, vf26x\n"
        "vclipw.xyz vf27, vf27w\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "cfc2.ni %0, $18\n"
        ".set reorder\n"
        : "=&r"(flags) : "r"(sphere), "r"(context + 0x1E0), "r"(context + 0x5A0) : "memory");
    return flags & 0x3F;
}
