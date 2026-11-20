typedef struct { int i0; int i4; int obj; } GObj;
typedef struct { int h; int del; int obj; } Arg;
typedef struct { char pad0[0x1204]; int i1204; } SChara;
typedef struct { char pad0[0x48]; int disp; } Lay;
extern int B_0018B6A4;
extern GObj *GameObject_GIRL, *GameObject_GIRL_B, *GameObject_GIRL_CLOTH, *GameObject_SMOKE_MAN, *GameObject_SMOKE_MAN_B,
    *GameObject_SMOKE_MAN_C, *GameObject_SMOKE_MAN_D, *GameObject_SMOKE_MAN_E, *GameObject_BIRD_B_DEMO,
    *GameObject_BIRD_B2_DEMO, *GameObject_BIRD_B3_DEMO, *GameObject_BIRD_B4_DEMO, *GameObject_BIRD_B5_DEMO,
    *GameObject_DEMO_OP2_STARTER;
extern Lay *StageLayout_HOME_STOP_LWS, *StageLayout_HOME_EFF_LWS;
extern char gcGlobalVar[];
extern void endingflowEndAdpcmSeq(int);
extern void PauseGame(int);
extern void ReleaseGame(int);
extern void fadeOut(int, int, float);
extern void setNowLoadingMessageDisplayFlag(int);
extern int SetCharacterObjDemoMotionMode(int, int, int, float);
extern SChara *GetScriptCharacterClass(int);
extern int SCRGetFirstObj(void *);
extern void isysRequestDeleteObj(int);
extern void FinishDemoCameraOrient(int);
extern void SCRSetDispFlag(int, int);
extern void demoManEnd(int);
extern void opflowOp2End(int);

#define STOP(g, t)                                          \
    SetCharacterObjDemoMotionMode((g)->obj, 0, 0, t);       \
    GetScriptCharacterClass((g)->obj)->i1204 = 0

static void func_000715A0(int unused, Arg *a)
{
    endingflowEndAdpcmSeq(B_0018B6A4);
    PauseGame(1);
    if (B_0018B6A4 != 0) {
        fadeOut(1, 0, 0.4f);
        setNowLoadingMessageDisplayFlag(1);
    }
    STOP(GameObject_GIRL, 0.0f);
    STOP(GameObject_GIRL_B, 0.0f);
    STOP(GameObject_GIRL_CLOTH, 0.0f);
    STOP(GameObject_SMOKE_MAN, 0.0f);
    STOP(GameObject_SMOKE_MAN_B, 0.0f);
    STOP(GameObject_SMOKE_MAN_C, 0.0f);
    STOP(GameObject_SMOKE_MAN_D, 0.0f);
    STOP(GameObject_SMOKE_MAN_E, 0.0f);
    STOP(GameObject_BIRD_B_DEMO, 0.0f);
    STOP(GameObject_BIRD_B2_DEMO, 0.0f);
    STOP(GameObject_BIRD_B3_DEMO, 0.0f);
    STOP(GameObject_BIRD_B4_DEMO, 0.0f);
    STOP(GameObject_BIRD_B5_DEMO, 0.0f);
    SetCharacterObjDemoMotionMode(SCRGetFirstObj(gcGlobalVar + 0x2B0), 0, 0, 10.0f);
    GetScriptCharacterClass(SCRGetFirstObj(gcGlobalVar + 0x2B0))->i1204 = 0;
    SetCharacterObjDemoMotionMode(a->obj, 0, 0, 10.0f);
    GetScriptCharacterClass(a->obj)->i1204 = 0;
    isysRequestDeleteObj(a->del);
    FinishDemoCameraOrient(a->h);
    SCRSetDispFlag(StageLayout_HOME_STOP_LWS->disp, 1);
    SCRSetDispFlag(StageLayout_HOME_EFF_LWS->disp, 1);
    demoManEnd(GameObject_DEMO_OP2_STARTER->obj);
    opflowOp2End(B_0018B6A4);
    ReleaseGame(1);
}

