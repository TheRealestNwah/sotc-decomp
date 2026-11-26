extern void endBossDeathEffect(void);
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
#define SETUP_func_0004FC58(o, d)                                                                        \
    *(int *)(GetScriptCharacterClass(o) + 0x1204) = 1;                                                 \
    SetCharacterObjDemoMotionMode(o, (int)((d) + 4), *(int *)(GetLayoutClass(th) + 0x134), 0.0f); \
    isysAddGroupWithLinkParam(o, m[0], 0, 0)
#define SETUPG_func_0004FC58(g, d)            \
    {                           \
        int *gg = (g);         \
        int o;                  \
        __asm__("" : "+r"(gg)); \
        o = gg[2];            \
        SETUP_func_0004FC58(o, d);            \
    }
#define PAD_func_0004FC58(bit, def) \
    if (padManagerData.trig & (bit)) \
        CharaCtrlSetOutsideScriptCtrlStatus(GameObject_DORMIN[2], (def)->status)
extern int *GameObject_GIRL_END3;
extern int *GameObject_HORSE_B, *GameObject_HORSE_C, *GameObject_HORSE_D, *GameObject_HORSE_E, *GameObject_HORSE_F, *GameObject_HORSE_G;
extern int *GameObject_BABY, *GameObject_DEER, *GameObject_SQUIRREL;
extern int *GameObject_BIRD_B_DEMO, *GameObject_BIRD_C_DEMO, *GameObject_BIRD_D_DEMO, *GameObject_BIRD_E_DEMO, *GameObject_BIRD_F_DEMO, *GameObject_BIRD_G_DEMO, *GameObject_BIRD_H_DEMO;
extern int *GameObject_PLAYER_A_DEMO, *GameObject_DEMO_END3_STARTER;
#define END(o, f) \
    SetCharacterObjDemoMotionMode((o)[2], 0, 0, f); \
    *(int *)(GetScriptCharacterClass((o)[2]) + 0x1204) = 0
extern int AdpcmSeq_DEMO_ED5_C1, AdpcmSeq_DEMO_ED7_C2, AdpcmSeq_DEMO_ED8_C11, AdpcmSeq_DEMO_ED8_C18;
extern char *SDemoStationedMotOriData_ENDDEMO3_CAMERA, *SDemoStationedMotOriData_ENDDEMO3_PLAYER,
    *SDemoStationedMotOriData_ENDDEMO3_HORSE, *SDemoStationedMotOriData_ENDDEMO3_GIRL,
    *SDemoStationedMotOriData_ENDDEMO3_SHARMAN, *SDemoStationedMotOriData_ENDDEMO3_GUARD_A,
    *SDemoStationedMotOriData_ENDDEMO3_GUARD_B, *SDemoStationedMotOriData_ENDDEMO3_GUARD_C,
    *SDemoStationedMotOriData_ENDDEMO3_GUARD_D, *SDemoStationedMotOriData_ENDDEMO3_GUARD_E,
    *SDemoStationedMotOriData_ENDDEMO3_HORSE_B, *SDemoStationedMotOriData_ENDDEMO3_HORSE_C,
    *SDemoStationedMotOriData_ENDDEMO3_HORSE_D, *SDemoStationedMotOriData_ENDDEMO3_HORSE_E,
    *SDemoStationedMotOriData_ENDDEMO3_HORSE_F, *SDemoStationedMotOriData_ENDDEMO3_HORSE_G,
    *SDemoStationedMotOriData_ENDDEMO3_BABY, *SDemoStationedMotOriData_ENDDEMO3_DEER,
    *SDemoStationedMotOriData_ENDDEMO3_SQUIRREL, *SDemoStationedMotOriData_ENDDEMO3_BIRD_B,
    *SDemoStationedMotOriData_ENDDEMO3_BIRD_C, *SDemoStationedMotOriData_ENDDEMO3_BIRD_D,
    *SDemoStationedMotOriData_ENDDEMO3_BIRD_E, *SDemoStationedMotOriData_ENDDEMO3_BIRD_F,
    *SDemoStationedMotOriData_ENDDEMO3_BIRD_G, *SDemoStationedMotOriData_ENDDEMO3_BIRD_H,
    *SDemoStationedMotOriData_ENDDEMO3_LWS;
