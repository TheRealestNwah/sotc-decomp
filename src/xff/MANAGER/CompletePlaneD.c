void CompletePlaneD(float *plane, float *point)
{
    __asm__ __volatile__("lqc2 vf04, 0x0(%0)\n"
                         "lqc2 vf05, 0x0(%1)\n"
                         "vmul.xyz vf05, vf04, vf05\n"
                         "vaddy.x vf05, vf05, vf05y\n"
                         "vaddz.x vf05, vf05, vf05z\n"
                         "vsubw.xyzw vf06, vf00, vf00w\n"
                         "vsubx.w vf04, vf06, vf05x\n"
                         "sqc2 vf04, 0x0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(plane), "r"(point) : "memory");
}
