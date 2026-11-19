typedef unsigned long u64;
typedef struct { int s0, t0, s1, t1; } __attribute__((aligned(8))) STPair;
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

/* 2 diffs, same size. The Original loads the s+0x20 word into $a2 (stored to sp+0x10 for b.s0);
   ours picks $a1. Field-order, struct-copy, pointer and volatile variants and a 30-minute permuter
   run (-j2) found nothing better. */
#ifdef NONMATCHING
/* Draws a sprite at caller-supplied screen coordinates v (x0, y0, x1, y1), skipping it when
   both corners are off the same screen edge; colour is scaled by c, alpha by fade. */
void spriteDrawSpriteST2(unsigned char *s, float *v, float c, float scale)
{
    STPair b;
    STPair a;

    a.s0 = *(int *)(s + 0x20);
    a.t0 = *(int *)(s + 0x24);
    a.s1 = *(int *)(s + 0x28);
    a.t1 = *(int *)(s + 0x2C);
    b = a;
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
        gsReg(0, ((u64)func_00028E90(s, v) << 6) | 0x16);
        lo = ((u64)0xFE00 << 46) | (u64)(int)(s[4] * c);
        col = lo | ((u64)(int)(s[6] * c) << 16 | (u64)(int)(s[5] * c) << 8);
        gsReg(1, col | (u64)(unsigned int)scale << 24);
        scale = 16.0f;
        m = (u64)-1 << 32;
        gsReg(2, (u64)b.s0 | ((u64)b.t0 << 32));
        i0 = (int)v[0];
        i1 = (int)v[1];
        gsReg(4, (u64)((i0 << 4) + (int)((v[0] - i0) * scale) + 0x8000) |
                     (u64)((i1 << 4) + (int)((v[1] - i1) * scale) + 0x8000) << 16 | m);
        gsReg(2, (u64)b.s1 | ((u64)b.t1 << 32));
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
#endif
