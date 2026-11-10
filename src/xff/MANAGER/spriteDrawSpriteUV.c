/* ~156 diffs, 6 words short (162 vs 168). Sprite draw from a sprite record + vertex buffer (setVertexPos fills 4 floats; skips when it fails or when scale^2 * s[8] * s[7] <= 0): pushes layer 0x1A, texTransRequest(s[0]), gsReg 0 with func_00028E90 << 6 | 0x116, colour reg 1 from s[4..6] plus the float alpha as a u64 (fixed-point 2^63 branch in the original), UV pairs from s+0x10/0x14 and s+0x18/0x1C (<<4 + 8), and two XYZ regs where each vertex coordinate is split into an integer part << 4 plus (frac * 16) + 0x8000. The Original reuses the scale float for the alpha and loads 16.0 into it afterwards, keeps s in $s2 and the 0x8000 constant in $s0 / -1<<32 mask in $s1; ours still allocates s3 and an extra f21. Prototype is (sprite, vertex args, float) because the float arrives in $f14 by position. */
typedef unsigned long u64;
extern int setVertexPos(float *, void *, void *);
extern int func_00028E90(void *, float *);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void texTransRequest(int, int, int);
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern void gsReg(int, u64);

#ifdef NONMATCHING
void spriteDrawSpriteUV(unsigned char *s, void *a1, float scale)
{
    float v[4];

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
        gsReg(0, ((u64)func_00028E90(s, v) << 6) | 0x116);
        col = (u64)s[4] | ((u64)0xFE00 << 46) | ((u64)(s[6] << 16) | (u64)(s[5] << 8));
        col |= ((u64)scale << 32) >> 8;
        gsReg(1, col);
        scale = 16.0f;
        m = (u64)-1 << 32;
        gsReg(3, (u64)((*(int *)(s + 0x10) << 4) + 8) | ((u64)((*(int *)(s + 0x14) << 4) + 8) << 16));
        i0 = (int)v[1];
        i1 = (int)v[0];
        gsReg(4, ((u64)((i0 << 4) + (int)((v[1] - i0) * scale) + 0x8000) << 16 |
                  (u64)((i1 << 4) + (int)((v[0] - i1) * scale) + 0x8000)) | m);
        gsReg(3, (u64)((*(int *)(s + 0x18) << 4) + 8) | ((u64)((*(int *)(s + 0x1C) << 4) + 8) << 16));
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
