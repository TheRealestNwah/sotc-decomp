void iosGetRandomVector(void *a0)
{
    __asm__ __volatile__(".set noreorder\n"
        "vrnext.x vf5, R\n"
        "vrnext.y vf5, R\n"
        "vrnext.z vf5, R\n"
        "vsubw.xyz vf5, vf5, vf0w\n"
        "sqc2 vf5, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0) : "memory");
}