#define SETUP_func_00050678(o, d)                                                                        \
    *(int *)(GetScriptCharacterClass(o) + 0x1204) = 1;                                     \
    SetCharacterObjDemoMotionMode(o, (int)((d) + 4), *(int *)(GetLayoutClass(th) + 0x134), 0.0f); \
    isysAddGroupWithLinkParam(o, m[0], 0, 0)
#define SETUPG_func_00050678(g, d)            \
    {                           \
        int *gg = (g);          \
        int o;                  \
        __asm__("" : "+r"(gg)); \
        o = gg[2];              \
        SETUP_func_00050678(o, d);            \
    }
#define PAD_func_00050678(bit, def)                                                   \
    if (padManagerData.trig & (bit)) {                                  \
        CharaCtrlSetOutsideScriptCtrlStatus(GameObject_GIRL_END3[2], (def)->status); \
        CharaCtrlSetOutsideScriptCtrlStatus(GameObject_BABY[2], (def)->status); \
    }

void demo_PlayerDeathEffectEnd(void)
{
    endBossDeathEffect();
}

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
    SETUP_func_0004FC58(o, SDemoStationedMotOriData_ENDDEMO2_PLAYER);
    o = gStatGetHorseDemoISYSObj();
    m[2] = o;
    SETUP_func_0004FC58(o, SDemoStationedMotOriData_ENDDEMO2_HORSE);
    SETUPG_func_0004FC58(GameObject_GIRL_END, SDemoStationedMotOriData_ENDDEMO2_GIRL);
    { register int *gg __asm__("$3") = GameObject_DORMIN; o = gg[2]; }
    SETUP_func_0004FC58(o, SDemoStationedMotOriData_ENDDEMO2_DORMIN);
    SETUPG_func_0004FC58(GameObject_SHARMAN, SDemoStationedMotOriData_ENDDEMO2_SHARMAN);
    SETUPG_func_0004FC58(GameObject_GUARD_A, SDemoStationedMotOriData_ENDDEMO2_GUARD_A);
    SETUPG_func_0004FC58(GameObject_GUARD_B, SDemoStationedMotOriData_ENDDEMO2_GUARD_B);
    SETUPG_func_0004FC58(GameObject_GUARD_C, SDemoStationedMotOriData_ENDDEMO2_GUARD_C);
    SETUPG_func_0004FC58(GameObject_GUARD_D, SDemoStationedMotOriData_ENDDEMO2_GUARD_D);
    SETUPG_func_0004FC58(GameObject_GUARD_E, SDemoStationedMotOriData_ENDDEMO2_GUARD_E);
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
            PAD_func_0004FC58(0x20, ScriptCtrlDef_SCRDemoCharaMaru);
            PAD_func_0004FC58(0x40, ScriptCtrlDef_SCRDemoCharaBatsu);
            PAD_func_0004FC58(0x10, ScriptCtrlDef_SCRDemoCharaSankaku);
            PAD_func_0004FC58(0x80, ScriptCtrlDef_SCRDemoCharaShikaku);
            PAD_func_0004FC58(0x08, ScriptCtrlDef_SCRDemoCharaR1);
        } else if (m[4] != 0) {
            SetCharacterObjScriptKeyEnableFlagOnDemoOrient(GameObject_DORMIN[2], 0);
            m[4] = 0;
        }
        scrRun();
    }
    func_0004FC58(th, m);
    SetScriptObjDeleteCallBackFunc(th, 0, 0);
}

