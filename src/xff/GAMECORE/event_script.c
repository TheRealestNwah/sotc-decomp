extern void *isysGetThisSubThread(void);
extern void bootTexAlphaAnim(void *, void *, float, float);
extern int D_0017AF88[], D_0017AFA0[], D_0017AFB8[];
extern int (*D_0017AFD4)(int);
extern int D_0017AFD0;
extern int D_0017AFD8;
extern int D_0017AFCC;
extern char gcGlobalVar[];
extern int opflowAdvertiseDemoStat;
extern void *DldSysUndefSymbol;
extern int SH_GameObjectKITE_ADVERTISE[];
extern void PauseGame(int);
extern void ReleaseGame(void);
extern void scrRunM(int);
extern void updateSScriptSystem(int);
extern int *getSScriptWork(int);
extern int GetStageAreaNumberByPos(void *);
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern char *getEventScriptClass(int);
extern void execSCRBaseFunc(int, int);
extern void *SCRGetFirstObj(void *);
extern void updateSmallManager(void *);
extern void D_000BC4F0(void *obj, int arg);
extern void scrInit(void *);
extern void initSScriptSystem(void *);
extern void initSmallManager(void);
extern void SetScriptObjDeleteCallBackFunc(void *, void (*func)(void *obj, int arg), int);
extern void isysJumpSubThread(void *, int);
extern char *GameObject_KITE_ADVERTISE;
extern void terminateSmallManager(void);

static void func_000BC4D0(void);

void nico_snakeAllTexEnd(void)
{
    void *th = isysGetThisSubThread();

    bootTexAlphaAnim(th, D_0017AF88, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017AFA0, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017AFB8, 0.0f, -0.05f);
}

static void func_000BC250(void)
{
    int th = isysGetThisSubThread();

    for (;;) {
        if (D_0017AFD4 != 0) {
            int paused = 0;
            while (!D_0017AFD4(D_0017AFD0)) {
                if (!paused) {
                    PauseGame(1);
                    paused = 1;
                }
                scrRunM(1);
            }
            if (paused)
                ReleaseGame();
            D_0017AFD4 = 0;
            D_0017AFD0 = 0;
        }
        updateSScriptSystem(th);
        if (D_0017AFD8 != 0) {
            int area = -1;
            int *g;
            int o;

            if (getSScriptWork(th)[0] != 0)
                area = GetStageAreaNumberByPos(*(void **)(getSScriptWork(th)[1] + 0x134));
            o = 0;
            for (g = isysGroupForFirst(gcGlobalVar + 0x2FC, 0); g != 0; g = isysGroupForNext(g, 0)) {
                char *ec;
                o = *g;
                ec = getEventScriptClass(o);
                if (area == *(int *)(ec + 0x74)) {
                    D_0017AFCC = o;
                    execSCRBaseFunc(th, *(int *)(ec + 0x70));
                    D_0017AFCC = 0;
                }
            }
            if (o != 0)
                isysGroupForExit(o, 0);
        }
        switch (opflowAdvertiseDemoStat) {
        case 2:
            if (DldSysUndefSymbol != SH_GameObjectKITE_ADVERTISE)
                func_000BC4D0();
            break;
        case 1:
            updateSmallManager(SCRGetFirstObj(gcGlobalVar + 0x2B4));
            break;
        default:
            updateSmallManager((void *)getSScriptWork(th)[0]);
            break;
        }
        scrRunM(1);
    }
}

void nico_soundScriptStart(void)
{
    void *t = isysGetThisSubThread();
    scrInit(t);
    initSScriptSystem(t);
    initSmallManager();
    SetScriptObjDeleteCallBackFunc(t, D_000BC4F0, 0);
    scrRunM(1);
    D_0017AFD0 = 0;
    D_0017AFD4 = 0;
    isysJumpSubThread(func_000BC250, 0);
}

int getNowExecEventScriptObj(void)
{
    return D_0017AFCC;
}

void setLoadingCheckFunc(int arg0, int arg1)
{
    (*(int *)&D_0017AFD4) = arg0;
    D_0017AFD0 = arg1;
}

void setEventScriptEnable(int arg0)
{
    D_0017AFD8 = arg0;
}

static void func_000BC4D0(void)
{
    ((void (*)(int))updateSmallManager)(*(int *)(GameObject_KITE_ADVERTISE + 8));
}

static void T_000BC4F0(void)
{
    terminateSmallManager();
}
