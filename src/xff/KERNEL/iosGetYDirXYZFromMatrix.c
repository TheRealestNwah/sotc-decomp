/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosGetYDirXYZFromMatrix(float *dst, float *src)
{
    __asm__ __volatile__(
                         "lqc2 vf4, 0x10(%1)\n"
                         "vsub.w vf4, vf4, vf4\n"
                         "sqc2 vf4, 0x0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(dst), "r"(src) : "memory");
}
