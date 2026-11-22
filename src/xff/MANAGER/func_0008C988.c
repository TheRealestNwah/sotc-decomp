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

/*
 * Parked: 4 diffs (2 per loop). Remaining: in both loops the second
 * iosGetSinCosf call takes its argument from the hoisted copy of &b
 * ($s0) instead of recomputing addiu $a0,$sp,0x10 in the delay slot.
 */
#ifdef NONMATCHING
static inline void vtx(float *v, float ang, float r, float y)
{
    float *p;
    iosGetSinCosf(v, ang);
    p = v;
    VSCALE(p, r);
    glVertex3f(v[1], y, v[0]);
}

static inline void vtx2(float *v, float ang, float r, float y)
{
    iosGetSinCosf(v, ang);
    VSCALE(v, r);
    glVertex3f(v[1], y, v[0]);
}

static void func_0008C988(int n, float r0, float r1, float range, float y)
{
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float e[4] __attribute__((aligned(16)));
    float f[4] __attribute__((aligned(16)));
    float t, dt;

    glBegin(1);
    vtx(a, range, r0, y);
    vtx(b, range, r1, y);
    vtx(c, -range, r0, y);
    vtx(d, -range, r1, y);
    vtx(e, 0.0f, r0, y);
    vtx(f, 0.0f, r1, y);
    glEnd();
    dt = 3.1415926f / (float)n;
    glBegin(1);
    for (t = 0.0f; t < range; t += dt) {
        vtx(a, t, r0, y);
        vtx2(b, t, r1, y);
    }
    for (t = 0.00001f; t < range; t += dt) {
        vtx(a, -t, r0, y);
        vtx2(b, -t, r1, y);
    }
    glEnd();
}
#endif
