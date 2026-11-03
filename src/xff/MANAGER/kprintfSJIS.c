typedef char *va_list;
#define va_start(ap, last)     (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))

typedef struct {
    float x;
    float y;
    float base_x;
    float base_y;
    float min_x;
    float min_y;
    float max_x;
    float max_y;
    float r;
    float g;
    float b;
    float a;
    int param0;
    int param1;
    int layer;
    float scale;
} KPrintContext;

typedef struct {
    int enabled;
    char pad[0x8C];
    float r;
    float g;
    float b;
    float a;
    int param0;
} KPrintState;

extern KPrintState D_001359F0;
extern char B_001482A8[];
extern int iosGetFontIDWithEUC(int);
extern int iosGetFontIDWithSJIS(int);
extern int iosDlGetLayer(void);
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern int vsprintf(char *, const char *, va_list);
extern void func_00015310(void *, char *, int (*)(int));

static inline void initContext(KPrintContext *ctx, float x, float y, float r, float g, float b, float a, int param0, int param1)
{
    ctx->base_x = x;
    ctx->base_y = y;
    ctx->x = x;
    ctx->y = y;
    ctx->r = r;
    ctx->g = g;
    ctx->b = b;
    ctx->a = a;
    ctx->param0 = param0;
    ctx->param1 = param1;
    ctx->layer = iosDlGetLayer();
    ctx->min_x = (float)(-getDrawScreenWidth() - 16);
    ctx->min_y = (float)(-getDrawScreenHeight() - 16);
    ctx->max_x = (float)getDrawScreenWidth();
    ctx->max_y = (float)getDrawScreenHeight();
    ctx->scale = 1.0f;
}

void kprintfSJIS(int x, int y, const char *fmt, ...)
{
    KPrintContext ctx;
    va_list ap;

    if (D_001359F0.enabled) {
        initContext(&ctx, x, y, D_001359F0.r, D_001359F0.g, D_001359F0.b, D_001359F0.a, D_001359F0.param0, 0);
        ctx.layer = iosDlGetLayer();
        va_start(ap, fmt);
        vsprintf(B_001482A8, fmt, ap);
        func_00015310(&ctx, B_001482A8, iosGetFontIDWithSJIS);
    }
}
