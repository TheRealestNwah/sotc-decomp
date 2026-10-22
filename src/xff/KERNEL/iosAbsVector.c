void iosAbsVector(void *a0, void *a1)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%1)\n"
        "vabs.xyzw vf6, vf5\n"
        "sqc2 vf6, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0), "r"(a1) : "memory");
}
