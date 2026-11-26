typedef struct {
    char unknown000[0x168];
    float animT;
    char unknown16C[0x170 - 0x16C];
    float animX;
    float animY;
    char unknown178[0x1AC - 0x178];
    int animOn;
} GlobalVar;

typedef struct {
    char pad0[0x28];
    void (*draw)(void *, int, int, int, float);
    void (*flush)(void *);
} SpriteMenu;

extern GlobalVar gcGlobalVar;
extern char rootPtn[];
extern char ZeroPoint[];
extern char IdentityQuaternion[];
extern int B_0018AF80;
extern int B_0018AF88[3];
extern int D_0017ABCC;
extern int D_0017ABD0;
extern int D_0017ABD4;
extern int D_0017ABD8;
extern int D_0017ABDC;
extern char *StageLayout_LEO_TORCH0;
extern char *StageLayout_LEO_TORCH1;
extern char *StageLayout_LEO_TORCH2;
extern char *StageLayout_LEO_TORCH3;
extern char *StageLayout_LEO_TORCH0_ANIM;
extern char *StageLayout_LEO_TORCH1_ANIM;
extern char *StageLayout_LEO_TORCH2_ANIM;
extern char *StageLayout_LEO_TORCH3_ANIM;
extern int *ScriptCtrlDef_SCRLeoTorchFinish;
extern int ScriptAnimationObjDef_LOAD_EFF_START;
extern int ScriptAnimationObjDef_LOAD_EFF_LOOP;
extern int ScriptAnimationObjDef_LOAD_EFF_END;

extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern char *GetSCRCharaAIWorkPtr();
extern void SetLayoutObjAccessSwitch(void *, int);
extern void *SCRGetFirstObj(void *);
extern void torchObjRelease(void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void isysRequestDeleteObj(void *);
extern void *isysGetThisSubThread(void);
extern void isysSleepSubThread(void);
extern void *get_main_cameraman_camera_obj(void);
extern int ExecObjectAnimation(void *, void *, float, float);
extern void fadeOut(int, int, float);
extern void *texSearchMopByName(char *);
extern float texAnimationOne(void *, float, float);
extern int _SCRSetupLWSSetScriptSetStackSize(int, int, void *, void *, void *, void *, int);
extern void _SCRStartLWSIgnorePause(int, int, int, int);
extern void scrRun(void);
extern int set_nowloadingflag();
extern SpriteMenu *GetSpriteMenuClass(void *);
extern void SpriteMenuSetLayer(void *, int);
extern void SpriteMenuSetDispFlagAll(void *, int);
extern int SpriteMenuIsFadeCheckAllLayer(void *);
extern void *gcCreateScriptObj(void *, int, void *, int, int, int, char *);

static const char RO_0017D6E0[] = "loading";

static void func_00064370(void *character);
static void T_00064410(void);
static void T_000644B0(void);
static void T_00064550(void);
static void T_000645F0(void);
static void func_00064660(void);
static void func_00064668(void);
static void func_00064670(void);
static void func_00064678(void);

void SCRLeoTorch0_Disp(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00064370);
}

void SCRLeoTorch1_Disp(void *character)
{
    RequestCharacterMotionShiftFunc(character, (void (*)(void *))T_00064410);
}

void SCRLeoTorch2_Disp(void *character)
{
    RequestCharacterMotionShiftFunc(character, (void (*)(void *))T_000644B0);
}

void SCRLeoTorch3_Disp(void *character)
{
    RequestCharacterMotionShiftFunc(character, (void (*)(void *))T_00064550);
}

int SCRConditionLeoCheckArmorBroken(void *actor)
{
    return (*(int *)(GetSCRCharaAIWorkPtr(actor) + 0x41C0)) != 0;
}

void SCRLeoArmorBroken(void *character)
{
    RequestCharacterMotionShiftFunc(character, (void (*)(void *))T_000645F0);
}

void SCRLeoFall(void *character)
{
    RequestCharacterMotionShiftFunc(character, (void (*)(void *))func_00064660);
}

void SCRLeoDamage(void *character)
{
    RequestCharacterMotionShiftFunc(character, (void (*)(void *))func_00064668);
}

void SCRLeoDashAttackEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, (void (*)(void *))func_00064670);
}

void SCRLeoDashAttack(void *character)
{
    RequestCharacterMotionShiftFunc(character, (void (*)(void *))func_00064678);
}

