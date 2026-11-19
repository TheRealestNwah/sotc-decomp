extern int *GetGlDebugSw(void);
extern void disphalfarc(void *color, float angle, float radius);
extern void glDisable(int);
extern void glEnable(int);
extern void glLoadMatrixf(void *);
extern void kprintfContextCentering(void *ctx, char *fmt, ...);

/* Clamps s to [-lim, lim] into d; the first two arcs use it in place, the
   last two through clampAngle (register allocation differs). */
#define CL(d, s, lim)                                        do {                                                         if ((s) < 0.0f ? (s) <= -(lim) : (lim) <= (s)) {             d = (lim);                                               if ((s) < 0.0f)                                              d = -(lim);                                      } else                                                       d = (s);                                         } while (0)

static inline float clampAngle(float s, float lim)
{
    float d;

    if (s < 0.0f ? s <= -lim : lim <= s) {
        d = lim;
        if (s < 0.0f)
            d = -lim;
    } else
        d = s;
    return d;
}

/* Debug overlay: draws the angle arcs for o and prints them. */
static void func_00002DB8(char *o, void *ctx)
{
    float mtx[16] __attribute__((aligned(16)));
    typedef struct { float f[4]; } __attribute__((aligned(16))) Col;
    char **sub = (char **)(o + 0x1C0);
    float t, a, r;

    if (*GetGlDebugSw() != 0) {
    {
    register float *m asm("$2") = mtx;
    register void *q asm("$3") = *(void **)(o + 0x13C);
    register void *p asm("$4") = *(void **)(o + 0x134);
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%2)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         "lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         :
                         : "r"(m), "r"(p), "r"(q)
                         : "memory");
    }
    glLoadMatrixf(mtx);
    glEnable(3);
    glEnable(7);
    glDisable(8);
    if (*sub != 0) {
    t = *(int *)(*sub + 0x74);

    a = t < 0.0f ? 3.1415926f : t * 0.0174532933f;
    CL(r, a, 3.1415926f);
    {
    Col c0 = { { 0.099999996f, 0.29999999f, 0.19999999f, 0.099999996f } };
    disphalfarc(&c0, r, *(float *)(o + 0xE34));
    disphalfarc(&c0, -r, *(float *)(o + 0xE34));
    }

    a = t < 0.0f ? 3.1415926f : t * 0.0174532933f / 30.0f;
    CL(r, a, 3.1415926f);
    {
    Col c1 = { { 0.099999996f, 0.59999998f, 0.19999999f, 0.29999999f } };
    disphalfarc(&c1, r, *(float *)(o + 0xE34));
    disphalfarc(&c1, -r, *(float *)(o + 0xE34));
    }

    a = -(*(float *)(o + 0x72C) * 0.0174532933f);
    r = clampAngle(a, 6.2831852f);
    {
    Col c2 = { { 0.099999996f, 0.29999999f, 0.5f, 0.39999999f } };
    disphalfarc(&c2, r, *(float *)(o + 0xE34) * 0.7f);
    }

    a = -(*(float *)(o + 0x72C) * 0.0174532933f) / 30.0f;
    r = clampAngle(a, 6.2831852f);
    {
    Col c3 = { { 0.099999996f, 0.19999999f, 0.29999999f, 0.59999998f } };
    disphalfarc(&c3, r, *(float *)(o + 0xE34) * 0.7f);
    }

    if (t < 0.0f)
        kprintfContextCentering(ctx, "\xb2\xf3\xc5\xbe\xa5\xea\xa5\xdf\xa5\xc3\xa5\xc8: \xa1\xe7/ \xc9\xc3\n");
    else
        kprintfContextCentering(ctx, "\xb2\xf3\xc5\xbe\xa5\xea\xa5\xdf\xa5\xc3\xa5\xc8: %.2f\xa1\xeb/\xc9\xc3(%.2f)\n", t,
                                *(float *)(o + 0x72C));
    }
    }
}
