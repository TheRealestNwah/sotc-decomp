/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosITOF0Vector(float *dst, float *src)
{
    __asm__ __volatile__(
                         "lqc2 vf5, 0x0(%1)\n"
                         "vitof0.xyzw vf6, vf5\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(dst), "r"(src) : "memory");
}
