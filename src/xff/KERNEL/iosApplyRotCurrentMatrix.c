void iosApplyRotCurrentMatrix(void *a0, void *a1)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf8, 0x0(%1)\n"
        "vmulax.xyzw ACC, vf1, vf8x\n"
        "vmadday.xyzw ACC, vf2, vf8y\n"
        "vmaddaz.xyzw ACC, vf3, vf8z\n"
        "vmaddw.xyzw vf10, vf0, vf8w\n"
        "sqc2 vf10, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0), "r"(a1) : "memory");
}
