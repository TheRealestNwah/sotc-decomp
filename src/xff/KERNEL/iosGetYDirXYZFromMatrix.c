void iosGetYDirXYZFromMatrix(void *a0, void *a1)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf4, 0x10(%1)\n"
        "vsub.w vf4, vf4, vf4\n"
        "sqc2 vf4, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0), "r"(a1) : "memory");
}
