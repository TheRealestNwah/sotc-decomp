typedef unsigned long u64;

extern int getDrawScreenHeight(void);
extern int getDrawScreenWidth(void);
extern void gsReg(int, u64);
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern int iosDlGetWorkBufId(void);
extern void iosDlPopLayer(void);
extern void iosDlPushLayer(int);
extern void iosSetDC(int, void *);
extern void *memset(void *, int, unsigned int);
extern void spriteNoTexFast(int, int, int, int, int, int *, int);
extern void texResetVRAMRequest(int);

typedef struct {
    char pad[0x1C];
    int dc;
} DcInfo;

extern int D_0013616C;
extern int D_00136170;
extern DcInfo *D_0013617C;

#ifdef NONMATCHING
void shadowReset(void)
{
    int rect[4];
    int col[4];
    int w;
    int h;

    w = getDrawScreenWidth();
    h = getDrawScreenHeight();
    if (D_0013616C != 0) {
        D_00136170 = 1;
        iosDlPushLayer(7);
        texResetVRAMRequest((w * h + 0x10000) >> 6);
        iosSetDC(D_0013617C->dc + iosDlGetWorkBufId() * 0x190, D_0013617C);
        gsRegBegin();
        {
            int x = (-w / 2) * 16;
            int y = (-h / 2) * 16;
            rect[1] = y;
            rect[0] = x;
            rect[2] = w * 16;
            rect[3] = h * 16;
        }
        memset(col, 0, 0x10);
        col[3] = 0x80;
        gsReg(0x4A, 0);
        gsReg(0x3B, 0x8000000080UL);
        gsReg(0x47, 0x31001);
        gsReg(0x42, 0x8000000064UL);
        gsReg(0x46, 1);
        gsReg(0x49, 0);
        spriteNoTexFast(rect[0], rect[1], rect[2], rect[3], 0xFFFFFF, col, 0);
        gsReg(0x47, 0x51001);
        gsReg(0x42, 0x8000000068UL);
        gsReg(0x46, 0);
        gsRegEnd();
        iosDlPopLayer();
    }
}
#else
extern void shadowReset(void);
#endif
