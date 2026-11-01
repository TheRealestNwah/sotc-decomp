typedef struct {
    unsigned int active : 1;
    unsigned int end : 1;
    unsigned int pad2 : 1;
    unsigned int ready : 1;
    int b;
    int arg;
    void *obj;
} DemoInfo;

extern DemoInfo activedemoInfo;
extern void *isysGetThisSubThread(void);
extern void scrInit(void *);
extern void gameModeSet(int);
extern void gameModeCls(int);
extern void PauseCamFinalizer(int);
extern void scrRun(void);
extern void activeDemoCancel(int);
extern void setDefaultFsEffect(void);
extern void *get_main_cameraman(void);
extern void *get_game_camera(void *);
extern void end_stream_lws_movie_playing_game_camera(void *);

void st_activedemoflow(void)
{
    scrInit(isysGetThisSubThread());
    gameModeSet(1);
    PauseCamFinalizer(1);
    while (!activedemoInfo.ready)
        scrRun();
    activedemoInfo.active = 1;
    while (!activedemoInfo.end)
        scrRun();
    activeDemoCancel(activedemoInfo.arg);
    setDefaultFsEffect();
    end_stream_lws_movie_playing_game_camera(get_game_camera(get_main_cameraman()));
    PauseCamFinalizer(0);
    gameModeCls(1);
}
