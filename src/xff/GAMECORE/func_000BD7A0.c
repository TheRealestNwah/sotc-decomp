/* Parked: 137 diffs, same size (173 words). GS ring effect: 44 points on an ellipse via iosFTOI4Vector, then gsReg packets. Original keeps the buffer in s2 and does not hold 0x8000 in a callee-saved register; sin/cos call setup shares one f12 move. */
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
        p[0] += 0x8000;
        p[1] += 0x8000;
        p += 4;
    }
    mode = 0x42;
    if (B_0019CCD0.f4 * D_0017AFFC == 1.0f)
        mode = 2;
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
