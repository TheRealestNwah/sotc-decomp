void iosGetCurrentMatrixTrans(void *a0)
{
    __asm__ __volatile__(".set noreorder\n"
        "sqc2 vf4, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0) : "memory");
}
