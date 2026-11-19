typedef unsigned long u64;
typedef struct { float x, y, z, w; } V __attribute__((aligned(16)));
typedef union { V v; int i[4]; } U;

extern int D_0013655C;
extern float D_00136560;
extern float D_00136564;
extern float D_00136570;

extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern int getDrawBufferAddressFBP(void);
extern void *memset(void *, int, unsigned int);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void iosSetRootDC(void);
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern void gsReg(int, u64);
extern char *iosgluGetCameraContext(void);
extern void iosCopyMatrix(void *, void *);
extern void spriteNoTexFast(int, int, int, int, unsigned int, void *, int);
extern void bgDraw(void);

void zFog(void)
{
    int rect[4];
    int black[4];
    float m[16] __attribute__((aligned(16)));
    U col;
    U pos;
    int i = 0;
    int w = getDrawScreenWidth();
    int h = getDrawScreenHeight();

    rect[0] = -((w >> 1) << 4);
    rect[1] = -((h >> 1) << 4);
    rect[2] = w << 4;
    rect[3] = h << 4;
    memset(black, 0, sizeof(black));
    iosDlPushLayer(4);
    gsRegBegin();
    gsReg(0x4C, getDrawBufferAddressFBP() | ((u64)((w >> 6) & 0x3F) << 16));
    gsReg(0x18, ((0x800 - w / 2) << 4) | ((u64)((0x800 - h / 2) << 4) << 32));
    gsReg(0x40, ((u64)(w - 1) << 16) | ((u64)(h - 1) << 48));
    iosCopyMatrix(m, iosgluGetCameraContext() + 0x4A0);
    gsReg(0x47, 0x51001);
    gsReg(0x48, 0x51001);
    gsReg(0x42, ((u64)0x80 << 32) | 0x48);
    gsReg(0x43, ((u64)0x80 << 32) | 0x48);
    spriteNoTexFast(rect[0], rect[1], rect[2], rect[3], 0xFFFFFF, black, 1);
    for (; i <= D_0013655C; i++) {
        memset(&pos, 0, sizeof(pos));
        pos.i[3] = (i << 7) / D_0013655C;
        col = pos;
        pos.v = (V){0.0f, 0.0f, ((D_00136570 - D_00136564) - D_00136560) + D_00136560 * i / D_0013655C, 1.0f};
        __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                             "lqc2 vf14, 0x0(%1)\n"
                             "lqc2 vf15, 0x10(%1)\n"
                             "lqc2 vf16, 0x20(%1)\n"
                             "lqc2 vf17, 0x30(%1)\n"
                             "vmulax.xyzw ACC, vf14, vf8x\n"
                             "vmadday.xyzw ACC, vf15, vf8y\n"
                             "vmaddaz.xyzw ACC, vf16, vf8z\n"
                             "vmaddw.xyzw vf10, vf17, vf8w\n"
                             "sqc2 vf10, 0x0(%0)\n"
                             : : "r"(&pos), "r"(m) : "memory");
        pos.v.z /= pos.v.w;
        spriteNoTexFast(rect[0], rect[1], rect[2], rect[3], (unsigned int)pos.v.z, &col, 1);
    }
    gsRegEnd();
    bgDraw();
    iosSetRootDC();
    iosDlPopLayer();
}
