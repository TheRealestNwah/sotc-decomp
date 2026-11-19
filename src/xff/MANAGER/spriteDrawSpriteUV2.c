typedef unsigned long u64;
extern int func_00028E90(void *, float *);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void texTransRequest(int, int, int);
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern void gsReg(int, u64);
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);

static inline int IsOutOfScreen(float *v)
{
    int w = getDrawScreenWidth() >> 1;
    int h = getDrawScreenHeight() >> 1;

    if ((v[0] < -w && v[2] < -w) || (w < v[0] && w < v[2]) ||
        (v[1] < -h && v[3] < -h) || (h < v[1] && h < v[3]))
        return 1;
    return 0;
}

/* Draws a sprite at caller-supplied screen coordinates v (x0, y0, x1, y1), skipping it when
   both corners are off the same screen edge; colour is scaled by c, alpha by scale. */
void spriteDrawSpriteUV2(unsigned char *s, float *v, float c, float scale)
{
    if (IsOutOfScreen(v))
        return;
    scale = scale * (*(float *)(s + 8) * (float)s[7] * scale);
    if (scale > 0.0f) {
        u64 lo;
        u64 col;
        u64 m;
        int i0;
        int i1;

        iosDlPushLayer(0x1A);
        texTransRequest(*(int *)s, 0, 0);
        gsRegBegin();
        gsReg(0, ((u64)func_00028E90(s, v) << 6) | 0x116);
        lo = ((u64)0xFE00 << 46) | (u64)(int)(s[4] * c);
        col = lo | ((u64)(int)(s[6] * c) << 16 | (u64)(int)(s[5] * c) << 8);
        gsReg(1, col | (u64)(unsigned int)scale << 24);
        scale = 16.0f;
        m = (u64)-1 << 32;
        gsReg(3, (u64)((*(int *)(s + 0x10) << 4) + 8) | ((u64)((*(int *)(s + 0x14) << 4) + 8) << 16));
        i0 = (int)v[0];
        i1 = (int)v[1];
        gsReg(4, (u64)((i0 << 4) + (int)((v[0] - i0) * scale) + 0x8000) |
                     (u64)((i1 << 4) + (int)((v[1] - i1) * scale) + 0x8000) << 16 | m);
        gsReg(3, (u64)((*(int *)(s + 0x18) << 4) + 8) | ((u64)((*(int *)(s + 0x1C) << 4) + 8) << 16));
        i0 = (int)v[2];
        i1 = (int)v[3];
        gsReg(4, (u64)((i0 << 4) + (int)((v[2] - i0) * scale) + 0x8000) |
                     (u64)((i1 << 4) + (int)((v[3] - i1) * scale) + 0x8000) << 16 | m);
        gsReg(0x47, 0x5900D);
        gsReg(8, 5);
        gsRegEnd();
        iosDlPopLayer();
    }
}
