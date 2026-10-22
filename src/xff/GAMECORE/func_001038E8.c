static void func_001038E8(char *p)
{
    *(int *)(p + 0x224) = 0;
    *(int *)(p + 0x22C) = 0;
    *(int *)(p + 0x228) = 0;
    *(int *)(p + 0x230) = 0;
    *(int *)(p + 0x234) = 0;
    __asm__ __volatile__(".set noreorder\n"
                         "sqc2 vf0, 0x0(%0)\n"
                         ".set reorder\n"
                         : : "r"(p + 0x240) : "memory");
    __asm__ __volatile__(".set noreorder\n"
                         "sqc2 vf0, 0x0(%0)\n"
                         ".set reorder\n"
                         : : "r"(p + 0x260) : "memory");
}
