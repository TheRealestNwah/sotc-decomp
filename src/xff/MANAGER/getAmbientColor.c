extern int getAmbientColorC(float *);

int getAmbientColor(float *c)
{
    float s = 0.0039215684f;
    int r = getAmbientColorC(c);
    __asm__ __volatile__("lqc2 vf05, 0(%0)\n"
                         "qmtc2 %1, vf06\n"
                         "vmulx.xyzw vf05, vf05, vf06x\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(c), "r"(s) : "memory");
    return r;
}
