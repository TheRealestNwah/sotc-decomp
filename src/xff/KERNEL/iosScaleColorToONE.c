typedef int s128 __attribute__((mode(TI)));
extern s128 RO_00042F90[];

/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosScaleColorToONE(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "vmul.xyzw vf5, vf4, vf5\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(dst), "r"(src), "r"(RO_00042F90) : "memory");
}
