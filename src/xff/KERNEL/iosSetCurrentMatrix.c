/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosSetCurrentMatrix(float *src)
{
    __asm__ __volatile__(
                         "lqc2 vf1, 0x0(%0)\n"
                         "lqc2 vf2, 0x10(%0)\n"
                         "lqc2 vf3, 0x20(%0)\n"
                         "lqc2 vf4, 0x30(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(src) : "memory");
}
