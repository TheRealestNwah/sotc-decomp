void CalcFootVec(float *out, float *a, float *b, float *n)
{
    float tmp[4] __attribute__((aligned(16)));
    float d;
    float nn;
    float s;

    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "vsub.xyzw vf6, vf4, vf5\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(tmp), "r"(b), "r"(a) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "vmul.xyz vf5, vf4, vf5\n"
                         "vaddy.x vf5, vf5, vf5y\n"
                         "vaddz.x vf5, vf5, vf5z\n"
                         "qmfc2.ni $2, vf5\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(tmp), "r"(n) : "$2");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyz vf5, vf4, vf4\n"
                         "vaddy.x vf5, vf5, vf5y\n"
                         "vaddz.x vf5, vf5, vf5z\n"
                         "qmfc2.ni $2, vf5\n"
                         "mtc1 $2, %0\n"
                         : "=f"(nn) : "r"(n) : "$2");
    s = -d / nn;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "lqc2 vf4, 0x0(%2)\n"
                         "mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf5\n"
                         "vmulx.xyzw vf6, vf4, vf5x\n"
                         "vadd.xyzw vf5, vf6, vf7\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(tmp), "r"(n), "f"(s) : "$8", "memory");
}
