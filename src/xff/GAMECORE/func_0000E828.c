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
extern int rootPtn;
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

static void func_0000E828(void)
{
    DemoInfo *d = &activedemoInfo;

    while (1) {
        if (!d->loaded) {
            int idx = (StageEnt *)d->arg - gcGetStageData(0);
            stagemanager_loadstagecore(&rootPtn, idx, GetStageAreaNumber(), 0);
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
