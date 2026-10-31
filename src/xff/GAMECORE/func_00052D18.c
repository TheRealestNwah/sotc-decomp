typedef struct {
    char pad0[0x48];
    float length;
    float fadeIn;
    float fadeOut;
    float level;
    float accel;
    char pad5C[4];
    float maxSpeed;
} WaveParam;

typedef struct {
    char pad0[0x114];
    WaveParam *param;
} WaveObj;

typedef struct {
    WaveObj *obj;
    float scale;
} WaveOwner;

typedef struct Wave {
    char pad0[0x20];
    int active;
    float level;
    float dist;
    float speed;
    float time;
    WaveOwner *owner;
    struct Wave *next;
} Wave;

typedef struct {
    int pad0;
    Wave *free;
} WaveList;

typedef struct {
    char pad0[0x190];
    float dt;
} GcGlobal;

extern GcGlobal gcGlobalVar;
extern float AI_GetInterRatio(float, float, float, float, float);
extern void AI_UpdateVelocity(float *, float, float);

static inline void vecClear(void *v)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(v) : "memory");
}

static void func_00052D18(WaveList *list, Wave *w)
{
    WaveOwner *owner = w->owner;

    if (w->active) {
        WaveParam *p;
        float half = 0.5f / owner->obj->param->length;
        float r = AI_GetInterRatio(owner->scale, 0.0f, 1.0f, 1.0f - half, half + 1.0f);
        float t;
        float end, in, out;

        p = owner->obj->param;
        t = w->time;
        end = p->length * r;
        in = p->fadeIn * r;
        out = p->fadeOut * r;
        if (end < t) {
            vecClear(w);
            w->next = 0;
            w->speed = 0.0f;
            w->active = 0;
            do {
                w->level = 0.0f;
                w->dist = 0.0f;
            } while (0);
            w->time = 0.0f;
            w->next = list->free;
            list->free = w;
        } else {
            float start = end - out;

            if (start < t)
                w->level = AI_GetInterRatio(t, start, end, p->level, 0.0f);
            else if (in < t)
                w->level = p->level;
            else
                w->level = AI_GetInterRatio(t, 0.0f, in, 0.0f, p->level);
        }
        if (w->active) {
            AI_UpdateVelocity(&w->speed, owner->obj->param->accel, owner->obj->param->maxSpeed);
            w->dist += w->speed * gcGlobalVar.dt;
        }
        w->time += gcGlobalVar.dt;
    }
}
