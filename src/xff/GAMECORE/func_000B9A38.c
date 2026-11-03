typedef struct {
    char pad0[0x14];
    float x14;
    char pad18[0x3C - 0x18];
    float x3C;
    float x40;
    float x44;
    char pad48[0x94 - 0x48];
    float x94;
    float x98;
    float x9C;
    float xA0;
} AIParam;

typedef struct {
    char pad0[0x64];
    AIParam *param;
    char pad68[0x210 - 0x68];
    float x210;
    char pad214[0x218 - 0x214];
    float x218;
    char pad21C[0x230 - 0x21C];
    float x230;
    float x234;
    float x238;
    float x23C;
    char pad240[0x260 - 0x240];
    float x260;
    float x264;
} AIObj;

extern int AI_UpdateVelocity(float *, float, float);

static void func_000B9A38(AIObj *o)
{
    float f;

    AI_UpdateVelocity(&o->x23C, 0.0f, o->param->x44);
    AI_UpdateVelocity(&o->x264, o->x260 = o->param->xA0, o->param->x9C);
    f = o->x260;
    o->x230 = o->param->x14 * f;
    AI_UpdateVelocity(&o->x234, o->param->x94, o->param->x98);
    AI_UpdateVelocity(&o->x210, o->x230, o->x234);
    AI_UpdateVelocity(&o->x238, o->param->x40, o->param->x3C);
    AI_UpdateVelocity(&o->x218, 0.0f, o->x238);
}
