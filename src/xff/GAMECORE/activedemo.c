typedef struct { int a; int b; char finder[0x14]; int c; } VuColiDisp;
extern VuColiDisp B_00183B30;
extern char rootPtn[];
extern void InitCollisionFinder(void *, void *, int);
typedef struct {
    unsigned int f0 : 2;
    unsigned int end : 1;
    unsigned int loaded : 1;
    int b;
    char *arg;
    void *obj;
} DemoInfo;
typedef struct { int w[5]; } StageEnt;
extern DemoInfo activedemoInfo;
extern int B_00183B50;
extern int AdpcmSeq_F8_HORSE_DOWN;
extern StageEnt *gcGetStageData(int);
extern int GetStageAreaNumber(void);
extern void stagemanager_loadstagecore(void *, int, int, int);
extern void stagemanager_unloadstagecore(int);
extern int bgmStandby(int, int, int, int);
extern void bgmStop(int, int, float);
extern void active_demo_end(void);
extern void scrRun(void);
extern void memset(void *, int, unsigned int);
typedef struct {
    unsigned int active : 1;
    unsigned int end : 1;
    unsigned int pad2 : 1;
    unsigned int ready : 1;
    int b;
    int arg;
    void *obj;
} DemoInfo_st_activedemoflow;
extern void *isysGetThisSubThread(void);
extern void scrInit(void *);
extern void gameModeSet(int);
extern void gameModeCls(int);
extern void PauseCamFinalizer(int);
extern void setDefaultFsEffect(void);
extern void *get_main_cameraman(void);
extern void *get_game_camera(void *);
extern void end_stream_lws_movie_playing_game_camera(void *);
typedef struct Ptn Ptn;
extern void *createScriptObj(void *, void *, Ptn *, int, int, int, int, int);
extern int ScrIntrDef_START_ACTIVE_DEMO;
extern void bgmPlay(int, float);
extern void scriptIntrSignal(int);

void activeDemoCancel(int id);

void initVuColiDispWork(int a)
{
    B_00183B30.a = a;
    B_00183B30.b = 2;
    B_00183B30.c = 0;
    InitCollisionFinder(B_00183B30.finder, rootPtn, 0x400);
}

static void func_0000E828(void)
{
    DemoInfo *d = &activedemoInfo;

    while (1) {
        if (!d->loaded) {
            int idx = (StageEnt *)d->arg - gcGetStageData(0);
            stagemanager_loadstagecore(&(*(int *)&rootPtn), idx, GetStageAreaNumber(), 0);
            while ((B_00183B50 = bgmStandby(AdpcmSeq_F8_HORSE_DOWN, 0, 0, 0)) == 0)
                scrRun();
            d->loaded = 1;
        } else if (d->end) {
            int idx = (StageEnt *)d->arg - gcGetStageData(0);
            d->loaded = 0;
            bgmStop(B_00183B50, 0, 3.0f);
            active_demo_end();
            stagemanager_unloadstagecore(idx);
            break;
        } else {
            scrRun();
        }
    }
    memset(d, 0, 0x10);
}

void activedemoflowDemoEnd(void)
{
    (*(int *)&activedemoInfo) |= 2;
}

int getActivedemoStage(void)
{
    return (*(int *)((char *)(((unsigned char *)&activedemoInfo)) + 8));
}

int chkActiveDemoStart(void)
{
    return (*(int *)&activedemoInfo) & 1;
}

void st_activedemoflow(void)
{
    scrInit(isysGetThisSubThread());
    gameModeSet(1);
    PauseCamFinalizer(1);
    while (!(*(DemoInfo_st_activedemoflow *)&activedemoInfo).ready)
        scrRun();
    (*(DemoInfo_st_activedemoflow *)&activedemoInfo).active = 1;
    while (!(*(DemoInfo_st_activedemoflow *)&activedemoInfo).end)
        scrRun();
    ((void (*)(int))activeDemoCancel)((*(DemoInfo_st_activedemoflow *)&activedemoInfo).arg);
    setDefaultFsEffect();
    end_stream_lws_movie_playing_game_camera(get_game_camera(get_main_cameraman()));
    PauseCamFinalizer(0);
    gameModeCls(1);
}

void activeDemoAbort(void)
{
    if (activedemoInfo.obj != 0)
        ((void (*)(int))activeDemoCancel)((int)activedemoInfo.arg);
}

void activeDemoStandby(void *a)
{
    if (activedemoInfo.obj == 0) {
        activedemoInfo.arg = a;
        activedemoInfo.obj = createScriptObj(func_0000E828, 0, (Ptn *)&rootPtn, 0x1000, 0, 1, 0, 0);
    }
}

void activeDemoCancel(int id)
{
    int *d = ((int *)&activedemoInfo);

    if (d[3] != 0 && d[2] == id) {
        d[0] |= 4;
    }
}

void activeDemoStart(int arg)
{
    bgmPlay(B_00183B50, 100.0f);
    if (activedemoInfo.obj == 0) {
        activedemoInfo.arg = (char *)arg;
        activedemoInfo.obj = (void *)createScriptObj(func_0000E828, 0, &(*(int *)&rootPtn), 0x1000, 0, 1, 0, 0);
    }
    scriptIntrSignal(ScrIntrDef_START_ACTIVE_DEMO);
}
