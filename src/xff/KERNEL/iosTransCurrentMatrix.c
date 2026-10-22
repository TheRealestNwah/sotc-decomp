void iosTransCurrentMatrix(void *a0)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf8, 0x0(%0)\n"
        "vmulax.xyzw ACC, vf1, vf8x\n"
        "vmadday.xyzw ACC, vf2, vf8y\n"
        "vmaddaz.xyzw ACC, vf3, vf8z\n"
        "vmaddw.xyzw vf4, vf4, vf0w\n"
        ".set reorder\n"
        : : "r"(a0) : "memory");
}
