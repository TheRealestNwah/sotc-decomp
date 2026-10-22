int ClipPoint(void *point, void *matrix)
{
    int flags;
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 vf27, 0(%1)\n"
        "lqc2 vf28, 0(%2)\n"
        "lqc2 vf29, 0x10(%2)\n"
        "lqc2 vf30, 0x20(%2)\n"
        "lqc2 vf31, 0x30(%2)\n"
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
        : "=r"(flags) : "r"(point), "r"(matrix) : "memory");
    return flags & 0x3F;
}
