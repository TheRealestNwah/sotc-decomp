/* Parked at 19 diffs: draws a 44-segment ring (makeRing, also used by func_000BE108) as GS line strips twice: once with a blended color lerped by 1 - D_0017B008.f8, then with blend mode 0x4A/0xA (|0x80 when the fade factor is 1). The B_0019CCD0.f4 and D_0017B000 loads for the alpha term are pinned to $f7/$f8 as in the Original. Remaining diffs are FPU register allocation in the color block (0x248-0x2BC): the Original gives the 38/42 constants f5/f6, computes the 46 term before B*D and converts every channel through f0. Pinning the constants or the sums makes it worse. */
#ifdef NONMATCHING
extern float D_0017AFF0;
extern float D_0017B000;
extern struct { float f0; float f4; float f8; } D_0017B008;
extern struct { int pad0; float f4; } B_0019CCD0;
extern float iosGetCosf(float);
extern float iosGetSinf(float);
extern int getDrawScreenHeight(void);
extern void iosFTOI4Vector(int *, float *);
extern void gsReg(int, long);

static inline void makeRing(int *p, float radius)
{
    float v[4];
    int i;
    float phase = 0.0f;
    float k = 0.022727272f;

    for (i = 0; i < 0x2C; i++) {
        float a = 2.0f * (float)i * 3.1415927f * k + phase;
        float c = iosGetCosf(a);
        float s = iosGetSinf(a);
        v[0] = radius * c + 160.0f;
        v[1] = radius * 1.166667f * s + 160.0f;
        ((int *)v)[2] = 0;
        v[3] = 1.0f;
        v[1] -= (float)((0x1C0 - getDrawScreenHeight()) >> 1);
        iosFTOI4Vector(p, v);
        p[0] += 0x8000;
        p[1] += 0x8000;
        p += 4;
    }
}

static void func_000BD348(int *buf)
{
    int i;
    long mode;
    float t;
    int *q;
    long z, z2;
    int *q2;
    int r, g, bb;

    makeRing(buf, D_0017AFF0 * 20.0f * D_0017B008.f8);
    gsReg(0, 0x4D);
    gsReg(1, ((long)(int)(B_0019CCD0.f4 * D_0017B000 * 128.0f) << 0x18) | (((long)0x3F800000 << 0x10 | 0xA3) << 0x10 | 0x93B9));
    gsReg(4, ((long)((0x8A0 - ((0x1C0 - getDrawScreenHeight()) >> 1)) * 0x10) << 0x10) | ((long)0xFFFE524F << 0x20) | 0x8A00);
    t = 1.0f - D_0017B008.f8;
    { register float bv asm("$f7") = B_0019CCD0.f4; register float dv asm("$f8") = D_0017B000;
    r = t * 46.0f + 139.0f;
    g = t * 38.0f + 109.0f; bb = t * 42.0f + 121.0f;
    gsReg(1, (long)r | ((long)g << 8) | ((long)bb << 0x10) |
             ((long)(int)((t * 0.0f + 128.0f - 0.0f) * (bv * dv)) << 0x18) | ((long)0xFE00 << 0x2E)); }
    z = (long)0xFFFE524F << 0x20;
    q = buf;
    for (i = 0; i < 0x2C; i++) {
        gsReg(4, (long)q[0] | ((long)q[1] << 0x10) | z);
        q += 4;
    }
    gsReg(4, (long)buf[0] | ((long)buf[1] << 0x10) | ((long)0xFFFE524F << 0x20));
    mode = B_0019CCD0.f4 * D_0017B000 != 1.0f ? 0x4A : 0xA;
    if (B_0019CCD0.f4 * D_0017B000 == 1.0f)
        mode |= 0x80;
    z2 = (long)0xFFFE524F << 0x20;
    gsReg(0, mode);
    q2 = buf;
    for (i = 0; i < 0x2C; i++) {
        gsReg(4, (long)q2[0] | ((long)q2[1] << 0x10) | z2);
        q2 += 4;
    }
    gsReg(4, (long)buf[0] | ((long)buf[1] << 0x10) | ((long)0xFFFE524F << 0x20));
}
#endif
