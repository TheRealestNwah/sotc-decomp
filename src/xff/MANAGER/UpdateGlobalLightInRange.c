void UpdateGlobalLightInRange(char *l, char *g)
{
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" "qmtc2 %2, vf06\n" "vmulx.xyzw vf05, vf05, vf06x\n" "sqc2 vf05, 0x0(%0)\n"
                         ".set noreorder\n.set reorder\n"
                         : : "r"(l + 0xE0), "r"(g + 0x30), "r"(0.5f) : "memory");
}
