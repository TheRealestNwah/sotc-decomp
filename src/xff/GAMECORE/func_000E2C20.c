extern char gcGlobalVar[];
extern float RO_001811D0;
extern char RO_001811B8[];
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern void *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern void iosInitKPrintfContext(void *, float, float, int, int, float, float, float, float);
extern void iosSetKPrintfLocateContext(void *, float, float);
extern void kprintfContext(void *, const char *, ...);

typedef struct {
    char pad0[0x1C];
    void *chara;
    char pad20[0x37C4 - 0x20];
    float timer;
} DispWork;

static void func_000E2C20(DispWork *w, int reset)
{
    char ctx[0x40];

    if (reset)
        w->timer = 2.0f;
    else
        w->timer -= *(float *)(gcGlobalVar + 0x170);
    if (0.0f < w->timer) {
        float x, y;
        iosDlPushLayer(3);
        x = getDrawScreenWidth() * -0.2f;
        y = getDrawScreenHeight() * RO_001811D0;
        if (GetCharacterClass(w->chara))
            iosInitKPrintfContext(ctx, x, y, 0, 1, 0.6f, 0.6f, 1.0f, 1.0f);
        else
            iosInitKPrintfContext(ctx, x, y, 0, 1, 1.0f, 0.6f, 0.6f, 1.0f);
        iosSetKPrintfLocateContext(ctx, x, y);
        kprintfContext(ctx, RO_001811B8, *(int *)(GetLayoutClass(w->chara) + 0x130));
        iosDlPopLayer();
    }
}
