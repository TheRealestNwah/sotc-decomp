extern char *GameObject_BIRD_B_DEMO;
extern char *GameObject_GIRL_B;
extern char *GameObject_OP1_LEAF;
extern char *GameObject_DEMO_OP1_STARTER;
extern char gcGlobalVar[];
extern int D_0017AD48;
extern int SetCharacterObjDemoMotionMode(void *, int, int, float);
extern char *GetScriptCharacterClass(void *);
extern void *SCRGetFirstObj(void *);
extern void isysRequestDeleteObj(void *);
extern void FinishDemoCameraOrient(void *);
extern void demoManEnd(void *);
extern void ReleaseGame(int);

static void func_00070E48(void *unused, void **demo)
{
    SetCharacterObjDemoMotionMode(*(void **)(GameObject_BIRD_B_DEMO + 8), 0, 0, 0.0f);
    *(int *)(GetScriptCharacterClass(*(void **)(GameObject_BIRD_B_DEMO + 8)) + 0x1204) = 0;
    SetCharacterObjDemoMotionMode(*(void **)(GameObject_GIRL_B + 8), 0, 0, 0.0f);
    *(int *)(GetScriptCharacterClass(*(void **)(GameObject_GIRL_B + 8)) + 0x1204) = 0;
    SetCharacterObjDemoMotionMode(*(void **)(GameObject_OP1_LEAF + 8), 0, 0, 0.0f);
    *(int *)(GetScriptCharacterClass(*(void **)(GameObject_OP1_LEAF + 8)) + 0x1204) = 0;
    if (D_0017AD48 != 0) {
        SetCharacterObjDemoMotionMode(SCRGetFirstObj(gcGlobalVar + 0x2B0), 0, 0, 10.0f);
        *(int *)(GetScriptCharacterClass(SCRGetFirstObj(gcGlobalVar + 0x2B0)) + 0x1204) = 0;
        SetCharacterObjDemoMotionMode(SCRGetFirstObj(gcGlobalVar + 0x2B4), 0, 0, 10.0f);
        *(int *)(GetScriptCharacterClass(SCRGetFirstObj(gcGlobalVar + 0x2B4)) + 0x1204) = 0;
    }
    isysRequestDeleteObj(demo[1]);
    FinishDemoCameraOrient(demo[0]);
    demoManEnd(*(void **)(GameObject_DEMO_OP1_STARTER + 8));
    ReleaseGame(1);
}
