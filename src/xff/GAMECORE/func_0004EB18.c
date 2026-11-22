extern void FinishDemoCameraOrient(int);
extern char *GetScriptCharacterClass(int);
extern void PauseGame(int);
extern void ReleaseGame(int);
extern int SetCharacterObjDemoMotionMode(int, int, int, float);
extern void demoManEnd(int);
extern void end_stream_lws_movie_playing_game_camera(int);
extern void endingflowDemoEnd(void);
extern void endingflowEndAdpcmSeq(int);
extern void fadeOut(float, int, int);
extern void setNowLoadingMessageDisplayFlag(int);
extern int get_game_camera(int);
extern int get_main_cameraman(void);
extern void isysRequestDeleteObj(int);
extern int *GameObject_DEMO_END_STARTER;
extern int *GameObject_DORMIN_MORPH;
extern int *GameObject_GIRL_END;
extern int *GameObject_GUARD_A;
extern int *GameObject_GUARD_B;
extern int *GameObject_GUARD_C;
extern int *GameObject_GUARD_D;
extern int *GameObject_GUARD_E;
extern int *GameObject_HORSE_B;
extern int *GameObject_HORSE_C;
extern int *GameObject_HORSE_D;
extern int *GameObject_HORSE_E;
extern int *GameObject_HORSE_F;
extern int *GameObject_HORSE_G;
extern int *GameObject_PLAYER_A_DEMO;
extern int *GameObject_PLAYER_A_DEMO_BLACK;
extern int *GameObject_SHARMAN;
extern int *GameObject_SMOKE_MAN;
extern int *GameObject_SMOKE_MAN_B;
extern int *GameObject_SMOKE_MAN_C;
extern int *GameObject_SMOKE_MAN_D;
extern int *GameObject_SMOKE_MAN_E;

#define STOP(o, f) \
    SetCharacterObjDemoMotionMode((o)[2], 0, 0, f); \
    *(int *)(GetScriptCharacterClass((o)[2]) + 0x1204) = 0

static void func_0004EB18(int unused, int *a)
{
    endingflowEndAdpcmSeq(a[3]);
    PauseGame(1);
    fadeOut(0.4f, 1, 0);
    setNowLoadingMessageDisplayFlag(1);
    ReleaseGame(1);
    STOP(GameObject_GIRL_END, 0);
    STOP(GameObject_DORMIN_MORPH, 0);
    STOP(GameObject_SMOKE_MAN, 0);
    STOP(GameObject_SMOKE_MAN_B, 0);
    STOP(GameObject_SMOKE_MAN_C, 0);
    STOP(GameObject_SMOKE_MAN_D, 0);
    STOP(GameObject_SMOKE_MAN_E, 0);
    STOP(GameObject_SHARMAN, 0);
    STOP(GameObject_GUARD_A, 0);
    STOP(GameObject_GUARD_B, 0);
    STOP(GameObject_GUARD_C, 0);
    STOP(GameObject_GUARD_D, 0);
    STOP(GameObject_GUARD_E, 0);
    STOP(GameObject_HORSE_B, 0);
    STOP(GameObject_HORSE_C, 0);
    STOP(GameObject_HORSE_D, 0);
    STOP(GameObject_HORSE_E, 0);
    STOP(GameObject_HORSE_F, 0);
    STOP(GameObject_HORSE_G, 0);
    STOP(GameObject_PLAYER_A_DEMO, 10.0f);
    STOP(GameObject_PLAYER_A_DEMO_BLACK, 10.0f);
    isysRequestDeleteObj(a[1]);
    FinishDemoCameraOrient(a[0]);
    end_stream_lws_movie_playing_game_camera(get_game_camera(get_main_cameraman()));
    demoManEnd(GameObject_DEMO_END_STARTER[2]);
    endingflowDemoEnd();
}
typedef struct { int frame; int vol; int seq; } SeqEnt;
extern int DldSysUndefSymbol;
extern char rootPtn[];
extern int isysGetThisSubThread(void);
extern void *iosCreatePartition(void *, int);
extern char *GetScriptLayoutClass(int);
extern char *GetLayoutClass(int);
extern void SetScriptLayoutObjLetterProcMode(int, int);
extern int *_SCRMallocAlign(void *, int, int);
extern void endingflowStartAdpcmSeq(SeqEnt *);
extern void endingflowTickAdpcmSeq(int);
extern void demoManBootRequest(int);
extern int demoManBootChk(int);
extern void scrRun(void);
extern int get_main_cameraman_camera_obj(void);
extern void begin_stream_lws_movie_playing_game_camera(int);
extern int PlayDemoCameraOrient(int, char *, int, int, int, float);
extern void isysAddGroupWithLinkParam(int, int, int, int);
extern int _SCRStartLwsDemoOrient(int, char *, int, int);
extern void demoManStart(int, int);
extern void SetScriptObjDeleteCallBackFunc(int, void *, void *);
extern int CheckDemoCameraOrientFinished(int);
extern int demoscrCheckDemoFinish(void);
extern int demoscrCheckDemoCutSkip(void);
extern int demoManChkLoadFinish(int);
extern void demoManSkip(int, int);

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

