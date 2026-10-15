/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosSetTransCurrentMatrix(float *src)
{
    __asm__ __volatile__(
                         "lqc2 vf8, 0x0(%0)\n"
                         "vmove.xyzw vf4, vf8\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(src) : "memory");
}
