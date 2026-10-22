void iosApplyRotMatrix(void *a0, void *a1, void *a2)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf8, 0x0(%2)\n"
        "lqc2 vf14, 0x0(%1)\n"
        "lqc2 vf15, 0x10(%1)\n"
        "lqc2 vf16, 0x20(%1)\n"
        "vmulax.xyzw ACC, vf14, vf8x\n"
        "vmadday.xyzw ACC, vf15, vf8y\n"
        "vmaddaz.xyzw ACC, vf16, vf8z\n"
        "vmaddw.xyzw vf10, vf0, vf8w\n"
        "sqc2 vf10, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0), "r"(a1), "r"(a2) : "memory");
}
