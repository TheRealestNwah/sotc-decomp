/* The empty noreorder block stops the assembler from moving the final sqc2
   into the return delay slot, as in the original. */
void iosScaleMatrixV(float *dst, float *src, float *s)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "lqc2 vf8, 0x0(%2)\n"
                         "vmulx.xyzw vf14, vf14, vf8x\n"
                         "vmuly.xyzw vf15, vf15, vf8y\n"
                         "vmulz.xyzw vf16, vf16, vf8z\n"
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         "sqc2 vf17, 0x30(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}
