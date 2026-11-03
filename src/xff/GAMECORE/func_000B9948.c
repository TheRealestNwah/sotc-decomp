typedef struct {
    char pad0[0x20];
    float x20;
    char pad24[0x3C - 0x24];
    float x3C;
    float x40;
    float x44;
    char pad48[0xA4 - 0x48];
    float xA4;
} AIParam;

typedef struct {
    char pad0[0x64];
    AIParam *param;
    char pad68[0x184 - 0x68];
    float x184;
    char pad188[0x18C - 0x188];
    float x18C;
    char pad190[0x210 - 0x190];
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
    char pad268[0x2E8 - 0x268];
    float x2E8;
    float x2EC;
    float x2F0;
} AIObj;

extern int AI_UpdateVelocity(float *, float, float);

static void func_000B9948(AIObj *o)
{
    float t;

    o->x184 = 0.0f;
    o->x260 = 1.0f;
    AI_UpdateVelocity(&o->x264, 1.0f, o->param->x20);
    o->x230 = 0.0f;
    t = o->x18C;
    if (t <= o->param->xA4) {
        o->x210 = o->x2F0 + o->x2E8 * 0.5f * t * t + o->x2EC * t;
    } else {
        AI_UpdateVelocity(&o->x210, o->x230, 1.0f);
    }
    AI_UpdateVelocity(&o->x238, o->param->x40, o->param->x3C);
    AI_UpdateVelocity(&o->x218, 0.0f, o->x238);
    AI_UpdateVelocity(&o->x23C, 0.0f, o->param->x44);
}