static void func_00050678(int a0, int *p)
{
    float z = 0.0f;
    float t = 10.0f;
    endingflowEndAdpcmSeq(p[4]);
    END(GameObject_GIRL_END3, z);
    END(GameObject_SHARMAN, z);
    END(GameObject_GUARD_A, z);
    END(GameObject_GUARD_B, z);
    END(GameObject_GUARD_C, z);
    END(GameObject_GUARD_D, z);
    END(GameObject_GUARD_E, z);
    END(GameObject_HORSE_B, z);
    END(GameObject_HORSE_C, z);
    END(GameObject_HORSE_D, z);
    END(GameObject_HORSE_E, z);
    END(GameObject_HORSE_F, z);
    END(GameObject_HORSE_G, z);
    END(GameObject_BABY, z);
    END(GameObject_DEER, z);
    END(GameObject_SQUIRREL, z);
    END(GameObject_BIRD_B_DEMO, z);
    END(GameObject_BIRD_C_DEMO, z);
    END(GameObject_BIRD_D_DEMO, z);
    END(GameObject_BIRD_E_DEMO, z);
    END(GameObject_BIRD_F_DEMO, z);
    END(GameObject_BIRD_G_DEMO, z);
    END(GameObject_BIRD_H_DEMO, z);
    END(GameObject_PLAYER_A_DEMO, t);
    END(p, t);
    isysRequestDeleteObj(p[1]);
    FinishDemoCameraOrient(p[0]);
    end_stream_lws_movie_playing_game_camera(get_game_camera(get_main_cameraman()));
    demoManEnd(GameObject_DEMO_END3_STARTER[2]);
    endingflowDemoEnd();
}

