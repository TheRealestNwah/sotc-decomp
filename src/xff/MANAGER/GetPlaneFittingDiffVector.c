void GetPlaneFittingDiffVector(float *out, float *plane, float *p)
{
    float d;
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vaddw.x vf07, vf00, vf00w\n"
                         "vmul.xyz vf06, vf05, vf06\n"
                         "vaddax.x ACC, vf00, vf06x\n"
                         "vmadday.x ACC, vf07, vf06y\n"
                         "vmaddz.x vf06, vf07, vf06z\n"
                         "vaddw.x vf06, vf06, vf05w\n"
                         "qmfc2 %0, vf06\n"
                         : "=r"(d) : "r"(plane), "r"(p));
    d = -d;
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "qmtc2 %2, vf06\n"
                         "vmulx.xyz vf05, vf05, vf06x\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(out), "r"(plane), "r"(d) : "memory");
    out[3] = 0.0f;
}
