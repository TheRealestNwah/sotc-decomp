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

/* Parked attempt: 13 words differ from the Original. Left: the GameObject_* lui/lw use $v1/$v0 swapped for the bird/girl/leaf blocks, and fadeIn's a0 = 0 is scheduled before the 1.0f load instead of in the delay slot. */
#ifdef NONMATCHING
extern int DldSysUndefSymbol;
extern int SDemoStationedMotOriData_OPDEMO1_BIRD_B;
extern int SDemoStationedMotOriData_OPDEMO1_CAMERA;
extern int SDemoStationedMotOriData_OPDEMO1_GIRL_B;
extern int SDemoStationedMotOriData_OPDEMO1_HORSE;
extern int SDemoStationedMotOriData_OPDEMO1_LEAF;
extern int SDemoStationedMotOriData_OPDEMO1_LWS;
extern int SDemoStationedMotOriData_OPDEMO1_PLAYER;
extern int opflowOpCancel;
extern int opflowOpDeleteReq;
extern char rootPtn[];
extern int CheckDemoCameraOrientFinished(void *);
extern char *GetLayoutClass(void *);
extern char *GetScriptLayoutClass(void *);
extern void PauseGame(int);
extern void *PlayDemoCameraOrient(void *, int, int, void *, void *, float);
extern void SetScriptLayoutObjLetterProcMode(void *, int);
extern void SetScriptObjDeleteCallBackFunc(void *, void *, void *);
extern void *_SCRMallocAlign(void *, int, int);
extern void *_SCRStartLwsDemoOrient(void *, int, int, void *);
extern void begin_stream_lws_movie_playing_game_camera(void *);
extern int demoManBootChk(void *);
extern void demoManBootRequest(void *);
extern int demoManChkLoadFinish(void *);
extern int demoManChkStart(void *);
extern void demoManSkip(void *, void *);
extern void demoManStart(void *, void *);
extern int demoscrCheckDemoCutSkip(void);
extern int demoscrCheckDemoFinish(void);
extern void fadeIn(int, int, float);
extern void fadeOut(int, int, float);
extern void *get_game_camera(void *);
extern void *get_main_cameraman(void);
extern void *get_main_cameraman_camera_obj(void);
extern void *iosCreatePartition(void *, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern void *isysGetThisSubThread(void);
extern void opflowOp1End(void);
extern void opflowSetDemoFrame(float);
extern void scrRun(void);
extern void setNowLoadingMessageDisplayFlag(int);

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;

    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != (char *)DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        return *(char **)(module + 0x10) + index * *(int *)(*(char **)(module + 8) + 0xC);
    }
    return 0;
}