typedef struct { int frame; int vol; int seq; } SeqEnt;
extern int AdpcmSeq_DEMO_OP2_C1, AdpcmSeq_DEMO_OP2_C18, AdpcmSeq_DEMO_OP2_C28, AdpcmSeq_DEMO_OP2_C37;
extern char *SDemoStationedMotOriData_OPDEMO2_CAMERA, *SDemoStationedMotOriData_OPDEMO2_PLAYER,
    *SDemoStationedMotOriData_OPDEMO2_HORSE, *SDemoStationedMotOriData_OPDEMO2_GIRL,
    *SDemoStationedMotOriData_OPDEMO2_GIRL_B, *SDemoStationedMotOriData_OPDEMO2_GIRL_CLOTH,
    *SDemoStationedMotOriData_OPDEMO2_SMOKE_MAN_A, *SDemoStationedMotOriData_OPDEMO2_SMOKE_MAN_B,
    *SDemoStationedMotOriData_OPDEMO2_SMOKE_MAN_C, *SDemoStationedMotOriData_OPDEMO2_SMOKE_MAN_D,
    *SDemoStationedMotOriData_OPDEMO2_SMOKE_MAN_E, *SDemoStationedMotOriData_OPDEMO2_BIRD_B1,
    *SDemoStationedMotOriData_OPDEMO2_BIRD_B2, *SDemoStationedMotOriData_OPDEMO2_BIRD_B3,
    *SDemoStationedMotOriData_OPDEMO2_BIRD_B4, *SDemoStationedMotOriData_OPDEMO2_BIRD_B5,
    *SDemoStationedMotOriData_OPDEMO2_LWS;
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
extern void opflowOp2Start(void);
extern int get_main_cameraman_camera_obj(void);
extern int get_main_cameraman(void);
extern int get_game_camera(int);
extern void begin_stream_lws_movie_playing_game_camera(int);
extern int PlayDemoCameraOrient(int, char *, int, int, int, float);
extern void isysAddGroupWithLinkParam(int, int, int, int);
extern int gStatGetHorseDemoISYSObj(void);
extern int _SCRStartLwsDemoOrient(int, char *, int, int);
extern void demoManStart(int, int);
extern void SetScriptObjDeleteCallBackFunc(int, void *, void *);
extern int inInNowLoadingEffect(void);
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
    GetScriptCharacterClass(o)->i1204 = 1;                                                 \
    SetCharacterObjDemoMotionMode(o, (int)((d) + 4), *(int *)(GetLayoutClass(th) + 0x134), 0.0f); \
    isysAddGroupWithLinkParam(o, m[0], 0, 0)

/* The empty asm keeps the GameObject pointer in its own register, as the Original does (lui $v1, lw $v0). */
#define SETUPG(g, d)            \
    {                           \
        GObj *gg = (g);         \
        int o;                  \
        __asm__("" : "+r"(gg)); \
        o = gg->obj;            \
        SETUP(o, d);            \
    }

