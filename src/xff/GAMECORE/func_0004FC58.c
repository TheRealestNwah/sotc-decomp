extern void FinishDemoCameraOrient(int);
extern char *GetScriptCharacterClass(int);
extern void PauseGame(int);
extern void ReleaseGame(int);
extern int SetCharacterObjDemoMotionMode(int, int, int, float);
extern void demoManEnd(int);
extern void end_stream_lws_movie_playing_game_camera(int);
extern void endingflowDemoEnd(void);
extern void endingflowEndAdpcmSeq(int);
extern void fadeWhiteOut(float, int, int);
extern int get_game_camera(int);
extern int get_main_cameraman(void);
extern void isysRequestDeleteObj(int);
extern int *GameObject_DEMO_END2_STARTER;
extern int *GameObject_DORMIN;
extern int *GameObject_GIRL_END;
extern int *GameObject_GUARD_A;
extern int *GameObject_GUARD_B;
extern int *GameObject_GUARD_C;
extern int *GameObject_GUARD_D;
extern int *GameObject_GUARD_E;
extern int *GameObject_PLAYER_A_DEMO_MORPH;
extern int *GameObject_SHARMAN;

#define STOP(o, f) \
    SetCharacterObjDemoMotionMode((o)[2], 0, 0, f); \
    *(int *)(GetScriptCharacterClass((o)[2]) + 0x1204) = 0

static void func_0004FC58(int unused, int *a)
{
    endingflowEndAdpcmSeq(a[3]);
    PauseGame(1);
    fadeWhiteOut(0.4f, 1, 0);
    ReleaseGame(1);
    STOP(GameObject_GIRL_END, 0);
    STOP(GameObject_DORMIN, 0);
    STOP(GameObject_SHARMAN, 0);
    STOP(GameObject_GUARD_A, 0);
    STOP(GameObject_GUARD_B, 0);
    STOP(GameObject_GUARD_C, 0);
    STOP(GameObject_GUARD_D, 0);
    STOP(GameObject_GUARD_E, 0);
    STOP(GameObject_PLAYER_A_DEMO_MORPH, 10.0f);
    STOP(a, 10.0f);
    isysRequestDeleteObj(a[1]);
    FinishDemoCameraOrient(a[0]);
    end_stream_lws_movie_playing_game_camera(get_game_camera(get_main_cameraman()));
    demoManEnd(GameObject_DEMO_END2_STARTER[2]);
    endingflowDemoEnd();
}

typedef struct { int frame; int vol; int seq; } SeqEnt;
typedef struct { int i0; int status; } CtrlDef;
extern int AdpcmSeq_DEMO_ED3_C1;
extern char *SDemoStationedMotOriData_ENDDEMO2_CAMERA, *SDemoStationedMotOriData_ENDDEMO2_PLAYER,
    *SDemoStationedMotOriData_ENDDEMO2_HORSE, *SDemoStationedMotOriData_ENDDEMO2_GIRL,
    *SDemoStationedMotOriData_ENDDEMO2_DORMIN, *SDemoStationedMotOriData_ENDDEMO2_SHARMAN,
    *SDemoStationedMotOriData_ENDDEMO2_GUARD_A, *SDemoStationedMotOriData_ENDDEMO2_GUARD_B,
    *SDemoStationedMotOriData_ENDDEMO2_GUARD_C, *SDemoStationedMotOriData_ENDDEMO2_GUARD_D,
    *SDemoStationedMotOriData_ENDDEMO2_GUARD_E, *SDemoStationedMotOriData_ENDDEMO2_LWS;
extern CtrlDef *ScriptCtrlDef_SCRDemoCharaMaru, *ScriptCtrlDef_SCRDemoCharaBatsu, *ScriptCtrlDef_SCRDemoCharaSankaku,
    *ScriptCtrlDef_SCRDemoCharaShikaku, *ScriptCtrlDef_SCRDemoCharaR1;
extern int endingReady;
typedef struct { int i0; int i4; int trig; } Pad;
extern Pad padManagerData;
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
extern int gStatGetHorseDemoISYSObj(void);
extern int _SCRStartLwsDemoOrient(int, char *, int, int);
extern void demoManStart(int, int);
extern void SetScriptObjDeleteCallBackFunc(int, void *, void *);
extern int CheckDemoCameraOrientFinished(int);
extern int demoscrCheckDemoFinish(void);
extern int demoscrCheckDemoCutSkip(void);
extern int demoManChkLoadFinish(int);
extern void demoManSkip(int, int);
extern void SetCharacterObjScriptKeyEnableFlagOnDemoOrient(int, int);
extern void CharaCtrlSetOutsideScriptCtrlStatus(int, int);

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

#define PAD(bit, def) \
    if (padManagerData.trig & (bit)) \
        CharaCtrlSetOutsideScriptCtrlStatus(GameObject_DORMIN[2], (def)->status)

