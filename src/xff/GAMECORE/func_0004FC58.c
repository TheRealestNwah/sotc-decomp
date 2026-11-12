/* func_0004FC58: ending demo teardown (5 diffs: li a0,1 for fadeWhiteOut is scheduled before the 0.4f constant instead of into the delay slot) */
extern void FinishDemoCameraOrient(int);
extern char *GetScriptCharacterClass(int);
extern void PauseGame(int);
extern void ReleaseGame(int);
extern int SetCharacterObjDemoMotionMode(int, int, int, float);
extern void demoManEnd(int);
extern void end_stream_lws_movie_playing_game_camera(int);
extern void endingflowDemoEnd(void);
extern void endingflowEndAdpcmSeq(int);
extern void fadeWhiteOut(int, int, float);
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

#ifdef NONMATCHING
#define STOP(o, f) \
    SetCharacterObjDemoMotionMode((o)[2], 0, 0, f); \
    *(int *)(GetScriptCharacterClass((o)[2]) + 0x1204) = 0

void func_0004FC58(int unused, int *a)
{
    endingflowEndAdpcmSeq(a[3]);
    PauseGame(1);
    fadeWhiteOut(1, 0, 0.4f);
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
#endif
