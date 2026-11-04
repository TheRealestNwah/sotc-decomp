typedef unsigned long u64;

extern char *D_STR_00130440;
extern int D_00130430[3];
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern void iosDlPushLayer(char *);
extern void iosDlPopLayer(void);
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern void gsReg(int, u64);

void fadeScreen(float alpha)
{
    u64 a = (u64)(int)(alpha * 128.0f) << 32;
    int w = getDrawScreenWidth();
    int h = getDrawScreenHeight() >> 1;

    iosDlPushLayer(D_STR_00130440);
    gsRegBegin();
    gsReg(0x42, a | 0x64);
    gsReg(0x47, 0x31001);
    gsReg(0x49, 0);
    gsReg(0, 0x146);
    gsReg(1, (u64)D_00130430[0] | ((u64)D_00130430[1] << 8) | ((u64)D_00130430[2] << 16) | ((u64)0x80 << 24) | ((u64)0x3F800000 << 32));
    gsReg(4, (u64)((0x800 - (w >> 1)) << 4) | ((u64)((0x800 - h) << 4) << 16) | ((u64)0xFFFFFFFF << 32));
    gsReg(4, (u64)((0x800 + (w >> 1)) << 4) | ((u64)((0x800 + h) << 4) << 16) | ((u64)0xFFFFFFFF << 32));
    gsReg(0x42, ((u64)0x80 << 32) | 0x44);
    gsReg(0x47, 0x5178D);
    gsReg(0x49, 1);
    gsRegEnd();
    iosDlPopLayer();
}
