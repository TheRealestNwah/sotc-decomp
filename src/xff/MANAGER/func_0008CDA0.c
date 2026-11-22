extern void glBegin(int);
extern void glEnd(void);
extern void glVertex3f(float, float, float);
extern void iosGetSinCosf(float *out, float angle);

#define VSCALE(v, s) \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n" \
                         "qmtc2.ni %1, vf6\n" \
                         "vmulx.xyz vf5, vf5, vf6x\n" \
                         "sqc2 vf5, 0x0(%0)\n" \
                         : : "r"(v), "r"(s) : "memory")

static void func_0008CDA0(float range, float scale, float step, int nlon, int nlat)
{
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float e[4] __attribute__((aligned(16)));
    float t, p, dt, dt2;

    dt = 3.1415926f / (float)nlon;
    for (t = 0.0f; t < 3.1415926f; t += dt) {
        iosGetSinCosf(a, t);
        glBegin(2);
        for (p = -range; p < range; p += step) {
            iosGetSinCosf(b, p);
            VSCALE(b, scale);
            glVertex3f(a[1] * b[1], a[0] * b[1], b[0]);
        }
        iosGetSinCosf(b, range);
        VSCALE(b, scale);
        glVertex3f(a[1] * b[1], a[0] * b[1], b[0]);
        glEnd();
    }
    iosGetSinCosf(b, range);
    glBegin(2);
    for (p = 0.0f; p <= 6.2831852f; p += step) {
        float s;
        iosGetSinCosf(c, p);
        s = scale * b[1];
        VSCALE(c, s);
        glVertex3f(c[0], c[1], scale * b[0]);
    }
    glEnd();
    dt2 = 3.1415926f / (float)nlat;
    for (t = 0.0f; t < range; t += dt2) {
        iosGetSinCosf(d, t);
        VSCALE(d, scale);
        glBegin(2);
        for (p = 0.0f; p <= 6.2831852f; p += step) {
            iosGetSinCosf(e, p);
            glVertex3f(e[0] * d[1], e[1] * d[1], d[0]);
        }
        glEnd();
    }
}