void demo_end2(void)
{
    SeqEnt seq[2] = { { 0, 99999, AdpcmSeq_DEMO_ED3_C1 }, { 0, 0x3E7, 0 } };
    int starter = GameObject_DEMO_END2_STARTER[2];
    int th = isysGetThisSubThread();
    void *part = iosCreatePartition(rootPtn, 0x47);
    char *lc;
    int *m;
    int cam;
    char *lay;
    float f;
    int o;
    int frame;

    *(void **)(GetScriptLayoutClass(th) + 0x2D4) = part;
    SetScriptLayoutObjLetterProcMode(th, 1);
    lc = GetScriptLayoutClass(th);
    m = _SCRMallocAlign(part, 0x14, 0x10);
    *(int **)(lc + 0x2D8) = m;
    m[3] = 0;
    endingflowStartAdpcmSeq(seq);
    m[4] = 0;
    demoManBootRequest(starter);
    while (demoManBootChk(starter) != 1)
        scrRun();
    endingReady |= 2;
    while (endingReady != 3)
        scrRun();
    cam = get_main_cameraman_camera_obj();
    lay = GetLayoutClass(th);
    if (*(unsigned int **)(GetScriptLayoutClass(GameObject_DEMO_END2_STARTER[2]) + 0x2DC) != 0)
        f = *(float *)(resourceData(*(unsigned int **)(GetScriptLayoutClass(GameObject_DEMO_END2_STARTER[2]) + 0x2DC)) + 0x10);
    else
        f = 1.0f;
    m[0] = PlayDemoCameraOrient(cam, SDemoStationedMotOriData_ENDDEMO2_CAMERA + 4, *(int *)(lay + 0x134), th,
                                GameObject_DEMO_END2_STARTER[2], f);
    begin_stream_lws_movie_playing_game_camera(get_game_camera(get_main_cameraman()));
    o = GameObject_PLAYER_A_DEMO_MORPH[2];
    SETUP(o, SDemoStationedMotOriData_ENDDEMO2_PLAYER);
    o = gStatGetHorseDemoISYSObj();
    m[2] = o;
    SETUP(o, SDemoStationedMotOriData_ENDDEMO2_HORSE);
    SETUPG(GameObject_GIRL_END, SDemoStationedMotOriData_ENDDEMO2_GIRL);
    { register int *gg __asm__("$3") = GameObject_DORMIN; o = gg[2]; }
    SETUP(o, SDemoStationedMotOriData_ENDDEMO2_DORMIN);
    SETUPG(GameObject_SHARMAN, SDemoStationedMotOriData_ENDDEMO2_SHARMAN);
    SETUPG(GameObject_GUARD_A, SDemoStationedMotOriData_ENDDEMO2_GUARD_A);
    SETUPG(GameObject_GUARD_B, SDemoStationedMotOriData_ENDDEMO2_GUARD_B);
    SETUPG(GameObject_GUARD_C, SDemoStationedMotOriData_ENDDEMO2_GUARD_C);
    SETUPG(GameObject_GUARD_D, SDemoStationedMotOriData_ENDDEMO2_GUARD_D);
    SETUPG(GameObject_GUARD_E, SDemoStationedMotOriData_ENDDEMO2_GUARD_E);
    m[1] = _SCRStartLwsDemoOrient(m[0], SDemoStationedMotOriData_ENDDEMO2_LWS + 4, *(int *)(GetLayoutClass(th) + 0x134), th);
    demoManStart(GameObject_DEMO_END2_STARTER[2], m[0]);
    SetScriptObjDeleteCallBackFunc(th, func_0004FC58, m);
    while (!CheckDemoCameraOrientFinished(m[0])) {
        m[3] = demoscrCheckDemoFinish();
        if (m[3])
            break;
        frame = *(int *)(m[0] + 0x40);
        if (demoscrCheckDemoCutSkip() && demoManChkLoadFinish(GameObject_DEMO_END2_STARTER[2]))
            demoManSkip(GameObject_DEMO_END2_STARTER[2], m[0]);
        endingflowTickAdpcmSeq(*(int *)(m[0] + 0x40));
        if (frame < 10) {
            if (m[4] == 0) {
                SetCharacterObjScriptKeyEnableFlagOnDemoOrient(GameObject_DORMIN[2], 1);
                m[4] = 1;
            }
            PAD(0x20, ScriptCtrlDef_SCRDemoCharaMaru);
            PAD(0x40, ScriptCtrlDef_SCRDemoCharaBatsu);
            PAD(0x10, ScriptCtrlDef_SCRDemoCharaSankaku);
            PAD(0x80, ScriptCtrlDef_SCRDemoCharaShikaku);
            PAD(0x08, ScriptCtrlDef_SCRDemoCharaR1);
        } else if (m[4] != 0) {
            SetCharacterObjScriptKeyEnableFlagOnDemoOrient(GameObject_DORMIN[2], 0);
            m[4] = 0;
        }
        scrRun();
    }
    func_0004FC58(th, m);
    SetScriptObjDeleteCallBackFunc(th, 0, 0);
}
