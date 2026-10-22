void CompletePlaneD(void *a0, void *a1)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf4, 0x0(%0)\n"
        "lqc2 vf5, 0x0(%1)\n"
        "vmul.xyz vf5, vf4, vf5\n"
        "vaddy.x vf5, vf5, vf5y\n"
        "vaddz.x vf5, vf5, vf5z\n"
        "vsubw.xyzw vf6, vf0, vf0w\n"
        "vsubx.w vf4, vf6, vf5x\n"
        "sqc2 vf4, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0), "r"(a1) : "memory");
}
