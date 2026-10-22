void iosGetInverseVectorXYZ(void *dst, void *src)
{
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(-1.0f) : "memory");
}
