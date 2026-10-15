void GetPlaneFittingVector(float *out, float *plane, float *p)
{
    float d;
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vaddw.x vf07, vf00, vf00w\n"
                         "vmul.xyz vf06, vf05, vf06\n"
                         "vaddax.x ACC, vf00, vf06x\n"
                         "vmadday.x ACC, vf07, vf06y\n"
                         "vmaddz.x vf06, vf07, vf06z\n"
                         "qmfc2 %0, vf06\n"
                         : "=r"(d) : "r"(plane), "r"(p));
    d = -d;
    __asm__ __volatile__("qmtc2 %2, vf30\n"
                         "lqc2 vf29, 0(%1)\n"
                         "vmulx.xyzw vf31, vf29, vf30x\n"
                         "lqc2 vf29, 0(%3)\n"
                         "vmove.xyzw vf30, vf31\n"
                         "vmove.xyzw vf31, vf29\n"
                         "vadd.xyz vf31, vf29, vf30\n"
                         "sqc2 vf31, 0(%0)\n"
                         ".set noreorder\n.set reorder\n"
                         : : "r"(out), "r"(plane), "r"(d), "r"(p) : "memory", "$2", "$3", "$7");
}
