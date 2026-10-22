typedef int s128 __attribute__((mode(TI)));

extern s128 B_00054800[];
extern int D_000409B0;

void MultiCurrentQuaternionL(s128 *q)
{
    s128 *c = &B_00054800[D_000409B0];

    __asm__ __volatile__(".set noreorder
"
                         "lqc2 vf11, 0(%1)\n"
                         "lqc2 vf12, 0(%0)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0(%0)\n"
                         : : "r"(c), "r"(q) : "memory");
}
