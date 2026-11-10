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

/* Parked: arg-copy register order and loop/scissor scheduling differ. */
#ifdef NONMATCHING
void spriteNoTexFast(int x, int y, int w, int h, u32 z, int *rgba, int abe)
{
    int pw, ph, n, i;

    if (D_00040BF8 == 0) {
        GSREG(0, (abe << 6) | 6);
        GSREG(1, RGBAQ(rgba));
        GSREG(4, XYZ(x, y, z));
        GSREG(4, XYZ(x + w, y + h, z));
    } else {
        pw = w >> 4;
        ph = h >> 4;
        GSREG(1, RGBAQ(rgba));
        GSREG(0, (abe << 6) | 6);
        n = (w >> 10) + ((pw % 64) != 0);
        for (i = 0; i < n; i++) {
            GSREG(0x40, SCISSOR(i * 64, (i + 1) * 64 - 1, 0, ph - 1));
            GSREG(4, XYZ(x, y, z));
            GSREG(4, XYZ(x + w, y + h, z));
        }
        GSREG(0x40, SCISSOR(0, pw - 1, 0, ph - 1));
    }
}
#endif
