/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosGetRandomVector0(float *dst)
{
    __asm__ __volatile__(
                         "vrnext.xyz vf5, R\n"
                         "vsubw.xyz vf5, vf5, vf0w\n"
                         "vrxor R, vf5x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(dst) : "memory");
}
