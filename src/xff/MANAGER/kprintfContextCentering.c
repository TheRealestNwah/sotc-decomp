typedef char *va_list;
#define va_start(ap, last) \
    (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))

typedef struct {
    int enabled;
    int font;
} KPrintState;

typedef struct {
    float x;
    float y;
    float base_x;
} KPrintContext;

typedef struct {
    char pad0[0x10];
    int width;
    char pad14[4];
    int space;
    char pad1c[4];
} FontInfo;

extern KPrintState D_001359F0;
extern char B_001482A8[];
extern int iosGetFontIDWithEUC(int);
extern void iosGetFontInfo(FontInfo *, int);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern int vsprintf(char *, const char *, va_list);
extern void func_00015310(void *, char *, int (*)(int));

void kprintfContextCentering(KPrintContext *ctx, const char *fmt, ...)
{
    FontInfo info;
    FontInfo *fi = &info;
    va_list ap;
    KPrintState *state = &D_001359F0;
    char *p;
    int n;
    char c;
    char d;

    if (state->enabled) {
        iosDlPushLayer(*(int *)((char *)ctx + 0x38));
        p = B_001482A8;
        va_start(ap, fmt);
        vsprintf(p, fmt, ap);
        iosGetFontInfo(fi, state->font);
        c = *p++;
        n = 0;
        if (c != 0 && c != '\n') {
            do {
                d = *p++;
                n++;
            } while (d != 0 && d != '\n');
        }
        ctx->x = ctx->base_x - (float)(n * ((fi->width * 2 - fi->space) >> 1)) * 0.5f;
        func_00015310(ctx, B_001482A8, iosGetFontIDWithEUC);
        iosDlPopLayer();
    }
}
