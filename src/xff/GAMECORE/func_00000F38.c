typedef struct {
    char pad0[0x40];
} KPrintfContext;

extern int D_001798C8;
extern char *GetLayoutClass(void *);
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void iosInitKPrintfContext(KPrintfContext *, int, int, float, float, float, float, float, float);
extern void iosSetKPrintfLocateContext(KPrintfContext *, float, float);
extern void kprintfContext(KPrintfContext *, char *, ...);
extern void GetEulerYXZFromQuaternion(float *, void *);

static void func_00000F38(void *obj)
{
    KPrintfContext ctx;
    float eul[4] __attribute__((aligned(16)));
    char *lc = GetLayoutClass(obj);
    float x;
    float y;
    float dy;
    float *p;

    if (D_001798C8 == 0 || lc == 0)
        return;
    x = getDrawScreenWidth() * 0.15f;
    y = getDrawScreenHeight() * -0.445f;
    dy = getDrawScreenHeight() * 0.05f;
    iosDlPushLayer(0x1D);
    iosInitKPrintfContext(&ctx, 0, 1, x, y, 0.5f, 1.0f, 0.5f, 1.0f);
    iosSetKPrintfLocateContext(&ctx, x, y);
    if (lc[0x150] != 0)
        kprintfContext(&ctx, "\245\307\245\320\245\303\245\260\260\334\306\260\245\342\241\274\245\311");
    else
        kprintfContext(&ctx, "\304\314\276\357\260\334\306\260\245\342\241\274\245\311");
    y += dy;
    iosSetKPrintfLocateContext(&ctx, x, y);
    p = *(float **)(lc + 0x134);
    y += dy;
    kprintfContext(&ctx, "\260\314\303\326 %.2f %.2f %.2f", -p[0], p[1], -p[2]);
    GetEulerYXZFromQuaternion(eul, *(void **)(lc + 0x13C));
    iosSetKPrintfLocateContext(&ctx, x, y);
    kprintfContext(&ctx, "\262\363\305\276 %.2f %.2f %.2f", eul[0] * 57.29578f, -(eul[1] * 57.29578f), eul[2] * 57.29578f);
    iosDlPopLayer();
}
