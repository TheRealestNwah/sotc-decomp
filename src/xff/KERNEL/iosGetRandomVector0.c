void iosGetRandomVector0(void *a0)
{
    __asm__ __volatile__(".set noreorder\n"
        "vrnext.xyz vf5, R\n"
        "vsubw.xyz vf5, vf5, vf0w\n"
        "vrxor R, vf5x\n"
        "sqc2 vf5, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0) : "memory");
}
