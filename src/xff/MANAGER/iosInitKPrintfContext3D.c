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
extern float UnitMatrix[];
extern void glLoadMatrixf(float *);
extern void iosgluGetViewCoordPosition(float *, float *);

int iosInitKPrintfContext3D(KPrintContext *ctx, float *pos, int param0, int param1, float r, float g, float b, float a)
{
    float view[4];

    glLoadMatrixf(UnitMatrix);
    iosgluGetViewCoordPosition(view, pos);
    ctx->r = r;
    ctx->base_x = view[0];
    ctx->base_y = view[1];
    ctx->x = view[0];
    ctx->y = view[1];
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
    return 0.0f < view[2];
}
