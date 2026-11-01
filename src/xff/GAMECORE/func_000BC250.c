extern int (*D_0017AFD4)(int);
extern int D_0017AFD0;
extern int D_0017AFD8;
extern int D_0017AFCC;
extern char gcGlobalVar[];
extern int opflowAdvertiseDemoStat;
extern void *DldSysUndefSymbol;
extern int SH_GameObjectKITE_ADVERTISE[];
extern int isysGetThisSubThread(void);
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
extern void func_000BC4D0(void);
extern void *SCRGetFirstObj(void *);
extern void updateSmallManager(void *);

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
