typedef struct {
    long x0;
    char pad8[0x100];
    long x108;
    long x110;
    long x118;
    long x120;
    long x128;
    long x130;
    unsigned long x138;
    long x140;
    long x148;
    long x150;
    unsigned long x158;
    long x160;
    float x168;
    float x16C;
    float x170;
    float x174;
    float x178;
    float x17C;
    float x180;
    float x184;
    float x188;
    float x18C;
    float x190;
    float x194;
    char pad198[0x8];
    float x1A0;
    char pad1A4[0x8];
    int x1AC;
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern int D_00179EA8;
extern long D_00179EB0;
extern void func_0000B688(void);
extern long iosGetTCount(void);
extern float iosGetSecondFromTCount(long);

static void func_0000B7C8(void)
{
    long t;

    func_0000B688();
    if (D_00179EA8 == 0)
        t = iosGetTCount();
    else if (D_00179EA8 == 1)
        t = D_00179EB0;
    else
        t = D_00179EB0;
    gcGlobalVar.x110 = gcGlobalVar.x108;
    gcGlobalVar.x130 = gcGlobalVar.x128;
    gcGlobalVar.x150 = gcGlobalVar.x148;
    gcGlobalVar.x0 = t;
    if (gcGlobalVar.x1AC != 0) {
        gcGlobalVar.x138 = ((unsigned long)(t << 8) >> 8);
        gcGlobalVar.x128 = 0;
        gcGlobalVar.x158 = (((unsigned long)(t << 8) >> 8) * (int)(gcGlobalVar.x1A0 * 256.0f)) >> 8;
        gcGlobalVar.x148 = 0;
    } else {
        gcGlobalVar.x128 = ((unsigned long)(t << 8) >> 8) - gcGlobalVar.x138;
        gcGlobalVar.x148 = ((((unsigned long)(t << 8) >> 8) * (int)(gcGlobalVar.x1A0 * 256.0f)) >> 8) - gcGlobalVar.x158;
    }
    gcGlobalVar.x108 = t - gcGlobalVar.x118;
    gcGlobalVar.x17C = gcGlobalVar.x178;
    gcGlobalVar.x18C = gcGlobalVar.x188;
    gcGlobalVar.x16C = gcGlobalVar.x168;
    gcGlobalVar.x178 = iosGetSecondFromTCount(gcGlobalVar.x128 + gcGlobalVar.x140);
    gcGlobalVar.x188 = iosGetSecondFromTCount(gcGlobalVar.x148 + gcGlobalVar.x160);
    gcGlobalVar.x168 = iosGetSecondFromTCount(gcGlobalVar.x108 + gcGlobalVar.x120);
    gcGlobalVar.x180 = iosGetSecondFromTCount(gcGlobalVar.x128 - gcGlobalVar.x130);
    gcGlobalVar.x190 = iosGetSecondFromTCount(gcGlobalVar.x148 - gcGlobalVar.x150);
    gcGlobalVar.x170 = iosGetSecondFromTCount(gcGlobalVar.x108 - gcGlobalVar.x110);
    gcGlobalVar.x184 = 1.0f / gcGlobalVar.x180;
    gcGlobalVar.x194 = 1.0f / gcGlobalVar.x190;
    gcGlobalVar.x174 = 1.0f / gcGlobalVar.x170;
}
