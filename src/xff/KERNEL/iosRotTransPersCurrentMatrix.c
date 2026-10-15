/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosRotTransPersCurrentMatrix(float *dst, float *src)
{
    __asm__ __volatile__(
                         "lqc2 vf8, 0x0(%1)\n"
                         "vmulax.xyzw ACC, vf1, vf8x\n"
                         "vmadday.xyzw ACC, vf2, vf8y\n"
                         "vmaddaz.xyzw ACC, vf3, vf8z\n"
                         "vmaddw.xyzw vf10, vf4, vf8w\n"
                         "vdiv Q, vf0w, vf10w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf10, vf10, Q\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(dst), "r"(src) : "memory");
}
