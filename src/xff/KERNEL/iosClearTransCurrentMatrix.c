/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosClearTransCurrentMatrix(void)
{
    __asm__ __volatile__(
                         "vmove.xyzw vf4, vf0\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : :  : "memory");
}
