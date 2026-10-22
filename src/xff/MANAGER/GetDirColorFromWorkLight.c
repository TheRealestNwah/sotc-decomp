typedef int s128 __attribute__((mode(TI)));

void GetDirColorFromWorkLight(s128 *a0, void *a1, char *a2)
{
    *a0 = *(s128 *)(a2 + 0x10);
    __asm__ __volatile__(".set noreorder
"
                         "lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(a1), "r"(a2 + 0x20), "r"(1.0f / 255.0f) : "memory");
}
