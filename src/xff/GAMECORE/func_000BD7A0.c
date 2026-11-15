/* Parked: 102 diffs (137 before). The empty-asm launder on the 0x8000 constant stops it being hoisted into a register (original adds it inline via $at). Remaining: v[2]/v[3] stores scheduled after FTOI4 setup in the original, hi parts of B_0019CCD0/D_0017AFFC kept in s0/s1 with reloads, and callee-saved register numbering. */
#ifdef NONMATCHING
extern float D_0017AFF0;
extern float D_0017AFFC;
extern float D_0017B010;
extern struct {
    int pad0;
    float f4;
} B_0019CCD0;
extern float iosGetCosf(float);
extern float iosGetSinf(float);
extern int getDrawScreenHeight(void);
extern void iosFTOI4Vector(int *, float *);
extern void gsReg(int, long);

void func_000BD7A0(int *buf)
{
    float v[4];
    float radius = D_0017AFF0 * 20.0f;
    float phase = D_0017B010 * 4.0f * 3.1415927f;
    int *p = buf;
    int i;
    int mode;
    int *q;

    for (i = 0; i < 0x2C; i++) {
        float a = 2.0f * (float)i * 3.1415927f * 0.022727272f + phase;
        float c = iosGetCosf(a);
        float s = iosGetSinf(a);
        v[0] = radius * c + 160.0f;
        v[1] = radius * 1.166667f * s + 160.0f;
        v[1] -= (float)((0x1C0 - getDrawScreenHeight()) >> 1);
        v[2] = 0;
        v[3] = 1.0f;
        iosFTOI4Vector(p, v);
        { int k = 0x8000; __asm__("" : "+r"(k)); p[0] = k + p[0]; k = 0x8000; __asm__("" : "+r"(k)); p[1] = k + p[1]; }
        p += 4;
    }
    mode = B_0019CCD0.f4 * D_0017AFFC == 1.0f ? 2 : 0x42;
    if (B_0019CCD0.f4 * D_0017AFFC == 1.0f)
        mode |= 0x80;
    gsReg(0, mode);
    gsReg(1, ((long)(int)(B_0019CCD0.f4 * D_0017AFFC * 128.0f) << 0x18) | (((long)0x3F800000 << 0x10 | 0xFF) << 0x10 | 0xFFFF));
    q = buf;
    for (i = 0; i < 0x2C; i++) {
        gsReg((i & 1) ? 0xC : 4, (long)q[0] | ((long)q[1] << 0x10) | ((long)0xFFFE524F << 0x20));
        q += 4;
    }
    gsReg(4, (long)buf[0] | ((long)buf[1] << 0x10) | ((long)0xFFFE524F << 0x20));
}
#endif