static void func_00064370(void *character)
{
    SetLayoutObjAccessSwitch(*(void **)(StageLayout_LEO_TORCH0 + 0x48), 1);
    B_0018AF80 = 1;
    torchObjRelease(SCRGetFirstObj((char *)&gcGlobalVar + 0x2B0));
    CharaCtrlSetScriptCtrlStatus(*(void **)(StageLayout_LEO_TORCH1_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
    CharaCtrlSetScriptCtrlStatus(*(void **)(StageLayout_LEO_TORCH2_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
    CharaCtrlSetScriptCtrlStatus(*(void **)(StageLayout_LEO_TORCH3_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
}

static void T_00064410(void)
{
    SetLayoutObjAccessSwitch(*(void **)(StageLayout_LEO_TORCH1 + 0x48), 1);
    B_0018AF80 = 1;
    torchObjRelease(SCRGetFirstObj((char *)&gcGlobalVar + 0x2B0));
    CharaCtrlSetScriptCtrlStatus(*(void **)(StageLayout_LEO_TORCH0_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
    CharaCtrlSetScriptCtrlStatus(*(void **)(StageLayout_LEO_TORCH2_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
    CharaCtrlSetScriptCtrlStatus(*(void **)(StageLayout_LEO_TORCH3_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
}

static void T_000644B0(void)
{
    SetLayoutObjAccessSwitch(*(void **)(StageLayout_LEO_TORCH2 + 0x48), 1);
    B_0018AF80 = 1;
    torchObjRelease(SCRGetFirstObj((char *)&gcGlobalVar + 0x2B0));
    CharaCtrlSetScriptCtrlStatus(*(void **)(StageLayout_LEO_TORCH0_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
    CharaCtrlSetScriptCtrlStatus(*(void **)(StageLayout_LEO_TORCH1_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
    CharaCtrlSetScriptCtrlStatus(*(void **)(StageLayout_LEO_TORCH3_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
}

static void T_00064550(void)
{
    SetLayoutObjAccessSwitch(*(void **)(StageLayout_LEO_TORCH3 + 0x48), 1);
    B_0018AF80 = 1;
    torchObjRelease(SCRGetFirstObj((char *)&gcGlobalVar + 0x2B0));
    CharaCtrlSetScriptCtrlStatus(*(void **)(StageLayout_LEO_TORCH0_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
    CharaCtrlSetScriptCtrlStatus(*(void **)(StageLayout_LEO_TORCH1_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
    CharaCtrlSetScriptCtrlStatus(*(void **)(StageLayout_LEO_TORCH2_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
}

static void T_000645F0(void)
{
    char *w = GetSCRCharaAIWorkPtr();

    if (*(int *)(w + 0x41C0) == 0) {
        isysRequestDeleteObj(*(void **)(w + 0x41B8));
        isysRequestDeleteObj(*(void **)(w + 0x41BC));
        isysRequestDeleteObj(*(void **)(w + 0x41B0));
        isysRequestDeleteObj(*(void **)(w + 0x41B4));
        *(int *)(w + 0x41C0) += 1;
    } else if (*(int *)(w + 0x41C0) == 1) {
        *(int *)(w + 0x41C0) = 2;
    }
}

static void func_00064660(void)
{
}

static void func_00064668(void)
{
}

static void func_00064670(void)
{
}

static void func_00064678(void)
{
}

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
    void *mop = texSearchMopByName("load_boss_worm");
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

int setNowLoadingMessageDisplayFlag(int a, int b, int c, int d)
{
    return set_nowloadingflag(a, b, c, d);
}

void nowLoadingScript(void)
{

    void *th = isysGetThisSubThread();
    SpriteMenu *sm = GetSpriteMenuClass(th);
    void *mop = texSearchMopByName((char *)RO_0017D6E0);
    float t;
    int prev;

    t = gcGlobalVar.animT;
    D_0017ABCC = 0;
    prev = -1;
    SpriteMenuSetLayer(th, 0);
    for (;;) {
        if (prev != D_0017ABCC)
            SpriteMenuSetDispFlagAll(th, D_0017ABCC);
        if (D_0017ABCC != 0 || SpriteMenuIsFadeCheckAllLayer(th))
            t = texAnimationOne(mop, t, gcGlobalVar.animX);
        sm->draw(th, 0, 0, 0, gcGlobalVar.animX);
        sm->flush(th);
        prev = D_0017ABCC;
        scrRun();
    }
}

int inInNowLoadingEffect(void)
{
    return D_0017ABD0;
}

void setNowLoadingEffectDisplayFlagHokoraBack(int flag, int arg, int wait)
{
    D_0017ABD8 = 1;
    if (D_0017ABD0 != flag) {
        D_0017ABD0 = flag;
        if (flag != 0) {
            D_0017ABD4 = 0;
            D_0017ABDC = 0;
            gcCreateScriptObj(func_00064798, arg, rootPtn, 0x1200, 0, 8, "st_drawNowLoadingEffect");
            if (wait != 0 && D_0017ABDC < 4) {
                do {
                    scrRun();
                } while (D_0017ABDC < 4);
            }
        }
    }
}
