void GetBlendedMotionRoot(void *a0, void *a1, void *a2, float f0)
{
    __asm__ __volatile__(".set noreorder\n"
        "mfc1 $8, %0\n"
        "qmtc2.ni $8, vf7\n"
        "lqc2 vf5, 0x0(%1)\n"
        "lqc2 vf6, 0x0(%2)\n"
        "vsubx.w vf8, vf0, vf7x\n"
        "vmulax.xyz ACC, vf5, vf7x\n"
        "vmaddw.xyz vf5, vf6, vf8w\n"
        "sqc2 vf5, 0x0(%3)\n"
        ".set reorder\n"
        : : "f"(f0), "r"(a1), "r"(a2), "r"(a0) : "memory", "$8");
}
