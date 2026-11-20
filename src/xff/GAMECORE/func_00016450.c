typedef struct { char pad[8]; struct { char pad[0xC]; int stride; } *type; char pad2[4]; char *base; } DldSym;
typedef struct {
    float x, y, z, w;
} Vec4 __attribute__((aligned(8)));

typedef struct {
    char pad[0x2B0];
    char objList[4];
    char horseList[4];
} GcGlobal;

extern GcGlobal gcGlobalVar;
extern int gameflowBootBossWait;
extern int gstatTimeAttackMode;
extern int gstatKaisouMode;
extern DldSym *DldSysUndefSymbol;
extern char *BossStatus_EVIS;
extern void func_000189A8(void);
extern char *bossStatGetActiveBoss(void);
extern void *SCRGetFirstObj(void *);
extern void *isysGetThisSubThread(void);
extern void scrInit(void *);
extern void PauseGame(int);
extern void fadeOut(float, int, int);
extern void setNowLoadingMessageDisplayFlag(int);
extern void SetupStageManager(int);
extern void backStageInit(void);
extern void *getPlayerColCont2(void *);
extern void ColCont2_Release(void *);
extern void YattsukeGetSeamlessAreaCenter(Vec4 *, int);
extern void GetQuaternionByDegEulerYXZ(Vec4 *, float, float, float);
extern void DebugSetObjectGeometry(void *, Vec4 *, Vec4 *);
extern char *GetLayoutClass(void *);
extern void backStageGobjSave(int);
extern void gStatRestartPlayerChara(void);
extern void gStatReloadHorseChara(void);
extern void gStatUnloadHorseChara(void);
extern void gStatLoadPlayerAccessories(void);
extern void bossStatSekibanJumpSetHorsePos(char *);
extern void *get_main_cameraman(void);
extern void *get_game_camera(void *);
extern void reset_game_camera(void *);
extern void SetupStageManagerWithVariationId(int, int);
extern void _gameFlagSet(int);
extern void scrRun(void);
extern int bgmStandby(char *, int, int, int *);
extern int bgmChkStandbyComplete(int);
extern void bgmPlay(int, float);
extern void setScrDemoMangerFinishCallback(void (*)(void), int);
extern void sheetMgrAllReqWait(int *);
extern int getGameHardMode(void);
extern void timeAttackTimeScriptBegin(float);

static inline void setGeom(void *obj, Vec4 *pos, float ry)
{
    Vec4 p;
    Vec4 q;
    float x = pos->x;
    float z = pos->z;
    float y = pos->y;

    p.x = x;
    p.y = y;
    p.z = z;
    p.w = 1.0f;
    GetQuaternionByDegEulerYXZ(&q, 0.0f, ry, 0.0f);
    DebugSetObjectGeometry(obj, &q, &p);
}

static void func_00016450(void)
{
    char *boss = bossStatGetActiveBoss();
    void *obj = SCRGetFirstObj(gcGlobalVar.objList);
    Vec4 center;
    Vec4 pos;
    Vec4 tmp;
    int handle;
    int st;
    int bgm;

    scrInit(isysGetThisSubThread());
    PauseGame(1);
    fadeOut(0.4f, 1, 0);
    setNowLoadingMessageDisplayFlag(1);
    SetupStageManager(-1);
    backStageInit();
    ColCont2_Release(getPlayerColCont2(obj));
    tmp.x = -*(float *)(boss + 0x54);
    tmp.y = *(float *)(boss + 0x58);
    tmp.z = -*(float *)(boss + 0x5C);
    tmp.w = 1.0f;
    pos = tmp;
    YattsukeGetSeamlessAreaCenter(&center, *(unsigned char *)(boss + 0x51));
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%0)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&pos), "r"(&center) : "memory");
    setGeom(obj, &pos, -*(float *)(boss + 0x60));
    backStageGobjSave(*(int *)(GetLayoutClass(obj) + 0x1A4));
    gStatRestartPlayerChara();
    if (boss != BossStatus_EVIS) {
        gStatReloadHorseChara();
    } else {
        if (SCRGetFirstObj(gcGlobalVar.horseList))
            gStatUnloadHorseChara();
        _gameFlagSet(0x23A);
    }
    bgm = 0;
    gStatLoadPlayerAccessories();
    bossStatSekibanJumpSetHorsePos(boss);
    reset_game_camera(get_game_camera(get_main_cameraman()));
    scrRun();
    SetupStageManagerWithVariationId(1, *(unsigned char *)(boss + 0x52));
    handle = 0;
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
    scrRun();
    sheetMgrAllReqWait(&st);
    while ((unsigned int)(st - 0xDEAF) >= 2)
        scrRun();
    bgmPlay(bgm, 100.0f);
    if (gstatTimeAttackMode && !gstatKaisouMode)
        timeAttackTimeScriptBegin(getGameHardMode() ? *(float *)(boss + 0xC8) : *(float *)(boss + 0xC4));
    gameflowBootBossWait = 1;
}
