void iosCubicInterVectorXYZ(float *out, float *a, float *b, float *w, float t)
{
    float s = 1.0f - t;
    float f = s * s * w[0] + (s + s) * t * w[1] + t * t * w[2];
    __asm__ __volatile__("qmtc2 %3, vf07\n"
                         "lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vsubx.w vf08, vf00, vf07x\n"
                         "vmulax.xyz ACC, vf05, vf07x\n"
                         "vmaddw.xyz vf05, vf06, vf08w\n"
                         "sqc2 vf05, 0(%0)\n"
                         ".set noreorder\n.set reorder\n"
                         : : "r"(out), "r"(a), "r"(b), "r"(f) : "memory", "$2", "$3", "$7");
}
