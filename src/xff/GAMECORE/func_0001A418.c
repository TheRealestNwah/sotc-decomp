/* Stage-core load/unload cutscene helper: loads the stage core, ramps BGM volume, waits for standby, stops BGM, optionally runs the memory card save script (SavePoint_SAVE_F4) and waits 2 seconds, then restarts BGM and fades in until jumphokoraFlag bit 1 is set. */
typedef struct { char pad[0x168]; float time; char pad2[0x40]; int flag; } GcGlobal;
extern GcGlobal gcGlobalVar;
extern unsigned int jumphokoraFlag[2];
extern int B_001885C0;
extern int B_001885C4;
extern char rootPtn[];
extern int SavePoint_SAVE_F4;
extern void gameflowSheetMgrAllReqWait(void);
extern void *memset(void *, int, unsigned int);
extern void stagemanager_loadstagecore(void *, int, int, int);
extern void bgmChangeVol(int, float, float);
extern int bgmStandby(int, int, int, int);
extern void scrRun(void);
extern void initPauseMenuMap(void);
extern void bgmStop(int, float, int *);
extern int bgmStopChk(int);
extern void bootMemoryCardSaveScript(int);
extern void bgmPlay(int, float);
extern void fadeIn(int, int, float);
extern void bgmEnvTickProckMask(int);
extern void stagemanager_unloadstagecore(int);

static void func_0001A418(int stage, int bgm, int standby, int a3, int cont, int save)
{
    int handle = 0;
    int h;
    float t0;

    gcGlobalVar.flag = 1;
    gameflowSheetMgrAllReqWait();
    memset(jumphokoraFlag, 0, 8);
    B_001885C0 = stage;
    B_001885C4 = cont;
    stagemanager_loadstagecore(rootPtn, stage, a3, 0);
    if (bgm != 0)
        bgmChangeVol(bgm, 50.0f, 2.0f);
    gameflowSheetMgrAllReqWait();
    if (standby != 0) {
        while ((handle = bgmStandby(standby, 0, 0, 0)) == 0)
            scrRun();
    }
    initPauseMenuMap();
    if (bgm != 0) {
        bgmStop(bgm, 0.5f, &h);
        while (bgmStopChk(h) == 0)
            scrRun();
    }
    if (save != 0) {
        bootMemoryCardSaveScript(SavePoint_SAVE_F4);
        t0 = gcGlobalVar.time;
        while (gcGlobalVar.time - t0 < 2.0f)
            scrRun();
    }
    gameflowSheetMgrAllReqWait();
    if (handle != 0)
        bgmPlay(handle, 100.0f);
    gcGlobalVar.flag = 0;
    jumphokoraFlag[0] |= 1;
    fadeIn(0, 0, 3.0f);
    while (((jumphokoraFlag[0] >> 1) & 1) == 0)
        scrRun();
    if (handle != 0)
        bgmStop(handle, 10.0f, 0);
    if (cont == 0)
        bgmEnvTickProckMask(0);
    stagemanager_unloadstagecore(stage);
}

