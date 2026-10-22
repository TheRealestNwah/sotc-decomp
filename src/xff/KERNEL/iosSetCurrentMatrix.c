void iosSetCurrentMatrix(void *a0)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf1, 0x0(%0)\n"
        "lqc2 vf2, 0x10(%0)\n"
        "lqc2 vf3, 0x20(%0)\n"
        "lqc2 vf4, 0x30(%0)\n"
        ".set reorder\n"
        : : "r"(a0) : "memory");
}
