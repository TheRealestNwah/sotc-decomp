typedef unsigned int u32;
typedef unsigned long u64;

typedef struct {
    char pad[0xC];
    long *p;
    char pad2[0xC];
    int busy;
} GsCtx;

extern GsCtx *D_00040BF4;
extern int D_00040BF8;

static __inline__ void GSREG(long reg, long data)
{
    if (D_00040BF4->busy == 0) {
        *D_00040BF4->p++ = data;
        *D_00040BF4->p++ = reg;
    }
}
#define RGBAQ(c) ((long)(c)[0] | ((long)(c)[1] << 8) | ((long)(c)[2] << 16) | ((long)(c)[3] << 24) | ((long)0x3F800000 << 32))
#define XYZ(x, y, z) (((x) + 0x8000) | ((u64)((y) + 0x8000) << 16) | ((u64)(z) << 32))
#define SCISSOR(x0, x1, y0, y1) ((u64)(x0) | ((u64)(x1) << 16) | ((u64)(y0) << 32) | ((u64)(y1) << 48))
#define UV(u, v) (((u) + 8) | (((v) + 8) << 16))

/* Parked: register allocation and frame size differ (0x30 with s0-s4 in the original). */
#ifdef NONMATCHING
void spriteTexFast(int x, int y, int w, int h, u32 z, int *uv, int *rgba, int abe)
{
    int pw, ph, n, i, r, bw;

    bw = 64;

    if (D_00040BF8 == 0 || (pw = w >> 4, r = (pw % bw) != 0, ph = h >> 4, pw <= bw)) {
        GSREG(0, (abe << 6) | 0x116);
        GSREG(1, RGBAQ(rgba));
        GSREG(3, UV(uv[0], uv[1]));
        GSREG(4, XYZ(x, y, z));
        GSREG(3, UV(uv[0] + uv[2], uv[1] + uv[3]));
        GSREG(4, XYZ(x + w, y + h, z));
    } else {
        GSREG(1, RGBAQ(rgba));
        GSREG(0, (abe << 6) | 0x116);
        n = (w >> 10) + r;
        for (i = 0; i < n; i++) {
            GSREG(0x40, SCISSOR(i * 64, (i + 1) * 64 - 1, 0, ph - 1));
            GSREG(3, UV(uv[0], uv[1]));
            GSREG(4, XYZ(x, y, z));
            GSREG(3, UV(uv[0] + uv[2], uv[1] + uv[3]));
            GSREG(4, XYZ(x + w, y + h, z));
        }
        GSREG(0x40, SCISSOR(0, pw - 1, 0, ph - 1));
    }
}
#endif
