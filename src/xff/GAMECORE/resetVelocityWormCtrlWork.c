void resetVelocityWormCtrlWork(void *a0, char *a1)
{
    *(int *)(a1 + 0x9C) = 0;
    *(int *)(a1 + 0x98) = 0;
    *(int *)(a1 + 0xB4) = 0;
    __asm__ __volatile__(".set noreorder\n"
        "sqc2 vf0, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a1 + 0xA0) : "memory");
}
