extern char gcGlobalVar[];
extern char RO_0017C0F8[];
extern int iosInitKPrintfContext3D(float *ctx, int pos, int a, int b, float r, float g, float bl, float al);
extern void kprintfContextCentering(float *ctx, char *fmt, ...);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void glEnable(int);
extern void scrRun(void);

static void func_00001D18(char *o)
{
    float ctx[16];
    int n = 15;
    int off;
    float dy;
    float y = 128.0f;
    float *flag;
    float v = *(float *)(*(char **)(o + 0x19C) + 0x88);
    char *gv;

    while (1) {
        if (iosInitKPrintfContext3D(ctx, *(int *)(o + 0x134), 1, 0,
                                    v < 0.0f ? 0.2f : 1.0f,
                                    v < 0.0f ? 0.5f : 0.2f,
                                    v < 0.0f ? 1.0f : 0.2f, 1.0f)) {
            ctx[0] += 60.0f;
            dy = y;
            ctx[2] += 60.0f;
            ctx[1] += dy;
            iosDlPushLayer(0x18);
            glEnable(3);
            kprintfContextCentering(ctx, RO_0017C0F8, v);
            iosDlPopLayer();
        }
        off = 0x180;
        gv = gcGlobalVar + off;
        if (*(flag = (float *)gv) != 0.0f) {
            n--;
            y -= 16.0f;
        }
        if (n < 0)
            return;
        scrRun();
    }
}