void demo_end3(void)
{
    SeqEnt seq[5] = { { 0, 0x3E7, AdpcmSeq_DEMO_ED5_C1 }, { 0x26, 0x36, AdpcmSeq_DEMO_ED7_C2 },
                     { 0x35, 0x3B, AdpcmSeq_DEMO_ED8_C11 }, { 0x3A, 0x3E7, AdpcmSeq_DEMO_ED8_C18 },
                     { 0, 0x3E7, 0 } };
    int starter = GameObject_DEMO_END3_STARTER[2];
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
    m[4] = 0;
    endingflowStartAdpcmSeq(seq);
    demoManBootRequest(starter);
    while (demoManBootChk(starter) != 1)
        scrRun();
    endingReady |= 2;
    while (endingReady != 3)
        scrRun();
    cam = get_main_cameraman_camera_obj();
    lay = GetLayoutClass(th);
    if (*(unsigned int **)(GetScriptLayoutClass(GameObject_DEMO_END3_STARTER[2]) + 0x2DC) != 0)
        f = *(float *)(resourceData(*(unsigned int **)(GetScriptLayoutClass(GameObject_DEMO_END3_STARTER[2]) + 0x2DC)) + 0x10);
    else
        f = 1.0f;
    m[0] = PlayDemoCameraOrient(cam, SDemoStationedMotOriData_ENDDEMO3_CAMERA + 4, *(int *)(lay + 0x134), th,
                                GameObject_DEMO_END3_STARTER[2], f);
    begin_stream_lws_movie_playing_game_camera(get_game_camera(get_main_cameraman()));
    o = GameObject_PLAYER_A_DEMO[2];
    SETUP_func_00050678(o, SDemoStationedMotOriData_ENDDEMO3_PLAYER);
    o = gStatGetHorseDemoISYSObj();
    m[2] = o;
    SETUP_func_00050678(o, SDemoStationedMotOriData_ENDDEMO3_HORSE);
    { register int *gg __asm__("$3") = GameObject_GIRL_END3; o = gg[2]; }
    SETUP_func_00050678(o, SDemoStationedMotOriData_ENDDEMO3_GIRL);
    SETUPG_func_00050678(GameObject_SHARMAN, SDemoStationedMotOriData_ENDDEMO3_SHARMAN);
    SETUPG_func_00050678(GameObject_GUARD_A, SDemoStationedMotOriData_ENDDEMO3_GUARD_A);
    SETUPG_func_00050678(GameObject_GUARD_B, SDemoStationedMotOriData_ENDDEMO3_GUARD_B);
    SETUPG_func_00050678(GameObject_GUARD_C, SDemoStationedMotOriData_ENDDEMO3_GUARD_C);
    SETUPG_func_00050678(GameObject_GUARD_D, SDemoStationedMotOriData_ENDDEMO3_GUARD_D);
    SETUPG_func_00050678(GameObject_GUARD_E, SDemoStationedMotOriData_ENDDEMO3_GUARD_E);
    SETUPG_func_00050678(GameObject_HORSE_B, SDemoStationedMotOriData_ENDDEMO3_HORSE_B);
    SETUPG_func_00050678(GameObject_HORSE_C, SDemoStationedMotOriData_ENDDEMO3_HORSE_C);
    SETUPG_func_00050678(GameObject_HORSE_D, SDemoStationedMotOriData_ENDDEMO3_HORSE_D);
    SETUPG_func_00050678(GameObject_HORSE_E, SDemoStationedMotOriData_ENDDEMO3_HORSE_E);
    SETUPG_func_00050678(GameObject_HORSE_F, SDemoStationedMotOriData_ENDDEMO3_HORSE_F);
    SETUPG_func_00050678(GameObject_HORSE_G, SDemoStationedMotOriData_ENDDEMO3_HORSE_G);
    { register int *gg __asm__("$3") = GameObject_BABY; o = gg[2]; }
    SETUP_func_00050678(o, SDemoStationedMotOriData_ENDDEMO3_BABY);
    SETUPG_func_00050678(GameObject_DEER, SDemoStationedMotOriData_ENDDEMO3_DEER);
    SETUPG_func_00050678(GameObject_SQUIRREL, SDemoStationedMotOriData_ENDDEMO3_SQUIRREL);
    SETUPG_func_00050678(GameObject_BIRD_B_DEMO, SDemoStationedMotOriData_ENDDEMO3_BIRD_B);
    SETUPG_func_00050678(GameObject_BIRD_C_DEMO, SDemoStationedMotOriData_ENDDEMO3_BIRD_C);
    SETUPG_func_00050678(GameObject_BIRD_D_DEMO, SDemoStationedMotOriData_ENDDEMO3_BIRD_D);
    SETUPG_func_00050678(GameObject_BIRD_E_DEMO, SDemoStationedMotOriData_ENDDEMO3_BIRD_E);
    SETUPG_func_00050678(GameObject_BIRD_F_DEMO, SDemoStationedMotOriData_ENDDEMO3_BIRD_F);
    SETUPG_func_00050678(GameObject_BIRD_G_DEMO, SDemoStationedMotOriData_ENDDEMO3_BIRD_G);
    SETUPG_func_00050678(GameObject_BIRD_H_DEMO, SDemoStationedMotOriData_ENDDEMO3_BIRD_H);
    m[1] = _SCRStartLwsDemoOrient(m[0], SDemoStationedMotOriData_ENDDEMO3_LWS + 4, *(int *)(GetLayoutClass(th) + 0x134), th);
    demoManStart(GameObject_DEMO_END3_STARTER[2], m[0]);
    SetScriptObjDeleteCallBackFunc(th, func_00050678, m);
    while (!CheckDemoCameraOrientFinished(m[0])) {
        frame = *(int *)(m[0] + 0x40);
        if (demoscrCheckDemoCutSkip() && demoManChkLoadFinish(GameObject_DEMO_END3_STARTER[2]))
            demoManSkip(GameObject_DEMO_END3_STARTER[2], m[0]);
        if (frame >= 0x30) {
            if (m[3] == 0) {
                SetCharacterObjScriptKeyEnableFlagOnDemoOrient(GameObject_GIRL_END3[2], 1);
                SetCharacterObjScriptKeyEnableFlagOnDemoOrient(GameObject_BABY[2], 1);
                m[3] = 1;
            }
            PAD_func_00050678(0x20, ScriptCtrlDef_SCRDemoCharaMaru);
            PAD_func_00050678(0x40, ScriptCtrlDef_SCRDemoCharaBatsu);
            PAD_func_00050678(0x10, ScriptCtrlDef_SCRDemoCharaSankaku);
            PAD_func_00050678(0x80, ScriptCtrlDef_SCRDemoCharaShikaku);
            PAD_func_00050678(0x08, ScriptCtrlDef_SCRDemoCharaR1);
        }
        scrRun();
        endingflowTickAdpcmSeq(*(int *)(m[0] + 0x40));
    }
    func_00050678(th, m);
    SetScriptObjDeleteCallBackFunc(th, 0, 0);
}
