/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosUnitRotation(float *dst)
{
    __asm__ __volatile__(
                         "vmove.xyzw vf17, vf0\n"
                         "vmr32.xyzw vf16, vf17\n"
                         "vmr32.xyzw vf15, vf16\n"
                         "vmr32.xyzw vf14, vf15\n"
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(dst) : "memory");
}
