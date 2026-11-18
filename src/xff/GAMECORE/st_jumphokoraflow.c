typedef struct {
    char pad0[0x20];
    int flag;
    char pad24[0x74 - 0x24];
    float pos0[3];
    float rot0;
    float pos1[3];
    float rot1;
    int stage;
    unsigned int bgm;
    unsigned int seq;
    short count;
    short stage2;
    unsigned int seq2;
} DeadBoss;

extern int DldSysUndefSymbol;
extern char gcGlobalVar[];
extern int jumphokoraFlag[2];
extern int D_0017A2A8;
extern int BossStatus_POSEIDON;
extern int AdpcmSeq_HOME_BOSS_12_1;
extern DeadBoss *bossStatGetDeadBoss(void);
extern void *isysGetThisSubThread(void);
extern void scrInit(void *);
extern void bgmEnvTickProckMask(int);
extern int _gameFlagChk(int);
extern void _gameFlagSet(int);
extern void _gameFlagCls(int);
extern int bgmStandby(int, int, int, int);
extern void bgmPlay(int, float);
extern void bgmChangeVol(int, float, float);
extern void scrRun(void);
extern void PauseGame(int);
extern void setNowLoadingEffectDisplayFlagHokoraBack(int, int *, int);
extern void fadeOut(int, int, float);
extern void *get_main_cameraman(void);
extern void *get_game_camera(void *);
extern void compel_end_lws_movie_mode_game_camera(void *);
extern void end_stream_lws_movie_playing_game_camera(void *);
extern void reset_game_camera(void *);
extern void setDefaultFsEffect(void);
extern void PauseStageBoundaryManager(int);
extern void SetStageManagerAreaPreload(int);
extern void SetupStageManagerWithVariationId(int, int);
extern void setDemoBar(float, float);
extern void gameModeSet(int);
extern void gameModeCls(int);
extern void PauseCamFinalizer(int);
extern int SCRGetFirstObj(void *);
extern void ResetObject(int);
extern void CharaCtrlResetPlayableCtrlStatus(int);
extern void mapLogReset(void);
extern void gameflowSheetMgrAllReqWait(void);
extern void gStatLoadPlayerAccessories(void);
extern void setNowLoadingMessageDisplayFlag(int);
extern void func_0001A418(int, int, int, int, int, int);
extern void gameflowSetPos(int, float, float, float, float, float, float);

static inline int dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(int *)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

void st_jumphokoraflow(void)
{
    int bgm = 0;
    DeadBoss *boss = bossStatGetDeadBoss();
    int first;

    scrInit(isysGetThisSubThread());
    bgmEnvTickProckMask(1);
    if (!_gameFlagChk(0x1B)) {
        int seq = dldResolve(&boss->bgm);
        bgm = 0;
        if (seq != 0) {
            while ((bgm = bgmStandby(seq, 0, 0, 0)) == 0)
                scrRun();
            bgmPlay(bgm, 0.0f);
            bgmChangeVol(bgm, 100.0f, 0.5f);
        }
    }
    PauseGame(1);
    if (!_gameFlagChk(0x1B)) {
        D_0017A2A8 = 0;
        setNowLoadingEffectDisplayFlagHokoraBack(1, &D_0017A2A8, 1);
    } else {
        fadeOut(1, 0, 2.0f);
    }
    compel_end_lws_movie_mode_game_camera(get_main_cameraman());
    setDefaultFsEffect();
    PauseStageBoundaryManager(0);
    SetStageManagerAreaPreload((int)boss == BossStatus_POSEIDON ? 0 : 0x2D);
    SetupStageManagerWithVariationId(1, (int)boss != BossStatus_POSEIDON);
    setDemoBar(1.0f, 2.0f);
    gameModeSet(1);
    PauseCamFinalizer(1);
    {
        int pl = SCRGetFirstObj(gcGlobalVar + 0x2B0);
        ResetObject(pl);
        CharaCtrlResetPlayableCtrlStatus(pl);
    }
    mapLogReset();
    gameflowSheetMgrAllReqWait();
    D_0017A2A8 = 1;
    gStatLoadPlayerAccessories();
    setNowLoadingMessageDisplayFlag(0);
    first = !_gameFlagChk(0x1B);
    _gameFlagSet(0x1B);
    if ((int)boss == BossStatus_POSEIDON) {
        func_0001A418(0x18, bgm, AdpcmSeq_HOME_BOSS_12_1, 0, 1, first);
        first = 0;
        PauseStageBoundaryManager(0);
        bgm = 0;
        gameflowSheetMgrAllReqWait();
        SetStageManagerAreaPreload(0x2D);
        SetupStageManagerWithVariationId(1, 1);
        PauseCamFinalizer(1);
        gameflowSheetMgrAllReqWait();
    }
    func_0001A418(boss->stage, bgm, dldResolve(&boss->seq), 0x2D, 0, first);
    _gameFlagCls(0x1B);
    if (boss->stage2 != 0 && jumphokoraFlag[1] != 0 && jumphokoraFlag[1] < boss->count)
        func_0001A418(boss->stage2, 0, dldResolve(&boss->seq2), 0x2D, 0, 0);
    if (boss->flag != 0)
        _gameFlagSet(boss->flag);
    setDefaultFsEffect();
    end_stream_lws_movie_playing_game_camera(get_game_camera(get_main_cameraman()));
    if (jumphokoraFlag[1] != 0) {
        char *g = gcGlobalVar + 0x2B0;
        int pl = SCRGetFirstObj(g);
        int horse = SCRGetFirstObj(g + 4);
        gameflowSetPos(pl, boss->pos0[0], boss->pos0[1], boss->pos0[2], 0.0f, boss->rot0, 0.0f);
        gameflowSetPos(horse, boss->pos1[0], boss->pos1[1], boss->pos1[2], 0.0f, boss->rot1, 0.0f);
        scrRun();
        reset_game_camera(get_game_camera(get_main_cameraman()));
        scrRun();
    }
    PauseCamFinalizer(0);
    setDemoBar(0.0f, 2.0f);
    gameModeCls(1);
}
