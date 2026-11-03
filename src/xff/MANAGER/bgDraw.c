typedef unsigned long u64;

typedef struct {
    int v[4];
} __attribute__((aligned(16))) Vec4i;

extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern void iosSetRootDC(void);
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern int getFrameBufferSizeTBP(void);
extern void gsReg(int, u64);
extern void spriteTexFast(int, int, int, int, int, Vec4i *, Vec4i *, int);
extern void texResetVRAMRequest(int);

void bgDraw(void)
{
    int w = getDrawScreenWidth();
    int h = getDrawScreenHeight();
    int rect[4] = {(-w / 2) << 4, (-h / 2) << 4, w << 4, h << 4};
    Vec4i color = {{0x80, 0x80, 0x80, 0x80}};
    Vec4i uv = {{0, 0, 0x1000, 0x1000}};

    iosSetRootDC();
    gsRegBegin();
    gsReg(6, getFrameBufferSizeTBP() | 0x20110000 | ((u64)0x8000 << 18));
    gsReg(0x14, ((u64)-0x32 << 32) | 0x360);
    gsReg(0x47, 0x31001);
    gsReg(0x42, ((u64)0x80 << 32) | 0x54);
    spriteTexFast(rect[0], rect[1], rect[2], rect[3], 0xFFFFFF, &uv, &color, 1);
    gsReg(0x42, ((u64)0x80 << 32) | 0x44);
    gsReg(0x47, 0x5100D);
    gsRegEnd();
    texResetVRAMRequest(0);
}
