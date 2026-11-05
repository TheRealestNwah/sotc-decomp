typedef unsigned long u64;

typedef struct {
    char pad0[0xC];
    int r;
    int g;
    int b;
    char pad18[8];
    int a;
} GEnv;

extern GEnv genv;

extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void gsRegBegin(void);
extern void gsReg(int, u64);
extern void gsRegEnd(void);

void drawFrontFog(void)
{
    int hw = getDrawScreenWidth() >> 1;
    int hh = getDrawScreenHeight() >> 1;

    if (genv.a != 0) {
        iosDlPushLayer(0x14);
        gsRegBegin();
        gsReg(0x42, ((u64)0x80 << 32) | 0x44);
        gsReg(0x47, 0x31001);
        gsReg(0x49, 0);
        gsReg(0, 0x4E);
        gsReg(1, (u64)genv.r | ((u64)genv.g << 8) | ((u64)genv.b << 16) | ((u64)genv.a << 24) | ((u64)0x3F800000 << 32));
        gsReg(4, (u64)((0x800 - hw) << 4) | ((u64)((0x800 - hh) << 4) << 16) | ((u64)0xFFFFFFFF << 32));
        gsReg(4, (u64)((hw + 0x800) << 4) | ((u64)((hh + 0x800) << 4) << 16) | ((u64)0xFFFFFFFF << 32));
        gsReg(0x47, 0x5178D);
        gsReg(0x49, 1);
        gsRegEnd();
        iosDlPopLayer();
    }
}