#define SETUP(o, d)                                                                        \
    *(int *)(GetScriptCharacterClass(o) + 0x1204) = 1;                                                 \
    SetCharacterObjDemoMotionMode(o, (int)((d) + 4), *(int *)(GetLayoutClass(th) + 0x134), 0.0f); \
    isysAddGroupWithLinkParam(o, m[0], 0, 0)

#define SETUPG(g, d)            \
    {                           \
        int *gg = (g);         \
        int o;                  \
        __asm__("" : "+r"(gg)); \
        o = gg[2];            \
        SETUP(o, d);            \
    }

extern int AdpcmSeq_DEMO_ED1_C0, AdpcmSeq_DEMO_ED1_C12, AdpcmSeq_DEMO_ED2_C17;
extern char gcGlobalVar[];
extern char *SDemoStationedMotOriData_ENDDEMO_CAMERA, *SDemoStationedMotOriData_ENDDEMO_PLAYER,
    *SDemoStationedMotOriData_ENDDEMO_PLAYER_BLACK, *SDemoStationedMotOriData_ENDDEMO_GIRL,
    *SDemoStationedMotOriData_ENDDEMO_DORMIN, *SDemoStationedMotOriData_ENDDEMO_SMOKE_MAN_A,
    *SDemoStationedMotOriData_ENDDEMO_SMOKE_MAN_B, *SDemoStationedMotOriData_ENDDEMO_SMOKE_MAN_C,
    *SDemoStationedMotOriData_ENDDEMO_SMOKE_MAN_D, *SDemoStationedMotOriData_ENDDEMO_SMOKE_MAN_E,
    *SDemoStationedMotOriData_ENDDEMO_SHARMAN, *SDemoStationedMotOriData_ENDDEMO_GUARD_A,
    *SDemoStationedMotOriData_ENDDEMO_GUARD_B, *SDemoStationedMotOriData_ENDDEMO_GUARD_C,
    *SDemoStationedMotOriData_ENDDEMO_GUARD_D, *SDemoStationedMotOriData_ENDDEMO_GUARD_E,
    *SDemoStationedMotOriData_ENDDEMO_HORSE_B, *SDemoStationedMotOriData_ENDDEMO_HORSE_C,
    *SDemoStationedMotOriData_ENDDEMO_HORSE_D, *SDemoStationedMotOriData_ENDDEMO_HORSE_E,
    *SDemoStationedMotOriData_ENDDEMO_HORSE_F, *SDemoStationedMotOriData_ENDDEMO_HORSE_G,
    *SDemoStationedMotOriData_ENDDEMO_LWS;

#define SG(n, d) { int o = GameObject_##n[2]; SETUP(o, SDemoStationedMotOriData_ENDDEMO_##d); }
#define SGG(n, d) SETUPG(GameObject_##n, SDemoStationedMotOriData_ENDDEMO_##d)

