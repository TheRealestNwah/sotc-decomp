float GetPointDistanceSquareFromUnnormalizedPlane(float *plane, float *p)
{
    float d;
    float l;
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n"
                         "lqc2 vf06, 0x0(%2)\n"
                         "vaddw.x vf07, vf00, vf00w\n"
                         "vmul.xyz vf06, vf05, vf06\n"
                         "vaddax.x ACC, vf00, vf06x\n"
                         "vmadday.x ACC, vf07, vf06y\n"
                         "vmaddz.x vf06, vf07, vf06z\n"
                         "vaddw.x vf06, vf06, vf05w\n"
                         "qmfc2 $2, vf06\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(plane), "r"(p) : "$2");
    __asm__ __volatile__("lqc2 vf07, 0x0(%1)\n"
                         "vmul.xyz vf07, vf07, vf07\n"
                         "vaddy.x vf07, vf07, vf07y\n"
                         "vaddz.x vf07, vf07, vf07z\n"
                         "qmfc2 $2, vf07\n"
                         "mtc1 $2, %0\n"
                         : "=f"(l) : "r"(plane) : "$2");
    return d * d / l;
}