void demo_op1(void)
{
    void *obj = *(void **)(GameObject_DEMO_OP1_STARTER + 8);
    void *th = isysGetThisSubThread();
    void *part = iosCreatePartition(rootPtn, 0x3B);
    char *lc;
    void **m;
    void *cam;
    char *lay;
    float f;
    char *g;
    void *o;

    *(void **)(GetScriptLayoutClass(th) + 0x2D4) = part;
    SetScriptLayoutObjLetterProcMode(th, 1);
    lc = GetScriptLayoutClass(th);
    m = _SCRMallocAlign(part, 8, 0x10);
    *(void ***)(lc + 0x2D8) = m;
    demoManBootRequest(obj);
    while (demoManBootChk(obj) != 1)
        scrRun();
    while (((volatile struct { char pad[0x1AC]; int x; } *)gcGlobalVar)->x != 0)
        scrRun();
    opflowSetDemoFrame(0.0f);
    cam = get_main_cameraman_camera_obj();
    lay = GetLayoutClass(th);
    if (*(unsigned int **)(GetScriptLayoutClass(*(void **)(GameObject_DEMO_OP1_STARTER + 8)) + 0x2DC) != 0)
        f = *(float *)(resourceData(*(unsigned int **)(GetScriptLayoutClass(*(void **)(GameObject_DEMO_OP1_STARTER + 8)) + 0x2DC)) + 0x10);
    else
        f = 1.0f;
    g = gcGlobalVar + 0x2B0;
    m[0] = PlayDemoCameraOrient(cam, SDemoStationedMotOriData_OPDEMO1_CAMERA + 4, *(int *)(lay + 0x134), th, *(void **)(GameObject_DEMO_OP1_STARTER + 8), f);
    begin_stream_lws_movie_playing_game_camera(get_game_camera(get_main_cameraman()));
    { void *t = SCRGetFirstObj(g); o = t; }
    *(int *)(GetScriptCharacterClass(o) + 0x1204) = 1;
    SetCharacterObjDemoMotionMode(o, SDemoStationedMotOriData_OPDEMO1_PLAYER + 4, *(int *)(GetLayoutClass(th) + 0x134), 0.0f);
    isysAddGroupWithLinkParam(o, m[0], 0, 0);
    o = SCRGetFirstObj(g + 4);
    *(int *)(GetScriptCharacterClass(o) + 0x1204) = 1;
    SetCharacterObjDemoMotionMode(o, SDemoStationedMotOriData_OPDEMO1_HORSE + 4, *(int *)(GetLayoutClass(th) + 0x134), 0.0f);
    isysAddGroupWithLinkParam(o, m[0], 0, 0);
    o = *(void **)(GameObject_BIRD_B_DEMO + 8);
    *(int *)(GetScriptCharacterClass(o) + 0x1204) = 1;
    SetCharacterObjDemoMotionMode(o, SDemoStationedMotOriData_OPDEMO1_BIRD_B + 4, *(int *)(GetLayoutClass(th) + 0x134), 0.0f);
    isysAddGroupWithLinkParam(o, m[0], 0, 0);
    o = *(void **)(GameObject_GIRL_B + 8);
    *(int *)(GetScriptCharacterClass(o) + 0x1204) = 1;
    SetCharacterObjDemoMotionMode(o, SDemoStationedMotOriData_OPDEMO1_GIRL_B + 4, *(int *)(GetLayoutClass(th) + 0x134), 0.0f);
    isysAddGroupWithLinkParam(o, m[0], 0, 0);
    o = *(void **)(GameObject_OP1_LEAF + 8);
    *(int *)(GetScriptCharacterClass(o) + 0x1204) = 1;
    SetCharacterObjDemoMotionMode(o, SDemoStationedMotOriData_OPDEMO1_LEAF + 4, *(int *)(GetLayoutClass(th) + 0x134), 0.0f);
    isysAddGroupWithLinkParam(o, m[0], 0, 0);
    m[1] = _SCRStartLwsDemoOrient(m[0], SDemoStationedMotOriData_OPDEMO1_LWS + 4, *(int *)(GetLayoutClass(th) + 0x134), th);
    demoManStart(*(void **)(GameObject_DEMO_OP1_STARTER + 8), m[0]);
    while (demoManChkStart(*(void **)(GameObject_DEMO_OP1_STARTER + 8)) != 0)
        scrRun();
    setNowLoadingMessageDisplayFlag(0);
    fadeIn(0, 0, 1.0f);
    SetScriptObjDeleteCallBackFunc(th, 0, m);
    while (!CheckDemoCameraOrientFinished(m[0]) && !(D_0017AD48 = demoscrCheckDemoFinish())) {
        opflowSetDemoFrame(*(float *)((char *)m[0] + 0x3C));
        if (demoscrCheckDemoCutSkip() && demoManChkLoadFinish(*(void **)(GameObject_DEMO_OP1_STARTER + 8)))
            demoManSkip(*(void **)(GameObject_DEMO_OP1_STARTER + 8), m[0]);
        scrRun();
    }
    if (D_0017AD48) {
        opflowOpCancel = 1;
        PauseGame(1);
        fadeOut(1, 0, 0.4f);
        func_00070E48(th, m);
    }
    opflowOp1End();
    while (!opflowOpDeleteReq)
        scrRun();
    if (!D_0017AD48)
        func_00070E48(th, m);
}
#endif
