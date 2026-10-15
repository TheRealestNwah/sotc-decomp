/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosPushCurrentMatrix(void)
{
    __asm__ __volatile__(
                         "vsqi.xyzw vf1, (vi15++)\n"
                         "vsqi.xyzw vf2, (vi15++)\n"
                         "vsqi.xyzw vf3, (vi15++)\n"
                         "vsqi.xyzw vf4, (vi15++)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : :  : "memory");
}
