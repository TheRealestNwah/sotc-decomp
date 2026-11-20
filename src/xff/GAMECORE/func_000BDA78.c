typedef struct { float r; float a; } Hist;
extern Hist B_0019CC50[16];
extern struct { int pad0; float f4; } B_0019CCD0;
extern struct { int pad0; int pad4; float f8; } D_0017B018;
extern float D_0017B004;
extern int D_0017B028;
extern int D_0017B02C;
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
        float a = 2.0f * (float)i * 3.1415927f * k + phase;
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

static void func_000BDA78(int *in, int *out)
{
    int i;
    long z;
    float zero = 0.0f;

    if (D_0017B018.f8 > zero) {
        if (D_0017B02C != 0) {
            D_0017B02C = 0;
            D_0017B028 = 0;
        }
        for (i = 15; i > 0; i--) {
            B_0019CC50[i].r = B_0019CC50[i - 1].r;
            B_0019CC50[i].a = B_0019CC50[i - 1].a - 0.0625f;
        }
        B_0019CC50[0].r = D_0017B018.f8;
        B_0019CC50[0].a = 1.0f;
        D_0017B028++;
        if (D_0017B028 > 16)
            D_0017B028 = 16;
    } else if (D_0017B028 > 0) {
        D_0017B028--;
        D_0017B02C = 1;
        if (D_0017B028 == 0) {
            for (i = 0; i < 16; i++) {
                B_0019CC50[i].r = 0.0f;
                B_0019CC50[i].a = 0.0f;
            }
            D_0017B02C = 0;
        } else {
            for (i = 0; i < 16; i++)
                B_0019CC50[i].a -= 0.0625f;
        }
    } else {
        D_0017B02C = 0;
        for (i = 0; i < 16; i++) {
            B_0019CC50[i].r = 0.0f;
            B_0019CC50[i].a = 0.0f;
        }
        return;
    }
    makeRing(in, B_0019CC50[0].r * 20.0f, zero);
    if (B_0019CC50[0].r >= 7.0f)
        D_0017B004 = 0.0f;
    else if (B_0019CC50[0].r <= 1.0f)
        D_0017B004 = 1.0f;
    else
        D_0017B004 = -(B_0019CC50[0].r - 1.0f) / 6.0f + 1.0f;
    if (B_0019CC50[0].a > 0.0f) {
        makeRing(out, B_0019CC50[D_0017B028 - 1].r * 20.0f, zero);
        gsReg(0x42, ((long)0x80 << 0x20) | 0x48);
        gsReg(0, 0x4C);
        z = (long)0xFFFE524F << 0x20;
        for (i = 0; i < 0x2C; i++) {
            gsReg(1, 0x3F80000000FFFFFFLL);
            gsReg(4, (long)out[i * 4] | ((long)out[i * 4 + 1] << 0x10) | z);
            gsReg(1, ((long)(int)(B_0019CCD0.f4 * D_0017B004 * 64.0f * B_0019CC50[0].a) << 0x18) | 0x3F80000000FFFFFFLL);
            gsReg(4, (long)in[i * 4] | ((long)in[i * 4 + 1] << 0x10) | z);
        }
        gsReg(1, 0x3F80000000FFFFFFLL);
        gsReg(4, (long)out[0] | ((long)out[1] << 0x10) | ((long)0xFFFE524F << 0x20));
        gsReg(1, ((long)(int)(B_0019CCD0.f4 * D_0017B004 * 64.0f * B_0019CC50[0].a) << 0x18) | 0x3F80000000FFFFFFLL);
        gsReg(4, (long)in[0] | ((long)in[1] << 0x10) | ((long)0xFFFE524F << 0x20));
    }
}
