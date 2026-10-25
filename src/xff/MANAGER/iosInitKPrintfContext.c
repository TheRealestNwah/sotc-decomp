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

extern int iosDlGetLayer(void);
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);

void iosInitKPrintfContext(KPrintContext *ctx, int param0, int param1, float x, float y, float r, float g, float b, float a)
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
