typedef unsigned long u64;

extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void gsRegBegin(void);
extern void gsReg(int, u64);
extern void gsRegEnd(void);

void screenBrightness(int level)
{
    int w, h, hw, hh;

    w = getDrawScreenWidth();
    level -= 8;
    h = getDrawScreenHeight();
    hw = w >> 1;
    hh = h >> 1;

    if (level != 0) {
        iosDlPushLayer(0x1E);
        gsRegBegin();
        gsReg(0x47, 0x31001);
        gsReg(0x3B, ((u64)0x80 << 32) | 0x80);
        gsReg(0x42, ((u64)0x80 << 32) | 0x44);
        gsReg(0x49, 0);
        if (level < 0) {
            gsReg(1, ((u64)(-level * 4) << 24) | ((u64)0x3F800000 << 32));
        } else {
            gsReg(1, ((u64)level << 24) | ((u64)0x3F800000 << 32) | 0xFFFFFF);
        }
        gsReg(0, 0x146);
        gsReg(4, (u64)((0x800 - hw) << 4) | ((u64)((0x800 - hh) << 4) << 16) | ((u64)0xFFFFFFFF << 32));
        gsReg(4, (u64)((hw + 0x800) << 4) | ((u64)((hh + 0x800) << 4) << 16) | ((u64)0xFFFFFFFF << 32));
        gsReg(0x47, 0x5178D);
        gsReg(0x49, 1);
        gsRegEnd();
        iosDlPopLayer();
    }
}
