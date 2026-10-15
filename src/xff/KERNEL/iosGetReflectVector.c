/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosGetReflectVector(float *dst, float *src0, float *src1)
{
    __asm__ __volatile__(
                         "lqc2 vf4, 0x0(%1)\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "vmul.xyz vf7, vf4, vf5\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vadd.xyzw vf6, vf0, vf0\n"
                         "vmulx.xyz vf5, vf5, vf7x\n"
                         "vmulw.xyz vf5, vf5, vf6w\n"
                         "vsub.xyz vf4, vf4, vf5\n"
                         "sqc2 vf4, 0x0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(dst), "r"(src0), "r"(src1) : "memory");
}
