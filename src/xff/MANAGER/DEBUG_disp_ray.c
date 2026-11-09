/* Parked: 62 words off, FP callee-save register numbering (alpha lands in $f21, the 0.2f constant in $f20) and stack slot order of the colour arrays. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
extern char UnitMatrix[];
extern void glDrawLineStrip(s128 *, int, void *, float *, int);
extern void glDrawNull(s128 *, float *, int, int);
extern void *memset(void *, int, unsigned int);

void DEBUG_disp_ray(s128 *a, s128 *b, int mode, s128 *c, float alpha, int t0)
{
    s128 pts[2];
    float c0[4], c1[4], c2[4], c3[4], c4[4], z[4];

    c0[0] = 1.0f;
    c0[1] = 0.2f;
    c0[2] = 0.2f;
    c0[3] = alpha;
    c1[0] = 0.2f;
    c1[1] = 0.2f;
    c1[2] = 1.0f;
    c1[3] = alpha;
    if (mode != 0) {
        c2[0] = 1.0f;
        c2[1] = 1.0f;
        c2[2] = 0.2f;
        c2[3] = alpha;
        memset(z, 0, 0x10);
        z[3] = alpha;
        c3[0] = 0.2f;
        c3[1] = 1.0f;
        c3[2] = 1.0f;
        c3[3] = alpha;
        pts[0] = *a;
        pts[1] = *c;
        glDrawLineStrip(pts, 2, UnitMatrix, c2, t0);
        pts[0] = *c;
        pts[1] = *b;
        glDrawLineStrip(pts, 2, UnitMatrix, z, t0);
        glDrawNull(c, c3, t0, 0x3F800000);
    } else {
        c4[0] = 0.2f;
        c4[1] = 1.0f;
        c4[2] = 0.2f;
        c4[3] = alpha;
        pts[0] = *a;
        pts[1] = *b;
        glDrawLineStrip(pts, 2, UnitMatrix, c4, t0);
    }
    glDrawNull(a, c0, t0, 0x3F800000);
    glDrawNull(b, c1, t0, 0x3F800000);
}
#else
extern void DEBUG_disp_ray(void *, void *, int, void *, float, int);
#endif
