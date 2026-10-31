typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x34];
    float maxDist;
    char pad38[0x40 - 0x38];
    float minAngle;
    float maxAngle;
} StepParam;

typedef struct {
    char pad0[0x20];
    StepParam *param;
    char pad24[0xE0 - 0x24];
    float dist;
    char padE4[0x198 - 0xE4];
    int state;
    char pad19C[0x1A4 - 0x19C];
    int next;
    char pad1A8[0x1AC - 0x1A8];
    int kind;
    char pad1B0[0x1B8 - 0x1B0];
    float time;
    float limit;
    char pad1C0[0x240 - 0x1C0];
    Vec4 plane;
    char pad250[0x26C - 0x250];
    int busy;
} Step;

extern void *isysGetThisSubThread(void);
extern char *GetCharacterClass(void *);
extern Vec4 *GetCollisionDBPlane(void *);
extern float iosGetASinfExact(float);
extern int func_0009C190(Step *);

static inline int canStart(Step *s)
{
    int kind = s->kind;

    if (!(kind == 1 || kind == 2 || kind == 3 || kind == 7))
        return 1;
    return s->busy != 0;
}

static inline int getGroundPlane(Vec4 *out)
{
    char *ch = GetCharacterClass(isysGetThisSubThread());
    int ground = *(int *)(ch + 0xFF0);

    if (ground != 0)
        out->q = GetCollisionDBPlane(ch + 0xFF8)->q;
    return ground;
}

static inline int canStep(Step *s)
{
    float angle;
    int kind = s->kind;

    if (!(kind == 1 || kind == 2 || kind == 3 || kind == 7) || s->busy != 0)
        return 0;
    if (s->param->maxDist < s->dist)
        return 0;
    if (!getGroundPlane(&s->plane))
        return 0;
    angle = -(iosGetASinfExact(s->plane.f[1]) * 57.29578f - 90.0f);
    if (s->param->minAngle <= angle && angle <= s->param->maxAngle)
        return 1;
    return 0;
}

static void func_0009C2F0(Step *s)
{
    isysGetThisSubThread();
    switch (s->state) {
    case 0:
        if (canStart(s))
            s->next = 1;
        break;
    case 1:
        if (s->limit > s->time)
            s->next = 2;
        break;
    case 2:
        if (s->limit > s->time)
            s->next = 3;
        break;
    case 3:
        if (canStep(s))
            s->next = 4;
        break;
    case 4:
        if (s->limit >= s->time)
            s->next = 0;
        break;
    case 5:
        if (func_0009C190(s))
            s->next = 6;
        break;
    }
}
