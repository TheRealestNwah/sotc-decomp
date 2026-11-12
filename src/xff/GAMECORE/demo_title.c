extern char rootPtn[], gcGlobalVar[], padManagerData[];
extern char *GameObject_DEMO_TITLE_STARTER;
extern int titleDemoFinishFlag, B_0019CF44;
extern char SDemoStationedMotOriData_TITLEDEMO_CAM[], SDemoStationedMotOriData_TITLEDEMO_PLA[];
extern char SDemoStationedMotOriData_TITLEDEMO_HOR[], SDemoStationedMotOriData_TITLEDEMO_LWS[];
extern int ScriptSpriteMenuObjDef_SPRITE_TITLE;
extern void *DldSysUndefSymbol;
extern int isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptLayoutClass(int);
extern void SetScriptLayoutObjLetterProcMode(int, int);
extern char *_SCRMallocAlign(char *, int, int);
extern void demoManBootRequest(int);
extern int demoManBootChk(int);
extern void scrRun(void);
extern int opflowChkTitleDemoStart(void);
extern void fadeIn(int, int, float);
extern int get_main_cameraman_camera_obj(void);
extern char *GetLayoutClass(int);
extern int PlayDemoCameraOrient(int, void *, void *, int, int, float);
extern int get_main_cameraman(void);
extern int get_game_camera(int);
extern void begin_stream_lws_movie_playing_game_camera(int);
extern char *SCRGetFirstObj(void *);
extern char *GetScriptCharacterClass(int);
extern void SetCharacterObjDemoMotionMode(int, void *, void *, float);
extern void isysAddGroupWithLinkParam(int, int, int, int);
extern int _SCRStartLwsDemoOrient(int, void *, void *, int);
extern void demoManStart(int, int);
extern void SetScriptObjDeleteCallBackFunc(int, void *, int);
extern void _SCRStartSpriteMenuAnim(int, int, int, int, int *, int);
extern int opflowChkAbort(void);
extern int CheckDemoCameraOrientFinished(int);
extern void func_000C9078(int, int);

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        return *(char **)(module + 0x10) + index * *(int *)(*(char **)(module + 8) + 0xC);
    }
    return 0;
}

#ifdef NONMATCHING /* 223 diffs, 244 vs 260 words: dld-resolve branch forms, loop layout and register assignment */
void demo_title(void)
{
    int flag;
    int s2 = *(int *)(GameObject_DEMO_TITLE_STARTER + 8);
    int s4 = isysGetThisSubThread();
    char *s0, *s1, *lay;
    int *s5;
    float t, f21;
    int cam, p, q;

    iosCreatePartition(rootPtn, 0x3B);
    s0 = GetScriptLayoutClass(s4);
    *(char **)(GetScriptLayoutClass(s4) + 0x2D4) = s0;
    SetScriptLayoutObjLetterProcMode(s4, 1);
    s1 = GetScriptLayoutClass(s4);
    s5 = (int *)_SCRMallocAlign(s0, 8, 0x10);
    *(int **)(s1 + 0x2D8) = s5;
    titleDemoFinishFlag = 0;
    demoManBootRequest(s2);
    do {
        scrRun();
    } while (demoManBootChk(s2) != 1);
    do {
        scrRun();
    } while (!opflowChkTitleDemoStart());
    if (*(int *)(gcGlobalVar + 0x1AC)) {
        do {
            scrRun();
        } while (*(int *)(gcGlobalVar + 0x1AC));
    }
    fadeIn(0, 0, 1.0f);
    cam = get_main_cameraman_camera_obj();
    lay = GetLayoutClass(s4);
    t = *(float *)(resourceData((unsigned int *)*(int *)(GetScriptLayoutClass(*(int *)(GameObject_DEMO_TITLE_STARTER + 8)) + 0x2DC)) + 0x10);
    s5[0] = PlayDemoCameraOrient(cam, SDemoStationedMotOriData_TITLEDEMO_CAM + 4, *(void **)(lay + 0x134), s4, *(int *)(GameObject_DEMO_TITLE_STARTER + 8), t);
    get_game_camera(get_main_cameraman());
    begin_stream_lws_movie_playing_game_camera(0);
    s0 = SCRGetFirstObj(gcGlobalVar + 0x2B0);
    *(int *)(GetScriptCharacterClass((int)s0) + 0x1204) = 1;
    SetCharacterObjDemoMotionMode((int)s0, SDemoStationedMotOriData_TITLEDEMO_PLA + 4, *(void **)(GetLayoutClass(s4) + 0x134), 0.0f);
    isysAddGroupWithLinkParam((int)s0, s5[0], 0, 0);
    s0 = SCRGetFirstObj(gcGlobalVar + 0x2B4);
    *(int *)(GetScriptCharacterClass((int)s0) + 0x1204) = 1;
    SetCharacterObjDemoMotionMode((int)s0, SDemoStationedMotOriData_TITLEDEMO_HOR + 4, *(void **)(GetLayoutClass(s4) + 0x134), 0.0f);
    isysAddGroupWithLinkParam((int)s0, s5[0], 0, 0);
    s5[1] = _SCRStartLwsDemoOrient(s5[0], SDemoStationedMotOriData_TITLEDEMO_LWS + 4, *(void **)(GetLayoutClass(s4) + 0x134), s4);
    demoManStart(*(int *)(GameObject_DEMO_TITLE_STARTER + 8), s5[0]);
    SetScriptObjDeleteCallBackFunc(s4, (void *)func_000C9078, (int)s5);
    p = 1;
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_TITLE, s4, 0, 0, &p, 0);
    B_0019CF44 = 0;
    f21 = 0.0f;
    while (p) {
        if (*(int *)padManagerData & 0x5040)
            f21 = 30.0f;
        if (0.0f < f21)
            f21 -= *(float *)(gcGlobalVar + 0x180);
        B_0019CF44 = opflowChkAbort();
        if (B_0019CF44)
            break;
        if (CheckDemoCameraOrientFinished(s5[0]) && f21 <= 0.0f)
            break;
        scrRun();
    }
    func_000C9078(s4, (int)s5);
    p = 0;
    SetScriptObjDeleteCallBackFunc(s4, 0, 0);
}
#endif
