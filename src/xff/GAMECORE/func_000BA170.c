typedef struct {
    char pad0[0x94];
    float x94;
    float x98;
} AIParam;

typedef struct {
    char pad0[0x64];
    AIParam *param;
    char pad68[0x18C - 0x68];
    float x18C;
    char pad190[0x194 - 0x190];
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
    char pad268[0x2EC - 0x268];
    float x2EC;
} AIObj;

extern int AI_UpdateVelocity(float *, float, float);
extern void *isysGetThisSubThread(void);
extern void SetCharacterObjCollisionProcFlag(void *, int);

static void func_000BA170(AIObj *o)
{
    o->x230 = 0.0f;
    o->x260 = 1.0f;
    o->x264 = 1.0f;
    AI_UpdateVelocity(&o->x234, o->param->x94, o->param->x98);
    AI_UpdateVelocity(&o->x23C, 0.0f, 1.0f);
    o->x194 = 0.0f;
    o->x19C = 0.0f;
    if (o->x18C < 60.0f) {
        AI_UpdateVelocity(&o->x2EC, 1.0f, 0.1f);
        AI_UpdateVelocity(&o->x220, 0.0f, 1.0f);
        AI_UpdateVelocity(&o->x224, -0.2f, o->x2EC);
        AI_UpdateVelocity(&o->x228, 0.0f, 1.0f);
    } else {
        void *thread = isysGetThisSubThread();
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(&o->x220) : "memory");
        SetCharacterObjCollisionProcFlag(thread, 0);
    }
}
