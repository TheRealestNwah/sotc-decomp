/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosTransCurrentMatrix(float *src)
{
    __asm__ __volatile__(
                         "lqc2 vf8, 0x0(%0)\n"
                         "vmulax.xyzw ACC, vf1, vf8x\n"
                         "vmadday.xyzw ACC, vf2, vf8y\n"
                         "vmaddaz.xyzw ACC, vf3, vf8z\n"
                         "vmaddw.xyzw vf4, vf4, vf0w\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(src) : "memory");
}
