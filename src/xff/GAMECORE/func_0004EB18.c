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
