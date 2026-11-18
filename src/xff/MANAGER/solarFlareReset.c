#ifdef NONMATCHING /* 10 diffs: v0/v1 swap copying the FlareBuffer rodata, and the store order of r.w/r.h */
typedef unsigned long u64;

extern void gsReg(int, u64);
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern void iosDlPopLayer(void);
extern void iosDlPushLayer(int);
extern void *memset(void *, int, unsigned int);
extern void spriteNoTexFast(int, int, int, int, int, int *, int);

typedef struct {
    int pad0;
    int fbp;
    int pad8;
    int padC;
    int pad10;
    int width;
    int height;
} FlareBuffer;

typedef struct {
    int x, y, w, h;
} Rect __attribute__((aligned(8)));

static const FlareBuffer D_0013D500 = { 0, 0x1FE, 0x3FC0, 6, 6, 0x40, 0x40 };

void solarFlareReset(void)
{
    iosDlPushLayer(0x13);
    gsRegBegin();
    {
        FlareBuffer fb = D_0013D500;
        Rect r;
        {
            Rect col;

            col.x = -(fb.width * 8);
            col.y = -(fb.height * 8);
            col.h = fb.height * 16;
            col.w = fb.width * 16;
            r = col;
            memset(&col, 0, 0x10);
            col.h = 0x80;
            gsReg(0x4C, fb.fbp | (u64)((fb.width >> 6) & 0x3F) << 16);
            gsReg(0x18, (u64)((0x800 - fb.width / 2) << 4) | (u64)((0x800 - fb.height / 2) << 4) << 32);
            gsReg(0x40, (u64)(fb.width - 1) << 16 | (u64)(fb.height - 1) << 48);
            gsReg(0x47, 0x31001);
            gsReg(0x42, 0x44);
            spriteNoTexFast(r.x, r.y, r.w, r.h, 0xFFFFFF, &col.x, 1);
        }
    }
    gsReg(0x47, 0x5100D);
    gsRegEnd();
    iosDlPopLayer();
}
#endif
