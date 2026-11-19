typedef struct {
    char unknown000[0x168];
    float animT;
    char unknown16C[0x170 - 0x16C];
    float animX;
    float animY;
    char unknown178[0x1AC - 0x178];
    int animOn;
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern int D_0017ABD0;
extern int D_0017ABD4;
extern int D_0017ABD8;
extern int D_0017ABDC;
extern void *isysGetThisSubThread(void);
extern void isysSleepSubThread(void);
extern void *get_main_cameraman_camera_obj(void);
extern int ExecObjectAnimation(void *, void *, float, float);
extern void fadeOut(int, int, float);
extern int B_0018AF88[3];
extern int ScriptAnimationObjDef_LOAD_EFF_START;
extern int ScriptAnimationObjDef_LOAD_EFF_LOOP;
extern int ScriptAnimationObjDef_LOAD_EFF_END;
extern char ZeroPoint[];
extern char IdentityQuaternion[];
extern int texSearchMopByName(char *);
extern float texAnimationOne(int, float, float);
extern int _SCRSetupLWSSetScriptSetStackSize(int, int, void *, void *, void *, void *, int);
extern void _SCRStartLWSIgnorePause(int, int, int, int);
extern void scrRun(void);

static void func_00064680(void)
{
    void *obj = isysGetThisSubThread();
    void *camera;
    float x;
    float y;

    for (;;) {
        camera = get_main_cameraman_camera_obj();
        x = gcGlobalVar.animX;
        y = gcGlobalVar.animY;
        switch (D_0017ABDC) {
        case 0:
            break;
        case 1:
        case 2:
            if (ExecObjectAnimation(obj, camera, x, y)) {
                D_0017ABDC = 3;
                return;
            }
            break;
        case 3:
        case 4:
            ExecObjectAnimation(obj, camera, x, y);
            break;
        case 5:
        case 6:
            if (ExecObjectAnimation(obj, camera, x, y)) {
                if (D_0017ABD8)
                    fadeOut(0, 0, 2.0f);
                D_0017ABDC = 7;
                return;
            }
            break;
        case 7:
        case 8:
            if (ExecObjectAnimation(obj, camera, x, y)) {
                D_0017ABDC = 9;
                return;
            }
            break;
        case 9:
            break;
        }
        isysSleepSubThread();
    }
}

static void func_00064798(int *done)
{
    void *th = isysGetThisSubThread();
    int mop = texSearchMopByName("load_boss_worm");
    float t = gcGlobalVar.animT;

    if (D_0017ABD4 == 0) {
        B_0018AF88[0] = _SCRSetupLWSSetScriptSetStackSize(ScriptAnimationObjDef_LOAD_EFF_START, 0, ZeroPoint,
                                                          IdentityQuaternion, th, func_00064680, 0x1800);
        B_0018AF88[1] = _SCRSetupLWSSetScriptSetStackSize(ScriptAnimationObjDef_LOAD_EFF_LOOP, 0, ZeroPoint,
                                                          IdentityQuaternion, th, func_00064680, 0x1800);
        B_0018AF88[2] = _SCRSetupLWSSetScriptSetStackSize(ScriptAnimationObjDef_LOAD_EFF_END, 0, ZeroPoint,
                                                          IdentityQuaternion, th, func_00064680, 0x1800);
    }
    _SCRStartLWSIgnorePause(B_0018AF88[0], -1, 1, 0);
    _SCRStartLWSIgnorePause(B_0018AF88[1], -1, 1, 0);
    _SCRStartLWSIgnorePause(B_0018AF88[2], -1, 1, 0);
    D_0017ABDC = 0;
    while (D_0017ABD0 != 0) {
        if (gcGlobalVar.animOn != 0)
            t = texAnimationOne(mop, t, gcGlobalVar.animX);
        switch (D_0017ABDC) {
        case 0:
            D_0017ABDC = 1;
            break;
        case 1:
            _SCRStartLWSIgnorePause(B_0018AF88[0], -1, 3, 0);
            D_0017ABDC = 2;
            break;
        case 3:
            _SCRStartLWSIgnorePause(B_0018AF88[1], -1, 5, 0);
            D_0017ABDC = 4;
        case 4:
            if (done != 0 && *done != 0)
                D_0017ABDC = 5;
            break;
        case 5:
            _SCRStartLWSIgnorePause(B_0018AF88[1], -1, 3, 0);
            D_0017ABDC = 6;
            break;
        case 7:
            _SCRStartLWSIgnorePause(B_0018AF88[2], -1, 3, 0);
            D_0017ABDC = 8;
            break;
        case 9:
            D_0017ABD0 = 0;
            break;
        }
        scrRun();
    }
}
