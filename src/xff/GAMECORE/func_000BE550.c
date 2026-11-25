/* Life bar ring: a 44-point ring (same as func_000BDA78's makeRing) drawn as a triangle fan around the screen-centre vertex. */
extern struct { int pad0; float f4; } B_0019CCD0;
extern float D_0017AFF0;
extern float D_0017AFFC;
extern float iosGetCosf(float);
extern float iosGetSinf(float);
extern int getDrawScreenHeight(void);
extern void iosFTOI4Vector(int *, float *);
extern void gsReg(int, long);

static inline void makeRing(int *p, float radius, float phase)
{
    float v[4];
    int i;
    float k = 0.022727272f;

    for (i = 0; i < 0x2C; i++) {
        float a = 2.0f * (float)i * 3.1415926f * k + phase;
        float c = iosGetCosf(a);
        float s = iosGetSinf(a);
        v[0] = radius * c + 160.0f;
        v[1] = radius * 1.166667f * s + 160.0f;
        ((int *)v)[2] = 0;
        v[3] = 1.0f;
        v[1] -= (float)((0x1C0 - getDrawScreenHeight()) >> 1);
        iosFTOI4Vector(&p[i * 4], v);
        p[i * 4] += 0x8000;
        p[i * 4 + 1] += 0x8000;
    }
}

static void func_000BE550(float *o, int *p)
{
    float alpha = B_0019CCD0.f4 * D_0017AFFC;
    int inner = (int)(o[5] * 0.0f * alpha);
    int outer = (int)(o[5] * 128.0f * alpha);
    long c;
    int i;

    makeRing(p, D_0017AFF0 * 20.0f * o[3], 0.0f);
    gsReg(0x42, ((long)0x80 << 0x20) | 0x48);
    gsReg(0, 0x4D);
    c = 0x3F80000000FFFFFFLL;
    gsReg(1, ((long)outer << 0x18) | c);
    gsReg(4, ((long)((0x8A0 - ((0x1C0 - getDrawScreenHeight()) >> 1)) << 4) << 0x10) | ((long)0xFFFE524F << 0x20) | 0x8A00);
    gsReg(1, ((long)inner << 0x18) | c);
    for (i = 0; i < 0x2C; i++) {
        gsReg(4, (long)p[i * 4] | ((long)p[i * 4 + 1] << 0x10) | ((long)0xFFFE524F << 0x20));
    }
    gsReg(4, (long)p[0] | ((long)p[1] << 0x10) | ((long)0xFFFE524F << 0x20));
}
