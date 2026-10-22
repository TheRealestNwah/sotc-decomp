typedef int s128 __attribute__((mode(TI)));

extern s128 B_00054800[];
extern int D_000409B0;

void InvertCurrentQuaternion(void)
{
    s128 *c = &B_00054800[D_000409B0];

    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf11, 0(%0)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0(%0)\n"
                         : : "r"(c) : "memory");
}
