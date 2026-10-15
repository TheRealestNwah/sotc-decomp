typedef int s128 __attribute__((mode(TI)));

extern int D_000409B0;
extern s128 B_00054800[];

/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void InvertCurrentQuaternion(void)
{
    s128 *q = &B_00054800[D_000409B0];

    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(q) : "memory");
}
