typedef int s128 __attribute__((mode(TI)));
extern int D_000409B0;
extern s128 B_00054800[];

/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void InitQuaternionDrive(void)
{
    D_000409B0 = 0;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(B_00054800) : "memory");
}
