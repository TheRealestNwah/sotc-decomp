typedef struct { char pad[0x170]; float dt; } GcGlobal;
extern GcGlobal gcGlobalVar;
extern int DebugFindPlayer(int);
extern int GAMEUTIL_get_first_obj(int);
extern void SetSeamlessStageControlObject(int);
extern void update_camera_obj(int);
extern int func_000E32B0(void *);
extern void func_000E3348(void *);
extern void func_000E3350(void *);
extern void func_000E3358(void *, float);
extern void func_000E33D0(void *);

typedef struct {
    int camObj;
    int mode;
    int owner;
    char pad0C[0xC];
    int prevTarget;
    int target;
    char pad20[0x37C0 - 0x20];
    float timer;
} Cameraman;

#ifdef NONMATCHING
void doit_cameraman(Cameraman *c, float f)
{
    int *mode = &c->mode;

    c->prevTarget = c->target;
    c->timer = c->timer - gcGlobalVar.dt;
    func_000E3350(c);
    if (func_000E32B0(c) == 0) {
        c->target = DebugFindPlayer(c->owner);
        if (c->target == 0) {
            c->target = GAMEUTIL_get_first_obj(c->owner);
            if (c->target == 0 && *mode != 2) {
                return;
            }
        }
    }
    func_000E3348(c);
    SetSeamlessStageControlObject(c->target);
    func_000E3358(c, f);
    update_camera_obj(c->camObj);
    func_000E33D0(c);
}
#else
extern void doit_cameraman(Cameraman *c, float f);
#endif
