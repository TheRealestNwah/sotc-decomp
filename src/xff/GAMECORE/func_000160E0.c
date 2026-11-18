typedef struct { char pad[8]; struct { char pad[0xC]; int stride; } *type; char pad2[4]; char *base; } DldSym;
typedef struct { int normal; int pad4; int hard; int padC; int *flag; } TAItem;

extern int checkPointChangeHorse;
extern int gameflowBootBossWait;
extern DldSym *DldSysUndefSymbol;
typedef struct { char pad[0x10]; TAItem *items; } TAList;
extern TAList SH_TimeAttackItemListDEFAULT;
extern void func_000189A8(void);
extern void PauseGame(int);
extern void PauseSeamlessStageManager(int);
extern void PauseCamFinalizer(int);
extern void SetupStageManager(int);
extern void SetupStageManagerWithVariationId(int, int);
extern void fadeOut(int, int, float);
extern int gStatCheckPointLoad(void);
extern float GetTimeAttackTimeLimit(void);
extern char *bossStatGetDeadBoss(void);
extern char *bossStatGetActiveBoss(void);
extern void _gameFlagSet(int);
extern void _gameFlagCls(int);
extern int _gameFlagChk(int);
extern int time_attack_get_clear_num(void);
extern int getGameHardMode(void);
extern int _omakeGetFlagChk(int);
extern int _omakeSelectFlagChk(int);
extern void omakeGetAndSelectSet(int);
extern void omakeGetAndSelectCls(int);
extern void gStatOmakeSave(void);
extern void gStatRestartPlayerChara(void);
extern void gStatReloadHorseChara(void);
extern void gStatLoadPlayerAccessories(void);
extern void scrRun(void);
extern int bgmStandby(char *, int, int, int *);
extern int bgmChkStandbyComplete(int);
extern void bgmPlay(int, float);
extern void setScrDemoMangerFinishCallback(void (*)(void), int);
extern void sheetMgrAllReqWait(int *);

static inline void gameflowChangeHorse(void)
{
    if (checkPointChangeHorse == 1) {
        if (!_omakeSelectFlagChk(8))
            omakeGetAndSelectSet(8);
        else
            omakeGetAndSelectCls(8);
        gStatOmakeSave();
    } else if (checkPointChangeHorse == 2) {
        if (!_omakeSelectFlagChk(9))
            omakeGetAndSelectSet(9);
        else
            omakeGetAndSelectCls(9);
        gStatOmakeSave();
    }
    checkPointChangeHorse = 0;
}

static void func_000160E0(int timeAttack, int fade)
{
    int handle;
    int st;
    int stage;
    int bgm;
    char *boss;

    bgm = 0;
    PauseGame(1);
    PauseSeamlessStageManager(1);
    PauseCamFinalizer(1);
    SetupStageManager(-1);
    if (fade)
        fadeOut(1, 0, 0.4f);
    stage = gStatCheckPointLoad();
    if (timeAttack && GetTimeAttackTimeLimit() >= 0.0f) {
        TAItem *item;
        _gameFlagSet(*(int *)(bossStatGetDeadBoss() + 0xCC));
        { int n = time_attack_get_clear_num(); item = SH_TimeAttackItemListDEFAULT.items; item += n; }
        {
            int v = getGameHardMode() ? item->hard : item->normal;
            if (v != 0) {
                if (_omakeGetFlagChk(getGameHardMode() ? item->hard : item->normal) == 0)
                    _gameFlagSet(item->flag[2]);
            }
        }
    }
    gameflowChangeHorse();
    gStatRestartPlayerChara();
    if (!_gameFlagChk(0x1C))
        gStatReloadHorseChara();
    gStatLoadPlayerAccessories();
    PauseCamFinalizer(0);
    scrRun();
    SetupStageManagerWithVariationId(1, stage);
    PauseSeamlessStageManager(0);
    if (_gameFlagChk(0x1D)) {
        boss = bossStatGetActiveBoss();
        _gameFlagCls(0x1D);
        if (boss) {
            handle = 0;
            bgm = 0;
            if (*(int *)(boss + 0xD8)) {
                unsigned int *h;
                _gameFlagSet(*(int *)(boss + 0xD8));
                if (handle == 0) {
                h = (unsigned int *)(boss + 0xD4);
                do {
                    unsigned int off = *h & 0x3FFFF;
                    DldSym *sym = off ? *(DldSym **)((char *)h - off) : 0;
                    char *res = (sym && sym != DldSysUndefSymbol)
                        ? sym->base + ((*h >> 18) & 0xFFF) * sym->type->stride : 0;
                    if (res)
                        handle = bgmStandby(res, 0, 0, &handle);
                    scrRun();
                } while (handle == 0);
                }
                while (!bgmChkStandbyComplete(handle))
                    scrRun();
                setScrDemoMangerFinishCallback(func_000189A8, handle);
                bgm = handle;
            }
            gameflowBootBossWait = 1;
        }
    }
    scrRun();
    sheetMgrAllReqWait(&st);
    while ((unsigned int)(st - 0xDEAF) >= 2)
        scrRun();
    if (bgm)
        bgmPlay(bgm, 100.0f);
}
