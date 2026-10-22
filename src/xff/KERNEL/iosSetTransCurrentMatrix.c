void iosSetTransCurrentMatrix(void *a0)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf8, 0x0(%0)\n"
        "vmove.xyzw vf4, vf8\n"
        ".set reorder\n"
        : : "r"(a0) : "memory");
}
