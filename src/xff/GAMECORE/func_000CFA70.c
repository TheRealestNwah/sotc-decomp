/* Parked: 2 diffs, same size. Remaining: the init block stores button
 * (0x1C) before button10 (0x10); the Original stores 0x10 first. Writing
 * state, button, button10 in that order is the closest of the six orders. */
typedef struct {
    int state;
    int pad4;
    int sel;
    int done;
    int button10;
    float f14;
    float f18;
    int button;
    char pad20[0x50 - 0x20];
    float f50;
    float f54;
    char pad58[0x5C - 0x58];
    float f5C;
    int tex[6];
} PauseWork;

typedef void (*DrawFn)(void *, int, int, int, float);

typedef struct { char pad[0x168]; float time; int pad16C; float f170; } GcGlobal;
extern GcGlobal gcGlobalVar;
extern int FsEffect_PAUSE_BLUR;
extern int ScriptAnimationObjDef_PAUSE_CLOUD_END;
extern int ScrIntrDef_GAME_CANCEL;
extern int ScrIntrDef_MENU_CONTINUE;
extern char ZeroPoint[];
extern char IdentityQuaternion[];
extern const char RO_00180C18[];
extern const char RO_00180C20[];
extern const char RO_00180C30[];
extern const char RO_00180C40[];
extern const char RO_00180C58[];
extern const char RO_00180C68[];

extern char *GetSpriteMenuClass(void);
extern void fsEffectCreateSetScript(int, void *, int);
extern void *get_main_cameraman(void);
extern void *get_game_camera(void *);
extern void begin_pause_rise_game_camera(void *, void *);
extern float get_begin_interp_finish_time_camera_pause_rise(void);
extern void feedbackBlur2(int, float, float);
extern void scrRun(void);
extern int texSearchMopByName(const char *);
extern void SpriteMenuSetDispFlag(void *, int, int);
extern void SetLayoutDisplayFlag(int);
extern void *_SCRSetupLWSIgnorePauseSetStackSize(int, int, void *, void *, void *, int);
extern void _SCRStartLWSIgnorePause(void *, int, int, int);
extern void request_end_pause_rise_game_camera(void *, void *);
extern int is_end_pause_rise_game_camera(void *, void *);
extern int SpriteMenuIsFadeCheckSelectLayer(void *);
extern void scriptIntrSignal(int);
extern void func_000CF000(void *, char *, PauseWork *);
extern void func_000CF140(void *, char *, PauseWork *);
extern void func_000CF500(void *, char *, PauseWork *);
extern int func_000CF8E8(void *, char *, PauseWork *);

#define G(type, o) (*(type *)((char *)&gcGlobalVar + (o)))

#ifdef NONMATCHING
void func_000CFA70(int *menu)
{
    PauseWork w;
    char *cls;
    float start, t;
    void *cam, *gcam, *cam0;

    cls = GetSpriteMenuClass();
    start = gcGlobalVar.time;
    fsEffectCreateSetScript(menu[0], menu, FsEffect_PAUSE_BLUR);
    cam0 = get_main_cameraman();
    begin_pause_rise_game_camera(get_game_camera(cam0), cam0);
    t = get_begin_interp_finish_time_camera_pause_rise();
    while (gcGlobalVar.time - start < t * 0.5f) {
        feedbackBlur2((gcGlobalVar.time - start) * 64.0f / (t * 0.5f), 1.0f, 0.0f);
        scrRun();
    }
    w.f18 = 2.25f;
    w.f14 = 1.0f;
    w.state = 1;
    w.button = 3;
    w.button10 = 1;
    w.pad4 = 0;
    w.done = 0;
    w.sel = 0;
    w.tex[0] = texSearchMopByName(RO_00180C18);
    w.tex[1] = texSearchMopByName(RO_00180C20);
    w.tex[2] = texSearchMopByName(RO_00180C30);
    w.tex[3] = texSearchMopByName(RO_00180C40);
    w.tex[4] = texSearchMopByName(RO_00180C58);
    w.tex[5] = texSearchMopByName(RO_00180C68);
    w.f50 = w.f54 = 0.0f;
    w.f5C = gcGlobalVar.time;
    SpriteMenuSetDispFlag(menu, 0, 1);
    while (gcGlobalVar.time - start < t + 0.1f) {
        func_000CF500(menu, cls, &w);
        (*(DrawFn *)(cls + 0x28))(menu, 0, 0, 0, gcGlobalVar.f170);
        func_000CF140(menu, cls, &w);
        func_000CF000(menu, cls, &w);
        feedbackBlur2((t + 0.1f - (gcGlobalVar.time - start)) * 64.0f / (t + 0.1f), 1.0f, 0.0f);
        scrRun();
    }
    SetLayoutDisplayFlag(0);
    for (;;) {
        func_000CF500(menu, cls, &w);
        if (func_000CF8E8(menu, cls, &w) != 0)
            break;
        (*(DrawFn *)(cls + 0x28))(menu, w.button10 != 0, 0, 0, gcGlobalVar.f170);
        func_000CF140(menu, cls, &w);
        func_000CF000(menu, cls, &w);
        scrRun();
    }
    SetLayoutDisplayFlag(1);
    func_000CF500(menu, cls, &w);
    func_000CF8E8(menu, cls, &w);
    (*(DrawFn *)(cls + 0x28))(menu, 0, 0, 0, gcGlobalVar.f170);
    func_000CF140(menu, cls, &w);
    func_000CF000(menu, cls, &w);
    feedbackBlur2(0x40, 1.0f, 0.0f);
    scrRun();
    _SCRStartLWSIgnorePause(_SCRSetupLWSIgnorePauseSetStackSize(ScriptAnimationObjDef_PAUSE_CLOUD_END, 0, ZeroPoint, IdentityQuaternion, menu, 0x1000), -1, 3, 0);
    cam = get_main_cameraman();
    gcam = get_game_camera(cam);
    request_end_pause_rise_game_camera(gcam, cam);
    while (SpriteMenuIsFadeCheckSelectLayer(menu) != 0) {
        func_000CF500(menu, cls, &w);
        func_000CF8E8(menu, cls, &w);
        (*(DrawFn *)(cls + 0x28))(menu, 0, 0, 0, gcGlobalVar.f170);
        func_000CF140(menu, cls, &w);
        func_000CF000(menu, cls, &w);
        feedbackBlur2(0x40, 1.0f, 0.0f);
        scrRun();
    }
    while (is_end_pause_rise_game_camera(gcam, cam) == 0) {
        feedbackBlur2(0x3C, 1.0f, 0.0f);
        scrRun();
    }
    if (w.sel != 0)
        scriptIntrSignal(ScrIntrDef_GAME_CANCEL);
    else
        scriptIntrSignal(ScrIntrDef_MENU_CONTINUE);
}
#endif