void demo_end(void)
{
    SeqEnt seq[4] = { { 0, 12, AdpcmSeq_DEMO_ED1_C0 }, { 12, 0x2C, AdpcmSeq_DEMO_ED1_C12 },
                      { 0x2C, 99999, AdpcmSeq_DEMO_ED2_C17 }, { 0, 0x3E7, 0 } };
    int starter = GameObject_DEMO_END_STARTER[2];
    int th = isysGetThisSubThread();
    void *part = iosCreatePartition(rootPtn, 0x43);
    char *lc;
    int *m;
    int cam;
    char *lay;
    float f;
    int o;

    *(void **)(GetScriptLayoutClass(th) + 0x2D4) = part;
    SetScriptLayoutObjLetterProcMode(th, 1);
    lc = GetScriptLayoutClass(th);
    m = _SCRMallocAlign(part, 0x10, 0x10);
    *(int **)(lc + 0x2D8) = m;
    m[3] = 0;
    endingflowStartAdpcmSeq(seq);
    demoManBootRequest(starter);
    while (demoManBootChk(starter) != 1)
        scrRun();
    {
        register char *g __asm__("$2") = gcGlobalVar;
        __asm__("" : "+r"(g));
        if (*(int *)(g + 0x1AC)) {
            char *h;
            __asm__("" : "=r"(h) : "0"(g));
            do
                scrRun();
            while (*(int *)(h + 0x1AC));
        }
    }
    cam = get_main_cameraman_camera_obj();
    lay = GetLayoutClass(th);
    if (*(unsigned int **)(GetScriptLayoutClass(GameObject_DEMO_END_STARTER[2]) + 0x2DC) != 0)
        f = *(float *)(resourceData(*(unsigned int **)(GetScriptLayoutClass(GameObject_DEMO_END_STARTER[2]) + 0x2DC)) + 0x10);
    else
        f = 1.0f;
    m[0] = PlayDemoCameraOrient(cam, SDemoStationedMotOriData_ENDDEMO_CAMERA + 4, *(int *)(lay + 0x134), th,
                                GameObject_DEMO_END_STARTER[2], f);
    begin_stream_lws_movie_playing_game_camera(get_game_camera(get_main_cameraman()));
    SG(PLAYER_A_DEMO, PLAYER);
    SGG(PLAYER_A_DEMO_BLACK, PLAYER_BLACK);
    SGG(GIRL_END, GIRL);
    SGG(DORMIN_MORPH, DORMIN);
    SGG(SMOKE_MAN, SMOKE_MAN_A);
    SGG(SMOKE_MAN_B, SMOKE_MAN_B);
    SGG(SMOKE_MAN_C, SMOKE_MAN_C);
    SGG(SMOKE_MAN_D, SMOKE_MAN_D);
    SGG(SMOKE_MAN_E, SMOKE_MAN_E);
    SGG(SHARMAN, SHARMAN);
    SGG(GUARD_A, GUARD_A);
    SGG(GUARD_B, GUARD_B);
    SGG(GUARD_C, GUARD_C);
    SGG(GUARD_D, GUARD_D);
    SGG(GUARD_E, GUARD_E);
    SGG(HORSE_B, HORSE_B);
    SGG(HORSE_C, HORSE_C);
    SGG(HORSE_D, HORSE_D);
    SGG(HORSE_E, HORSE_E);
    SGG(HORSE_F, HORSE_F);
    SGG(HORSE_G, HORSE_G);
    m[1] = _SCRStartLwsDemoOrient(m[0], SDemoStationedMotOriData_ENDDEMO_LWS + 4, *(int *)(GetLayoutClass(th) + 0x134), th);
    demoManStart(GameObject_DEMO_END_STARTER[2], m[0]);
    SetScriptObjDeleteCallBackFunc(th, func_0004EB18, m);
    while (!CheckDemoCameraOrientFinished(m[0])) {
        m[3] = demoscrCheckDemoFinish();
        if (m[3])
            break;
        if (demoscrCheckDemoCutSkip() && demoManChkLoadFinish(GameObject_DEMO_END_STARTER[2]))
            demoManSkip(GameObject_DEMO_END_STARTER[2], m[0]);
        endingflowTickAdpcmSeq(*(int *)(m[0] + 0x40));
        scrRun();
    }
    func_0004EB18(th, m);
    SetScriptObjDeleteCallBackFunc(th, 0, 0);
}
