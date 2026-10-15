float GetDistanceSquareXZ(float *a, float *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n"
                         "lqc2 vf06, 0x0(%2)\n"
                         "vsub.xyzw vf07, vf05, vf06\n"
                         "vmul.xz vf07, vf07, vf07\n"
                         "vaddz.x vf07, vf07, vf07z\n"
                         "qmfc2 %0, vf07\n"
                         : "=r"(d) : "r"(a), "r"(b));
    return d;
}
