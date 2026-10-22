void GetPlaneFittingVector(void *dst, void *p, void *n)
{
    float d;

    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni %0, vf6\n"
                         ".set reorder\n"
                         : "=r"(d) : "r"(p), "r"(n));
    d = -d;
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf30\n"
                         "lqc2 vf29, 0x0(%1)\n"
                         "vmulx.xyzw vf31, vf29, vf30x\n"
                         "lqc2 vf29, 0x0(%2)\n"
                         "vmove.xyzw vf30, vf31\n"
                         "vmove.xyzw vf31, vf29\n"
                         "vadd.xyz vf31, vf29, vf30\n"
                         "sqc2 vf31, 0x0(%0)\n"
                         ".set reorder\n"
                         : : "r"(dst), "r"(p), "r"(n), "f"(d) : "$8", "memory");
}
