/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosPopCurrentMatrix(void)
{
    __asm__ __volatile__(
                         "vlqd.xyzw vf4, (--vi15)\n"
                         "vlqd.xyzw vf3, (--vi15)\n"
                         "vlqd.xyzw vf2, (--vi15)\n"
                         "vlqd.xyzw vf1, (--vi15)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : :  : "memory");
}
