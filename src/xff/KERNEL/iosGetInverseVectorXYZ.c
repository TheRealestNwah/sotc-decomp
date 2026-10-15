/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosGetInverseVectorXYZ(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2 %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(dst), "r"(src), "r"(-1.0f) : "memory");
}
