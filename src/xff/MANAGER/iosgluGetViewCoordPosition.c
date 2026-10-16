typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
typedef struct { Vec4 r[4]; } Mat4;
extern Mat4 B_00147AA0[];
extern int B_001482A0;
extern char *D_00130480;

void iosgluGetViewCoordPosition(float *out, float *v)
{
    __asm__ __volatile__("lqc2 vf10, 0x0(%1)\n"
                         "lqc2 vf11, 0x0(%2)\n"
                         "lqc2 vf12, 0x10(%2)\n"
                         "lqc2 vf13, 0x20(%2)\n"
                         "lqc2 vf14, 0x30(%2)\n"
                         "lqc2 vf15, 0x0(%3)\n"
                         "lqc2 vf16, 0x10(%3)\n"
                         "lqc2 vf17, 0x20(%3)\n"
                         "lqc2 vf18, 0x30(%3)\n"
                         "vmulax.xyzw ACC, vf11, vf10x\n"
                         "vmadday.xyzw ACC, vf12, vf10y\n"
                         "vmaddaz.xyzw ACC, vf13, vf10z\n"
                         "vmaddw.xyzw vf19, vf14, vf00w\n"
                         "vmulax.xyzw ACC, vf15, vf19x\n"
                         "vmadday.xyzw ACC, vf16, vf19y\n"
                         "vmaddaz.xyzw ACC, vf17, vf19z\n"
                         "vmaddw.xyzw vf20, vf18, vf19w\n"
                         "vdiv Q, vf00w, vf20w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf20, vf20, Q\n"
                         "vmulq.w vf20, vf00, Q\n"
                         "sqc2 vf20, 0x0(%0)\n"
                         : : "r"(out), "r"(v), "r"(&B_00147AA0[B_001482A0]), "r"(D_00130480 + 0x660) : "memory");
    out[0] -= 2048.0f;
    out[1] -= 2048.0f;
}
