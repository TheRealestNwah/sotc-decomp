/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosGetDRandomVector(float *dst)
{
    __asm__ __volatile__(
                         "vrnext.x vf5, R\n"
                         "vrnext.y vf5, R\n"
                         "vrnext.z vf5, R\n"
                         "vsubw.xyz vf5, vf5, vf0w\n"
                         "vadd.xyz vf5, vf5, vf5\n"
                         "vsubw.xyz vf5, vf5, vf0w\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(dst) : "memory");
}
