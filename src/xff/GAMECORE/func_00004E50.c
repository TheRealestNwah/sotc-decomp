typedef struct {
    float x;
    float y;
    float z;
    float alpha;
    char text[0x10];
    int font;
    char pad24[0x30 - 0x24];
} __attribute__((aligned(8))) Message;

typedef struct {
    float x;
    float y;
    float z;
    char pad0C[0x40 - 0xC];
} KPrintfContext3D;

typedef struct {
    char pad0[0x180];
    float unk180;
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern int iosInitKPrintfContext3D(KPrintfContext3D *, int, int, int, float, float, float, float);
extern void kprintfContextCentering(KPrintfContext3D *, const char *, ...);
extern void scrRun(void);

static void func_00004E50(Message *src)
{
    Message m = *src;
    float y = 128.0f;
    KPrintfContext3D ctx;

    for (;;) {
        if (gcGlobalVar.unk180 != 0.0f) {
            m.alpha -= 0.1f;
            y -= 16.0f;
        }
        if (m.alpha < 0.0f)
            break;
        if (iosInitKPrintfContext3D(&ctx, m.font, 0, 1, m.x, m.y, m.z, m.alpha) != 0) {
            ctx.x += 120.0f;
            ctx.z += 120.0f;
            ctx.y += y;
            kprintfContextCentering(&ctx, "%s", m.text);
        }
        scrRun();
    }
}
