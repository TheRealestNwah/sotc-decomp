extern char gcGlobalVar[];
extern int DebugGetGlobalDiffWith2ndController(float *);

int DebugGlobalMoveWith2ndController(float *out, float *in)
{
    float d[4];
    float s;
    int r;

    r = DebugGetGlobalDiffWith2ndController(d);
    s = *(float *)(gcGlobalVar + 0x170) * 30.0f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(s) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(d) : "memory");
    return r;
}
