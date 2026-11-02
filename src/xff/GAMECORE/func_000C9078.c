extern char gcGlobalVar[];
extern int titleDemoFinishFlag;
extern char *GameObject_DEMO_TITLE_STARTER;
extern int opflowChkLoadStart(void);
extern void fadeOut(int, float, int);
extern void setNowLoadingMessageDisplayFlag(int);
extern void *SCRGetFirstObj(void *);
extern void SetCharacterObjDemoMotionMode(void *, int, float, int);
extern char *GetScriptCharacterClass(void *);
extern void isysRequestDeleteObj(void *);
extern void FinishDemoCameraOrient(void *);
extern void demoManEnd(void *);
extern void opflowTitleDmoeEnd(void);

static void func_000C9078(void *o, int *work)
{
    int r = opflowChkLoadStart();
    char *p;

    titleDemoFinishFlag = 1;
    if (r == 1) {
        fadeOut(1, 0.39999998f, 0);
        setNowLoadingMessageDisplayFlag(1);
    } else if (r != 2) {
        fadeOut(1, 0.39999998f, 0);
    }
    p = gcGlobalVar + 0x2B0;
    SetCharacterObjDemoMotionMode(SCRGetFirstObj(p), 0, 10.0f, 0);
    *(int *)(GetScriptCharacterClass(SCRGetFirstObj(p)) + 0x1204) = 0;
    SetCharacterObjDemoMotionMode(SCRGetFirstObj(p + 4), 0, 10.0f, 0);
    *(int *)(GetScriptCharacterClass(SCRGetFirstObj(p + 4)) + 0x1204) = 0;
    isysRequestDeleteObj((void *)work[1]);
    FinishDemoCameraOrient((void *)work[0]);
    demoManEnd(*(void **)(GameObject_DEMO_TITLE_STARTER + 8));
    opflowTitleDmoeEnd();
}
