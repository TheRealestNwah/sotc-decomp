extern int *GameObject_GIRL_END3, *GameObject_SHARMAN, *GameObject_GUARD_A, *GameObject_GUARD_B, *GameObject_GUARD_C, *GameObject_GUARD_D, *GameObject_GUARD_E;
extern int *GameObject_HORSE_B, *GameObject_HORSE_C, *GameObject_HORSE_D, *GameObject_HORSE_E, *GameObject_HORSE_F, *GameObject_HORSE_G;
extern int *GameObject_BABY, *GameObject_DEER, *GameObject_SQUIRREL;
extern int *GameObject_BIRD_B_DEMO, *GameObject_BIRD_C_DEMO, *GameObject_BIRD_D_DEMO, *GameObject_BIRD_E_DEMO, *GameObject_BIRD_F_DEMO, *GameObject_BIRD_G_DEMO, *GameObject_BIRD_H_DEMO;
extern int *GameObject_PLAYER_A_DEMO, *GameObject_DEMO_END3_STARTER;
extern void endingflowEndAdpcmSeq(int);
extern int SetCharacterObjDemoMotionMode(int, int, int, float);
extern char *GetScriptCharacterClass(int);
extern void isysRequestDeleteObj(int);
extern void FinishDemoCameraOrient(int);
extern int get_main_cameraman(void);
extern int get_game_camera(int);
extern void end_stream_lws_movie_playing_game_camera(int);
extern void demoManEnd(int);
extern void endingflowDemoEnd(void);

#define END(o, f) \
    SetCharacterObjDemoMotionMode((o)[2], 0, 0, f); \
    *(int *)(GetScriptCharacterClass((o)[2]) + 0x1204) = 0

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
