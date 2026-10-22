void iosInitRandom(float a0)
{
    __asm__ __volatile__(".set noreorder\n"
        "mfc1 $6, %0\n"
        "qmtc2.ni $6, vf5\n"
        "vaddw.x vf6, vf5, vf0w\n"
        "vadd.x vf5, vf5, vf5\n"
        "vrinit R, vf5x\n"
        "vrxor R, vf6x\n"
        ".set reorder\n"
        : : "f"(a0) : "$6");
}
