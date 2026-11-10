/* ~162 diffs, 5 words short (165 vs 170). ST-coordinate sibling of spriteDrawSpriteUV: same vertex setup, fade and colour register (0x16 instead of 0x116) but the texture coordinates come from four raw words at s+0x20..0x2C copied (word by word) into an 8-aligned local, then copied again (ld/sd) and written as two ST registers (reg 2, s | t << 32) instead of the UV pairs. The Original keeps the sprite in $s0 and the scale float in $f20 (prototype float arrives in $f14 by position), saves only $s0/$s1/$ra and $f20 (frame 0x50); ours uses an extra register and frame 0x60. */
typedef unsigned long u64;
typedef struct { unsigned int s0, t0, s1, t1; } __attribute__((aligned(8))) STPair;
extern int setVertexPos(float *, void *, void *);
extern int func_00028E90(void *, float *);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void texTransRequest(int, int, int);
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern void gsReg(int, u64);

#ifdef NONMATCHING
void spriteDrawSpriteST(unsigned char *s, void *a1, float scale)
{
    float v[4];
    STPair a;
    STPair b;

    a.s0 = *(unsigned int *)(s + 0x20);
    a.t0 = *(unsigned int *)(s + 0x24);
    a.s1 = *(unsigned int *)(s + 0x28);
    a.t1 = *(unsigned int *)(s + 0x2C);
    b = a;
    if (setVertexPos(v, s, a1) != 0)
        return;
    scale = scale * (*(float *)(s + 8) * (float)s[7] * scale);
    if (scale > 0.0f) {
        u64 col;
        u64 m;
        int i0;
        int i1;

        iosDlPushLayer(0x1A);
        texTransRequest(*(int *)s, 0, 0);
        gsRegBegin();
        gsReg(0, ((u64)func_00028E90(s, v) << 6) | 0x16);
        col = (u64)s[4] | ((u64)0xFE00 << 46) | ((u64)(s[6] << 16) | (u64)(s[5] << 8));
        col |= ((u64)scale << 32) >> 8;
        gsReg(1, col);
        scale = 16.0f;
        m = (u64)-1 << 32;
        gsReg(2, (u64)b.s0 | ((u64)b.t0 << 32));
        i0 = (int)v[1];
        i1 = (int)v[0];
        gsReg(4, ((u64)((i0 << 4) + (int)((v[1] - i0) * scale) + 0x8000) << 16 |
                  (u64)((i1 << 4) + (int)((v[0] - i1) * scale) + 0x8000)) | m);
        gsReg(2, (u64)b.s1 | ((u64)b.t1 << 32));
        i0 = (int)v[3];
        i1 = (int)v[2];
        gsReg(4, ((u64)((i0 << 4) + (int)((v[3] - i0) * scale) + 0x8000) << 16 |
                  (u64)((i1 << 4) + (int)((v[2] - i1) * scale) + 0x8000)) | m);
        gsReg(0x47, 0x5900D);
        gsReg(8, 5);
        gsRegEnd();
        iosDlPopLayer();
    }
}
#endif
