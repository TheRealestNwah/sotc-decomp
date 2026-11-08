typedef unsigned long u64;
extern void gsReg(int, u64);
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern int getDrawScreenHeight(void);
extern int getDrawScreenWidth(void);
extern void iosDlPopLayer(void);
extern void iosDlPushLayer(int);

#ifdef NONMATCHING
void drawDemoBar(int layer, int h, float alpha)
{
    int w;
    int halfH;
    int halfW;
    int a;
    u64 mask;
    int x0;
    int x1;

    w = getDrawScreenWidth();
    halfH = getDrawScreenHeight() >> 1;
    a = (int)(alpha * 128.0f);
    halfW = w >> 1;
    if (a != 0) {
        iosDlPushLayer(layer);
        gsRegBegin();
        gsReg(0x42, ((u64)a << 0x20) | 0x64);
        gsReg(0x47, 0x31001);
        mask = (u64)-1 << 0x20;
        gsReg(0x49, 0);
        gsReg(0, 0x146);
        gsReg(1, ((0x3F800000UL << 0x10) | 0x8000) << 0x10);
        x0 = (0x800 - halfW) * 0x10;
        gsReg(4, x0 | (((0x800 - halfH) * 0x10) << 0x10) | mask);
        x1 = (halfW + 0x800) * 0x10;
        gsReg(4, x1 | ((((h - halfH) + 0x800) * 0x10) << 0x10) | mask);
        gsReg(4, x0 | ((((halfH - h) + 0x800) * 0x10) << 0x10) | mask);
        gsReg(4, x1 | (((halfH + 0x800) * 0x10) << 0x10) | mask);
        gsReg(0x42, 0x8000000044UL);
        gsReg(0x47, 0x5100D);
        gsReg(0x49, 1);
        gsReg(1, (((0x3F800000UL << 0x10) | 0x80FF) << 0x10) | 0xFFFF);
        gsRegEnd();
        iosDlPopLayer();
    }
}
#else
extern void drawDemoBar(int layer, int h, float alpha);
#endif
