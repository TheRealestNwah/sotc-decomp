/* Parked draft: finds, among the control points of the ten camera-offset control tables in
   B_0019FCF8, the one nearest to a position (VU0 squared distance); when mode == 1 points that
   are essentially coincident with the query get a 64-unit bias. Writes the winner to out and
   returns whether any was found. Written from the m2c draft; not yet compared closely. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0xC];
    int count;
    float *points;
} CtrlTable;

extern CtrlTable *B_0019FCF8[10];
extern float RO_00180F60;
extern int GAMEUTIL_is_diff_nearly_equal_zero3D(Vec4 *, Vec4 *, float);

static inline float distSq(Vec4 *a, Vec4 *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni %0, vf7\n"
                         : "=r"(r) : "r"(a), "r"(b) : "memory");
    return r;
}

int get_nearest_camera_vs_ofst_cntrl_position(Vec4 *out, Vec4 *pos, int mode)
{
    float best = RO_00180F60;
    int found = 0;
    int t;

    for (t = 0; t < 10; t++) {
        CtrlTable *table = B_0019FCF8[t];
        if (table != 0) {
            int i;
            float *p = table->points;
            for (i = 0; i < table->count; i++, p += 3) {
                Vec4 cand __attribute__((aligned(16)));
                float d;

                cand.f[0] = p[0];
                cand.f[1] = p[1];
                cand.f[2] = p[2];
                cand.f[3] = 1.0f;
                d = distSq(pos, &cand);
                if (mode == 1) {
                    if (GAMEUTIL_is_diff_nearly_equal_zero3D(&cand, pos, 0.001f) == mode) {
                        d -= 64.0f;
                        if (d < 0.0f)
                            d = 0.0f;
                    }
                }
                if (d < best) {
                    best = d;
                    found = 1;
                    out->q = cand.q;
                }
            }
        }
    }
    return found;
}
#endif
