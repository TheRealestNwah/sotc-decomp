extern char rootPtn[], gcGlobalVar[];
extern int gameflowAlertDisable, gstatTimeAttackMode, __gameMode, playerEnableDeath;
extern int AdpcmSeq_P_DOWN, StageData_PLAYER_BATTLE_END_MOT;
extern int ScrIntrDef_GAME_ENDING, ScrIntrDef_JUMP_HOKORA;
extern char *ScriptCtrlDef_SCRPlayerBreakDown;
extern int D_0017AF74, D_0017AF7C;
extern void *DldSysUndefSymbol;
extern int bossStatGetActiveBoss(void);
extern int isysGetThisSubThread(void);
extern void scrInit(int);
extern void scriptIntrAllDeleteJump(int);
extern void gameflowBossEyeCameraDisable(int);
extern void setSmallManagerSystemLock(int);
extern char *SCRGetFirstObj(void *);
extern void gameflowSetPauseEnable(int);
extern void gStatStopTimeAttack(void);
extern int *GetAnimationClass(char *);
extern void scrRun(void);
extern void YattsukeSetPlayerR1ON(int);
extern void stagemanager_loadstagecore(void *, int, int, int);
extern void effect_death(int, char *);
extern int get_main_cameraman(void);
extern void set_post_boss_dead_playable_flag_camera_etc_control(int, int);
extern int bgmStandby(int, int, int, int);
extern int CheckDeathTentacle(void);
extern int bgmChkStandbyComplete(int);
extern void bgmPlay(int, float);
extern void bgmStop(int, float);
extern void SetPlayerStatusDispSw(int);
extern void addPlayerMaxHp(float);
extern void addPlayerMaxGrip(float);
extern char *getSCRDataCtrlWork(char *);
extern int stagemanager_checkstageAlreadyLoadedByStageData(int);
extern void PauseGame(int);
extern void ReleaseGame(int);
extern void CharaCtrlSetOutsideScriptCtrlStatus(char *, int);
extern void stagemanager_unloadstagecore(int);
extern void endBossDeathEffect(void);
extern void bossStatSetDeadBoss(int);
extern int bossStatSrhSheetAliveBoss(void);
extern void scriptIntrSignal(int);
extern void bossStatSetActiveBoss(int);
extern void isysJumpSubThread(void (*)(void), int);
extern void st_boss_status(void);

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        return *(char **)(module + 0x10) + index * *(int *)(*(char **)(module + 8) + 0xC);
    }
    return 0;
}

#ifdef NONMATCHING /* 279 diffs, 348 vs 344 words: dld-resolve branch forms, wait-loop layout and saved-register assignment */
void st_boss_dead(int arg)
{
    char *boss = (char *)bossStatGetActiveBoss();
    int thr = isysGetThisSubThread();
    char *obj, *s3p, *p;
    int *anim;
    int bgm, cam, next;

    scrInit(thr);
    scriptIntrAllDeleteJump(thr);
    gameflowAlertDisable = 1;
    gameflowBossEyeCameraDisable(1);
    setSmallManagerSystemLock(1);
    if (boss) {
        obj = SCRGetFirstObj(gcGlobalVar + 0x2B8);
        gameflowSetPauseEnable(0);
        if (gstatTimeAttackMode)
            gStatStopTimeAttack();
        anim = GetAnimationClass(obj);
        p = resourceData((unsigned int *)(boss + 0x30));
        while (*anim != (int)p)
            scrRun();
        scrRun();
        if ((*(unsigned *)(boss + 0x50) >> 1) & 1)
            YattsukeSetPlayerR1ON(1);
        if (*(int *)(boss + 0x38)) {
            stagemanager_loadstagecore(rootPtn, *(int *)(boss + 0x38), *(unsigned char *)(boss + 0x51), 0);
            s3p = SCRGetFirstObj(gcGlobalVar + 0x2B8);
            anim = GetAnimationClass(s3p);
            p = resourceData((unsigned int *)(boss + 0x34));
            while (*anim != (int)p)
                scrRun();
            p = resourceData((unsigned int *)(boss + 0x3C));
            effect_death(*(int *)(p + 8), s3p);
        }
        D_0017AF74 = 4;
        cam = get_main_cameraman();
        set_post_boss_dead_playable_flag_camera_etc_control(cam, 1);
        while (__gameMode & 1)
            scrRun();
        YattsukeSetPlayerR1ON(0);
        do {
            bgm = bgmStandby(AdpcmSeq_P_DOWN, 0, 0, 0);
            if (bgm)
                break;
            scrRun();
        } while (1);
        while (CheckDeathTentacle())
            scrRun();
        if (bgmChkStandbyComplete(bgm))
            bgmPlay(bgm, 100.0f);
        D_0017AF7C = 0;
        SetPlayerStatusDispSw(1);
        if (!gstatTimeAttackMode) {
            addPlayerMaxHp(*(float *)(boss + 0xB4));
            addPlayerMaxGrip(*(float *)(boss + 0xB8));
        }
        if (resourceData((unsigned int *)(*(char **)(getSCRDataCtrlWork(obj) + 0x417C)))) {
            if (!stagemanager_checkstageAlreadyLoadedByStageData(StageData_PLAYER_BATTLE_END_MOT)) {
                PauseGame(1);
                while (!stagemanager_checkstageAlreadyLoadedByStageData(StageData_PLAYER_BATTLE_END_MOT))
                    scrRun();
                ReleaseGame(1);
            }
        }
        if (D_0017AF7C == 0) {
            do {
                CharaCtrlSetOutsideScriptCtrlStatus(SCRGetFirstObj(gcGlobalVar + 0x2B0), *(int *)(ScriptCtrlDef_SCRPlayerBreakDown + 4));
                scrRun();
            } while (D_0017AF7C == 0);
        }
        set_post_boss_dead_playable_flag_camera_etc_control(cam, 0);
        if (D_0017AF7C != 2) {
            do {
                scrRun();
            } while (D_0017AF7C != 2);
        }
        bgmStop(bgm, 2.0f);
        if (*(int *)(boss + 0x38)) {
            stagemanager_unloadstagecore(*(int *)(boss + 0x38));
            endBossDeathEffect();
        }
        bossStatSetDeadBoss((int)boss);
        SetPlayerStatusDispSw(0);
        playerEnableDeath = 1;
        next = bossStatSrhSheetAliveBoss();
        if (next == 0 && !gstatTimeAttackMode) {
            scriptIntrSignal(ScrIntrDef_GAME_ENDING);
        } else {
            scriptIntrSignal(ScrIntrDef_JUMP_HOKORA);
            bossStatSetActiveBoss(next);
        }
    }
    gameflowSetPauseEnable(1);
    gameflowAlertDisable = 0;
    gameflowBossEyeCameraDisable(0);
    isysJumpSubThread(st_boss_status, arg);
}
#endif
