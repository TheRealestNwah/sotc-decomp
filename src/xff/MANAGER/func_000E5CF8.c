typedef unsigned int s128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x10];
    int flags;
} LwsDef;

typedef struct {
    LwsDef *def;
    char anim[0x40];
    int motion;
    int usePos;
    int x4C;
    char gp[0x40];
    s128 pos;
    int xA0;
    void (*callback)(int);
    int callbackArg;
    int xAC;
    int started;
    int xB4;
    char padB8[0xC0 - 0xB8];
} CameraLwsAnime;

extern float func_000E72E0(LwsDef *);
extern void func_000E7388(CameraLwsAnime *, LwsDef *, int);
extern void UpdateAnimationClassPastSimpleInfo(void *);
extern int GetAnimationClassCurrentInfoDirectResource(void *, int, float, float);
extern void SetAnimationClassLastInfoDirectResource(void *, int);
extern void GetGeometryPointerPosition(void *, void *);
extern void InitAnimationClass(void *, char *);
extern void CopyGeometryPointer(void *, void *);
extern char InitialGeometryPointer[];
extern s128 ZeroPoint;

static void func_000E5CF8(CameraLwsAnime *a, int layout, int unused, float time)
{
    LwsDef *def;
    int on;
    float t;

    def = a->def;
    on = def != 0;
    if (def == 0) {
        return;
    }
    t = func_000E72E0(def);
    UpdateAnimationClassPastSimpleInfo(a->anim);
    if (a->started == 0) {
        if (GetAnimationClassCurrentInfoDirectResource(a->anim, a->motion, t, time) != 0) {
            a->started = on;
            if ((def->flags & 7) == 2) {
                SetAnimationClassLastInfoDirectResource(a->anim, a->motion);
            }
        }
    } else if ((def->flags & 7) != 2) {
        GetAnimationClassCurrentInfoDirectResource(a->anim, a->motion, t, time);
    }
    if (a->usePos != 0) {
        GetGeometryPointerPosition(&a->pos, a->gp);
    }
    func_000E7388(a, def, layout);
    if ((def->flags & 7) == 0 && a->started == 1) {
        if (a->xA0 != 0 && a->callback != 0) {
            a->callback(a->callbackArg);
        }
        a->def = 0;
        InitAnimationClass(a->anim, 0);
        a->motion = 0;
        a->usePos = 0;
        CopyGeometryPointer(a->gp, InitialGeometryPointer);
        a->pos = ZeroPoint;
        a->xA0 = 0;
        a->callback = 0;
        a->callbackArg = 0;
        a->xAC = 0;
        a->started = 0;
        a->xB4 = 0;
    }
}
