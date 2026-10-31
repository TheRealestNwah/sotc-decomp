typedef struct {
    float angle;
    float f04;
    float f08;
    float f0C;
    float f10;
    char pad14[0x1C - 0x14];
    float f1C;
    float f20;
    char pad24[0x30 - 0x24];
} MoveParamA3FA8;

typedef struct {
    char pad00[0x18];
    float range;
    char pad1C[0x40 - 0x1C];
    char sub40[0x80 - 0x40];
    float angle80;
    float f84;
    float f88;
    float f8C;
    char pad90[0xEC - 0x90];
    float fEC;
    float fF0;
    char padF4[0x100 - 0xF4];
    float angle100;
} DefA3FA8;

typedef struct {
    char pad00[0x20];
    DefA3FA8 *def;
    char pad24[0x40 - 0x24];
    int mode;
    char pad44[0x110 - 0x44];
    char pos[0x1D0 - 0x110];
    char rot[0x2B8 - 0x1D0];
    char vel0[0x2C8 - 0x2B8];
    char vel1[0x310 - 0x2C8];
    float speed;
} ObjA3FA8;

typedef union {
    ObjA3FA8 s;
} ObjA3FA8U;

extern float func_000A3AA0(float);
extern void AI_GetRandomVelocity(float *, void *, void *, float, float, float, float);
extern void func_000A33F8(ObjA3FA8 *, void *, void *, MoveParamA3FA8 *, void *);

static void func_000A3FA8(ObjA3FA8 *obj)
{
    MoveParamA3FA8 param;
    float t = func_000A3AA0(obj->def->f8C);
    DefA3FA8 *def;

    if (t != 0.0f) {
        obj->speed = 1.0f;
    } else {
        float r = obj->def->range;

        AI_GetRandomVelocity(&obj->speed, obj->vel0, obj->vel1, 1.0f - r, r + 1.0f, 1.0f, 5.0f);
    }
    def = obj->def;
    param.f04 = def->f84;
    param.f08 = obj->speed + t;
    param.f0C = 2.0f;
    param.f10 = def->f88;
    if (((ObjA3FA8U *)obj)->s.mode != 0) {
        param.angle = def->angle100 * 0.017453293f;
        param.f1C = def->fF0;
        param.f20 = def->fEC;
    } else {
        param.angle = def->angle80 * 0.017453293f;
        param.f20 = 0.0f;
        param.f1C = 1.0f;
    }
    func_000A33F8(obj, obj->pos, obj->rot, &param, def->sub40);
}
