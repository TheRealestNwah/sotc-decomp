/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosGetCurrentMatrixTrans(float *dst)
{
    __asm__ __volatile__(
                         "sqc2 vf4, 0x0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(dst) : "memory");
}
