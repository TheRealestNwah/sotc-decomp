extern int isysGetThisSubThread(void);
extern void scrInit(int);
extern int PauseGame(int);
extern void ReleaseGame(int);
extern void gameModeSet(unsigned int);
extern void adpcmGamePause(int);
extern void sndSepPauseAll(int);
extern int sePlaySystemSound(int);
extern void timeAttackInScriptBegin(void);
extern void ReplayInScriptBegin(void);
extern int D_0017A08C;
extern int SeList_pause;
extern int gameflowStartMenuKaisou;
extern int B_00184870;
extern int _omakeSelectFlagChk(int);
extern void begin_check_and_boot_boss_subjective_camera_lws_animation(void);
extern void end_check_and_boot_boss_subjective_camera_lws_animation(void);
extern void fadeIn(int, int, float);
extern int vschedGameTimeExec;
extern int D_0017A078;
extern void scrRun(void);
extern void _SCRStartSpriteMenuAnim(int, int, int, int, int, int);
extern int ScriptSpriteMenuObjDef_SPRITE_GAME_OVER_LAYOUT;
extern int D_0017A090;
extern void bgmStop(void *, int *, float);
extern void *getFogUnderWater(void);
extern char *sePlay(char *);
extern int seStop(char *);
extern void soundSetRevMode(int, int);
extern char *D_0017A1E4;
extern char *SeList_in_water_muddy1;
extern char *DldSysUndefSymbol;
extern void *SCRGetFirstObj(void *);
extern void SetGeometryPointerNodePosState(void *, int, int, void *, void *);
extern int sePlay3D(int, void *, int, int);
extern int SeList_hp_alert, SeList_grip_alert, SeList_grip_alert_vo;
extern int D_0017A05C, D_0017A064, D_0017A068;
extern char B_001847F0[], gcGlobalVar[], IdentityQuaternion[], ZeroPoint[];

static void func_000186A8(void)
{
    scrInit(isysGetThisSubThread());
    PauseGame(1);
}
static void T_000186D0(void)
{
    scrInit(isysGetThisSubThread());
    ReleaseGame(1);
}
static void T_000186F8(void)
{
    scrInit(isysGetThisSubThread());
    PauseGame(1);
}
static void T_00018720(void)
{
    scrInit(isysGetThisSubThread());
    ReleaseGame(1);
}
static void T_00018748(void)
{
    scrInit(isysGetThisSubThread());
    gameModeSet(1);
    D_0017A08C = 1;
    adpcmGamePause(1);
    sndSepPauseAll(1);
    sePlaySystemSound(SeList_pause);
    if (gameflowStartMenuKaisou == 0)
        timeAttackInScriptBegin();
    else
        ReplayInScriptBegin();
}
static void T_000187B0(void)
{
    scrInit(isysGetThisSubThread());
    adpcmGamePause(0);
    sndSepPauseAll(0);
    D_0017A08C = 0;
    B_00184870 = 9;
}
static void func_000187F8(void)
{
    scrInit(isysGetThisSubThread());
    ReleaseGame(1);
    vschedGameTimeExec = 1;
    adpcmGamePause(0);
    sndSepPauseAll(0);
    D_0017A08C = 0;
    if (_omakeSelectFlagChk(25)) {
        D_0017A078 = 1;
        begin_check_and_boot_boss_subjective_camera_lws_animation();
    } else {
        end_check_and_boot_boss_subjective_camera_lws_animation();
        D_0017A078 = 0;
    }
    if (gameflowStartMenuKaisou != 0)
        fadeIn(0, 0, 0.39999998f);
}
static void func_000188B0(int *done)
{
    int thread = isysGetThisSubThread();
    scrInit(thread);
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_GAME_OVER_LAYOUT,
        thread, 0, (int)done, 0, (int)&D_0017A090);
    while (*done == 0)
        scrRun();
}
static void func_00018970(void)
{
    scrInit(isysGetThisSubThread());
    D_0017A08C = 0;
    B_00184870 = 3;
}
static void func_000189A8(void *bgm)
{
    bgmStop(bgm, 0, 1.5f);
}
static void func_00018A58(void)
{
    int underwater = *(int *)getFogUnderWater();
    if (D_0017A1E4 == 0) {
        if (underwater && SeList_in_water_muddy1 != DldSysUndefSymbol)
            D_0017A1E4 = sePlay(SeList_in_water_muddy1);
    } else if (!underwater) {
        seStop(D_0017A1E4);
        D_0017A1E4 = 0;
    }
    if (underwater)
        soundSetRevMode(0, 2);
    else
        soundSetRevMode(1, 2);
}
static void func_00018B08(void)
{
    D_0017A05C = sePlaySystemSound(SeList_hp_alert);
}
static void func_00018B38(void)
{
    D_0017A064 = sePlaySystemSound(SeList_grip_alert);
    SetGeometryPointerNodePosState(B_001847F0, (int)SCRGetFirstObj(gcGlobalVar + 0x2b0),
        0, IdentityQuaternion, ZeroPoint);
    D_0017A068 = sePlay3D(SeList_grip_alert_vo, B_001847F0, 0, 0);
}