void demo_op2(void)
{
    SeqEnt seq[5] = { { 0, 0x63, AdpcmSeq_DEMO_OP2_C1 }, { 0x11, 0x63, AdpcmSeq_DEMO_OP2_C18 },
                     { 0x1D, 0x63, AdpcmSeq_DEMO_OP2_C28 }, { 0x24, 0x63, AdpcmSeq_DEMO_OP2_C37 },
                     { 0, 0x3E7, 0 } };
    int starter = GameObject_DEMO_OP2_STARTER->obj;
    int th = isysGetThisSubThread();
    void *part = iosCreatePartition(rootPtn, 0x3F);
    char *lc;
    int *m;
    int cam;
    char *lay;
    float f;
    int o;
    int r;

    *(void **)(GetScriptLayoutClass(th) + 0x2D4) = part;
    SetScriptLayoutObjLetterProcMode(th, 1);
    lc = GetScriptLayoutClass(th);
    m = _SCRMallocAlign(part, 0xC, 0x10);
    *(int **)(lc + 0x2D8) = m;
    B_0018B6A4 = 0;
    endingflowStartAdpcmSeq(seq);
    demoManBootRequest(starter);
    while (demoManBootChk(starter) != 1)
        scrRun();
    opflowOp2Start();
    cam = get_main_cameraman_camera_obj();
    lay = GetLayoutClass(th);
    if (*(unsigned int **)(GetScriptLayoutClass(GameObject_DEMO_OP2_STARTER->obj) + 0x2DC) != 0)
        f = *(float *)(resourceData(*(unsigned int **)(GetScriptLayoutClass(GameObject_DEMO_OP2_STARTER->obj) + 0x2DC)) + 0x10);
    else
        f = 1.0f;
    m[0] = PlayDemoCameraOrient(cam, SDemoStationedMotOriData_OPDEMO2_CAMERA + 4, *(int *)(lay + 0x134), th,
                                GameObject_DEMO_OP2_STARTER->obj, f);
    begin_stream_lws_movie_playing_game_camera(get_game_camera(get_main_cameraman()));
    o = SCRGetFirstObj(gcGlobalVar + 0x2B0);
    SETUP(o, SDemoStationedMotOriData_OPDEMO2_PLAYER);
    o = gStatGetHorseDemoISYSObj();
    m[2] = o;
    SETUP(o, SDemoStationedMotOriData_OPDEMO2_HORSE);
    SETUPG(GameObject_GIRL, SDemoStationedMotOriData_OPDEMO2_GIRL);
    SETUPG(GameObject_GIRL_B, SDemoStationedMotOriData_OPDEMO2_GIRL_B);
    SETUPG(GameObject_GIRL_CLOTH, SDemoStationedMotOriData_OPDEMO2_GIRL_CLOTH);
    SETUPG(GameObject_SMOKE_MAN, SDemoStationedMotOriData_OPDEMO2_SMOKE_MAN_A);
    SETUPG(GameObject_SMOKE_MAN_B, SDemoStationedMotOriData_OPDEMO2_SMOKE_MAN_B);
    SETUPG(GameObject_SMOKE_MAN_C, SDemoStationedMotOriData_OPDEMO2_SMOKE_MAN_C);
    SETUPG(GameObject_SMOKE_MAN_D, SDemoStationedMotOriData_OPDEMO2_SMOKE_MAN_D);
    SETUPG(GameObject_SMOKE_MAN_E, SDemoStationedMotOriData_OPDEMO2_SMOKE_MAN_E);
    SETUPG(GameObject_BIRD_B_DEMO, SDemoStationedMotOriData_OPDEMO2_BIRD_B1);
    SETUPG(GameObject_BIRD_B2_DEMO, SDemoStationedMotOriData_OPDEMO2_BIRD_B2);
    SETUPG(GameObject_BIRD_B3_DEMO, SDemoStationedMotOriData_OPDEMO2_BIRD_B3);
    SETUPG(GameObject_BIRD_B4_DEMO, SDemoStationedMotOriData_OPDEMO2_BIRD_B4);
    SETUPG(GameObject_BIRD_B5_DEMO, SDemoStationedMotOriData_OPDEMO2_BIRD_B5);
    m[1] = _SCRStartLwsDemoOrient(m[0], SDemoStationedMotOriData_OPDEMO2_LWS + 4, *(int *)(GetLayoutClass(th) + 0x134), th);
    SCRSetDispFlag(StageLayout_HOME_STOP_LWS->disp, 0);
    SCRSetDispFlag(StageLayout_HOME_EFF_LWS->disp, 0);
    demoManStart(GameObject_DEMO_OP2_STARTER->obj, m[0]);
    SetScriptObjDeleteCallBackFunc(th, func_000715A0, m);
    do
        scrRun();
    while (inInNowLoadingEffect());
    opflowOp2Start();
    while (!CheckDemoCameraOrientFinished(m[0])) {
        r = demoscrCheckDemoFinish();
        if (r == 1)
            B_0018B6A4 = r;
        if (r)
            break;
        if (demoscrCheckDemoCutSkip() && demoManChkLoadFinish(GameObject_DEMO_OP2_STARTER->obj))
            demoManSkip(GameObject_DEMO_OP2_STARTER->obj, m[0]);
        endingflowTickAdpcmSeq(*(int *)(m[0] + 0x40));
        scrRun();
    }
    func_000715A0(th, (Arg *)m);
    SetScriptObjDeleteCallBackFunc(th, 0, 0);
}
