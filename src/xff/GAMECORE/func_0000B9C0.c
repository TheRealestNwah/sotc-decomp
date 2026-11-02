typedef struct {
    char pad0[0x108];
    long x108;
    char pad110[0x8];
    long x118;
    long x120;
    long x128;
    char pad130[0x8];
    long x138;
    long x140;
    long x148;
    char pad150[0x8];
    long x158;
    long x160;
    float x168;
    char pad16C[0xC];
    float x178;
    char pad17C[0xC];
    float x188;
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern int D_00179EA8;
extern long D_00179EB0;
extern void func_0000B688(void);
extern void func_0000B7C8(void);
extern long iosGetTCount(void);
extern float iosGetSecondFromTCount(long);

static void func_0000B9C0(void)
{
    long t;
    GlobalVar *g;

    func_0000B688();
    switch (D_00179EA8) {
    case 0:
        t = iosGetTCount();
        break;
    case 1:
        t = D_00179EB0;
        break;
    default:
        t = D_00179EB0;
        break;
    }
    g = &gcGlobalVar;
    g->x140 = t;
    g->x120 = t;
    g->x158 = t;
    g->x138 = t;
    g->x118 = t;
    g->x148 = 0;
    g->x128 = 0;
    g->x108 = 0;
    g->x178 = iosGetSecondFromTCount(t);
    g->x188 = iosGetSecondFromTCount(g->x148 + g->x160);
    g->x168 = iosGetSecondFromTCount(g->x108 + g->x120);
    func_0000B7C8();
}
