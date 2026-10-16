/* Center of three vertices, with the greatest squared radius in w. */
void iasmCalcCollisionMultiDepSurfBoundarySub(float *out, const float *a,
                                            const float *b, const float *c,
                                            float weight)
{
    __asm__ __volatile__(
        "lqc2 vf04, 0(%1)\n"
        "lqc2 vf05, 0(%2)\n"
        "lqc2 vf06, 0(%3)\n"
        "mfc1 $8, %4\n"
        "qmtc2 $8, vf08\n"
        "vadd.xyz vf07, vf04, vf05\n"
        "vadd.xyz vf07, vf07, vf06\n"
        "vmulx.xyz vf07, vf07, vf08x\n"
        "vsub.xyz vf04, vf04, vf07\n"
        "vmul.xyz vf04, vf04, vf04\n"
        "vaddy.x vf04, vf04, vf04y\n"
        "vaddz.x vf04, vf04, vf04z\n"
        "vsub.xyz vf05, vf05, vf07\n"
        "vmul.xyz vf05, vf05, vf05\n"
        "vaddy.x vf05, vf05, vf05y\n"
        "vaddz.x vf05, vf05, vf05z\n"
        "vmaxx.x vf08, vf04, vf05x\n"
        "vsub.xyz vf06, vf06, vf07\n"
        "vmul.xyz vf06, vf06, vf06\n"
        "vaddy.x vf06, vf06, vf06y\n"
        "vaddz.x vf06, vf06, vf06z\n"
        "vmaxx.x vf08, vf08, vf06x\n"
        "vmulx.w vf07, vf00, vf08x\n"
        "sqc2 vf07, 0(%0)\n"
        ".set noreorder\n.set reorder\n"
        : : "r"(out), "r"(a), "r"(b), "r"(c), "f"(weight)
        : "$8", "memory");
}
