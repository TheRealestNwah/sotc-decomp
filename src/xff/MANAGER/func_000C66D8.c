typedef int s128 __attribute__((mode(TI)));

extern float *D_001370D8;

static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}
static inline void vecAddXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}
static inline void vecSubXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}
static inline void vecCross(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static void func_000C66D8(float *o, float *acc, float *drag, float *ext, void *unused, char *mode, char *prm)
{
    s128 tmp;
    float d = o[0x88 / 4] * D_001370D8[0];
    int m;

    vecScale((float *)&tmp, o + 4, D_001370D8[0]);
    vecAddXYZ(o, o, (float *)&tmp);
    vecScale((float *)&tmp, acc, D_001370D8[1]);
    vecAddXYZ(o, o, (float *)&tmp);
    vecScale((float *)&tmp, drag, d);
    vecAddXYZ(o, o, (float *)&tmp);
    m = *(int *)mode;
    if (m == 1 || m == 3) {
        vecScale((float *)&tmp, ext, o[0x48 / 4]);
        vecAddXYZ(o, o, (float *)&tmp);
    }
    if (*(int *)(mode + 0xC8)) {
        s128 sc, rel, cr;
        float r;
        float x;
        int i;

        vecScale((float *)&sc, drag + 0xC, o[0x80 / 4] * D_001370D8[0]);
        vecSubXYZ((float *)&rel, o, drag + 4);
        vecCross((float *)&cr, (float *)&sc, (float *)&rel);
        vecAddXYZ(o, o, (float *)&cr);
        if (*(int *)(mode + 0xC8) == 1 || 0.0f <= o[0x80 / 4]) {
            o[0x80 / 4] = o[0x80 / 4] + *(float *)(prm + 0xD4) * D_001370D8[0];
        } else {
            o[0x80 / 4] = o[0x80 / 4] - *(float *)(prm + 0xD4) * D_001370D8[0];
        }
        x = *(float *)(prm + 0xD8);
        r = 1.0f;
        if (x != 1.0f) {
            for (i = 0; i < *(int *)((char *)D_001370D8 + 0xC); i++)
                r *= x;
        }
        o[0x80 / 4] *= r;
    }
}
