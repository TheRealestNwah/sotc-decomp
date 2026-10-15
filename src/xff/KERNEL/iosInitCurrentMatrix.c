/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosInitCurrentMatrix(void)
{
    __asm__ __volatile__(
                         "vmove.xyzw vf4, vf0\n"
                         "vmr32.xyzw vf3, vf4\n"
                         "vmr32.xyzw vf2, vf3\n"
                         "vmr32.xyzw vf1, vf2\n"
                         "viaddi vi15, vi0, 0x0\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : :  : "memory");
}
