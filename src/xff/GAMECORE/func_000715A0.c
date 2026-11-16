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

static void func_000715A0(void *unused, Arg *a)
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
