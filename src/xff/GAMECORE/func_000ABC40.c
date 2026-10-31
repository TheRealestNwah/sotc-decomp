typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0xC];
    float speedScale;
    char pad10[0x1C - 0x10];
    float x;
    float x0;
    float x1;
    float y0;
    float y1;
    float yFixed;
    float yFixed2;
    char pad38[0x4C - 0x38];
    float accel;
    char pad50[0x58 - 0x50];
    float turnMax;
    float turnAccel;
    float turnMax2;
    float turnAccel2;
} RunParam;

typedef struct {
    char pad0[0x2C];
    int interp;
    char pad30[0x34 - 0x30];
    RunParam *param;
    char pad38[0x274 - 0x38];
    float flag274;
    char pad278[0x27C - 0x278];
    float flag27C;
    char pad280[0x28C - 0x280];
    float flag28C;
    char pad290[0x2C4 - 0x290];
    float blend;
    float blendTarget;
    float ratio;
    float yScale;
    char pad2D4[0x2DC - 0x2D4];
    float lean;
    float turn;
    char pad2E4[0x2F0 - 0x2E4];
    float roll;
    float leanVel;
    float speed;
    char pad2FC[0x314 - 0x2FC];
    float side;
    float sideVel;
    float flag31C;
    char pad320[0x330 - 0x320];
    Vec4 vel;
    float maxSpeed;
} Runner;

typedef struct {
    char pad0[0x10];
    float dir;
    char pad14[0x50 - 0x14];
    float dot;
} RunInput;

extern void *isysGetThisSubThread(void);
extern char *GetCharacterClass(void *);
extern int AI_UpdateVelocity(float *, float, float);
extern void AI_GetMotionBasicVelocity(Vec4 *, void *, float);

static void func_000ABC40(Runner *r, RunInput *in)
{
    char *ch = GetCharacterClass(isysGetThisSubThread());
    Vec4 vel;
    RunParam *p;
    float s;

    r->blendTarget = 1.0f;
    AI_UpdateVelocity(&r->blend, 1.0f, r->param->accel);
    AI_GetMotionBasicVelocity(&vel, ch + 0x9E0, r->blend);
    if (r->interp != 0) {
        p = r->param;
        r->yScale = (p->x - p->x0) * (p->y1 - p->y0) / (p->x1 - p->x0) + p->y0;
    } else {
        p = r->param;
        r->yScale = p->yFixed2;
    }
    r->flag27C = 0.0f;
    r->flag28C = 0.0f;
    r->vel.q = vel.q;
    r->maxSpeed = p->speedScale * r->yScale;
    AI_UpdateVelocity(&r->turn, p->turnAccel2, p->turnMax2);
    AI_UpdateVelocity(&r->speed, r->maxSpeed, 0.5f);
    p = r->param;
    r->ratio = r->speed / p->speedScale;
    r->flag31C = 0.0f;
    r->flag274 = 0.0f;
    AI_UpdateVelocity(&r->lean, 0.5f, 0.5f);
    AI_UpdateVelocity(&r->leanVel, 0.0f, r->lean);
    r->roll = 0.0f;
    s = 1.0f - (in->dot + 1.0f) * 0.5f;
    r->side = (r->roll < in->dir ? -s : s) * 0.8f;
    AI_UpdateVelocity(&r->sideVel, -0.3f, 0.1f);
}
