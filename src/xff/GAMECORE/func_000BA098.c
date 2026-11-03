typedef struct {
    char pad0[0x94];
    float x94;
    float x98;
} AIParam;

typedef struct {
    char pad0[0x64];
    AIParam *param;
    char pad68[0x194 - 0x68];
    float x194;
    char pad198[0x19C - 0x198];
    float x19C;
    char pad1A0[0x220 - 0x1A0];
    float x220;
    float x224;
    float x228;
    char pad22C[0x230 - 0x22C];
    float x230;
    float x234;
    float x238;
    float x23C;
    char pad240[0x260 - 0x240];
    float x260;
    float x264;
} AIObj;

extern int AI_UpdateVelocity(float *, float, float);

static inline void decay(float *v)
{
    float a = *v;

    if (a < 0.0f) {
        a = -a;
    }
    AI_UpdateVelocity(v, 0.0f, a);
}

static void func_000BA098(AIObj *o)
{
    o->x230 = 0.0f;
    o->x260 = 1.0f;
    o->x264 = 1.0f;
    AI_UpdateVelocity(&o->x234, o->param->x94, o->param->x98);
    AI_UpdateVelocity(&o->x23C, 0.0f, 1.0f);
    o->x194 = 0.0f;
    o->x19C = 0.0f;
    decay(&o->x220);
    decay(&o->x224);
    decay(&o->x228);
}
