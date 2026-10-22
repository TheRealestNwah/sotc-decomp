void UpdateGlobalLightInRange(char *a0, char *a1)
{
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(a0 + 0xE0), "r"(a1 + 0x30), "r"(0.5f) : "memory");
}
