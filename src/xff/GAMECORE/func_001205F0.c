extern int *DldSysUndefSymbol;
extern void (*D_0017B8B0)(int);
extern int D_0017B8B4;
extern struct {
    int a;
    int b;
    int trig;
} padManagerData;
extern char *getSCRDataCtrlWork(void);
extern void gameflowSetPauseEnable(int);
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern int get_main_cameraman(void);
extern int is_playing_lws_movie_now_game_camera(int);
extern void scrRun(void);
extern void scrRunM(int);
extern void PauseGame(int);
extern void ReleaseGame(int);
extern void bgmPlayerDemoEndTypeAllClose(void);
extern void fadeOut(int, int, float);
extern void fadeIn(int, int, float);
extern void compel_end_lws_movie_mode_game_camera(int);
extern void SCRDeleteAllActiveScriptAnimationObj(void);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static void func_001205F0(int obj)
{
    unsigned int *h = *(unsigned int **)(getSCRDataCtrlWork() + 0x4168);
    char *e;
    int cam;

    gameflowSetPauseEnable(0);
    e = dldResolve(h);
    if (e != 0)
        CharaCtrlSetScriptCtrlStatus(obj, *(int *)(e + 4));
    while (is_playing_lws_movie_now_game_camera(get_main_cameraman()) == 0)
        scrRun();
    while (is_playing_lws_movie_now_game_camera(cam = get_main_cameraman()) != 0) {
        if (padManagerData.trig & 0x800) {
            PauseGame(1);
            bgmPlayerDemoEndTypeAllClose();
            if (D_0017B8B0 != 0) {
                D_0017B8B0(D_0017B8B4);
                D_0017B8B0 = 0;
            }
            fadeOut(1, 0, 0.4f);
            scrRunM(0x14);
            ReleaseGame(1);
            e = dldResolve(h + 1);
            if (e != 0) {
                CharaCtrlSetScriptCtrlStatus(obj, *(int *)(e + 4));
                scrRun();
            }
            compel_end_lws_movie_mode_game_camera(cam);
            SCRDeleteAllActiveScriptAnimationObj();
            fadeIn(0, 0, 1.0f);
            break;
        }
        scrRun();
    }
    if (D_0017B8B0 != 0) {
        D_0017B8B0(D_0017B8B4);
        D_0017B8B0 = 0;
    }
    gameflowSetPauseEnable(1);
}
