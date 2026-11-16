/* Parked: 1 diff, same size (118 words). Debug draw of a circle sweep: fills the layer 0x17 state, draws two vertical axis lines (z = B then A), calls func_0008CDA0 twice, then loops ang over 0..2*pi in pi/2 steps: sincos of ang and of step, two VU0 scalings of the step sincos by A and B, and one line segment per pass. Prototype order of func_0008CDA0 (float, float, float, int, int) and iosGetSinCosf (float, float *) fixes the argument setup. Remaining: the second iosGetSinCosf call takes its address as a fresh `addiu $a0, $sp, 0x10`; ours reuses the s0 copy. A 25-minute permuter run found nothing better. */
#ifdef NONMATCHING
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void glColor4f(float, float, float, float);
extern void glBegin(int);
extern void glEnd(void);
extern void glBlendFunc(int, int);
extern void glVertex3f(float, float, float);
extern void iosGetSinCosf(float angle, float *out);
extern void func_0008CDA0(float, float, float, int, int);

static void func_0008D058(float *color, float step, float A, float B)
{
    float ang;
    float sc[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));

    iosDlPushLayer(0x17);
    glColor4f(color[0], color[1], color[2], color[3]);
    glBegin(8);
    glBlendFunc(5, 6);
    glEnd();
    glBegin(1);
    glVertex3f(0.0f, 0.0f, B);
    glVertex3f(0.0f, 0.0f, A);
    glEnd();
    func_0008CDA0(step, A, 0.31415922f, 2, 4);
    func_0008CDA0(step, B, 0.31415922f, 2, 4);
    ang = 0.0f;
    do {
        iosGetSinCosf(ang, sc);
        iosGetSinCosf(step, a);
        glBegin(1);
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "qmtc2.ni %2, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%1)\n"
                             : : "r"(a), "r"(b), "r"(A) : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "qmtc2.ni %2, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%1)\n"
                             : : "r"(a), "r"(c), "r"(B) : "memory");
        ang += 1.5707963f;
        glVertex3f(sc[1] * c[1], sc[0] * c[1], c[0]);
        glVertex3f(sc[1] * b[1], sc[0] * b[1], b[0]);
        glEnd();
    } while (ang < 6.2831853f);
    iosDlPopLayer();
}
#endif
