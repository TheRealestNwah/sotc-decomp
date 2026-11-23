typedef int s128 __attribute__((mode(TI)));

typedef struct {
    float off0, scale0, off1, scale1, off2, scale2;
    short *tbl;
} PackVec;
typedef union { float f[4]; short h[8]; s128 q; } VecU;

#define FETCH(o, i)                                                         \
    do {                                                                    \
        (o)->f[3] = 1.0f;                                                      \
        if (type != 0) {                                                    \
            if (type != 2) {                                                \
                float *fv = (float *)data + (i) * 3;                         \
                (o)->f[0] = fv[0];                                              \
                (o)->f[1] = fv[1];                                              \
                (o)->f[2] = fv[2];                                              \
            } else {                                                        \
                PackVec *p = data;                                          \
                short *s = p->tbl + (i) * 3;                                \
                (o)->f[0] = s[0] * p->scale0 * (1.0f / 32767.0f) + p->off0;    \
                (o)->f[1] = s[1] * p->scale1 * (1.0f / 32767.0f) + p->off1;    \
                (o)->f[2] = s[2] * p->scale2 * (1.0f / 32767.0f) + p->off2;    \
            }                                                               \
        } else {                                                            \
            float *c = data;                                                \
            (o)->f[0] = c[0];                                                  \
            (o)->f[1] = c[1];                                                  \
            (o)->f[2] = c[2];                                                  \
        }                                                                   \
    } while (0)

static void func_00033868(VecU *out, int type, void *data, int i0, int i1, float frac)
{
    if (frac == 0.0f) {
        if (data)
            FETCH(out, i0);
    } else {
        VecU v[2];
        if (data)
            FETCH(&v[0], i0);
        if (data)
            FETCH(&v[1], i1);
        __asm__ __volatile__("mfc1 $8, %3\n"
                             "qmtc2.ni $8, vf7\n"
                             "lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsubx.w vf8, vf0, vf7x\n"
                             "vmulax.xyz ACC, vf5, vf7x\n"
                             "vmaddw.xyz vf5, vf6, vf8w\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(out), "r"(&v[1]), "r"(&v[0]), "f"(frac) : "$8", "memory");
    }
}
