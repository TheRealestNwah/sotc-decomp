extern int RO_00042F80[];

void iosScaleColorTo255(void *a0, void *a1)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf4, 0x0(%1)\n"
        "lqc2 vf5, 0x0(%2)\n"
        "vmul.xyzw vf5, vf4, vf5\n"
        "sqc2 vf6, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0), "r"(a1), "r"(RO_00042F80) : "memory");
}
