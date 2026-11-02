extern int *DldSysUndefSymbol;
extern char gcGlobalVar[];
typedef struct { int a; int b; unsigned int h; } DemoEnt;
extern DemoEnt *B_0018AF70;
extern int B_0018AF74;
extern int B_0018AF64;
extern int B_0018AF78;
extern int SCRGetFirstObj(void *);
extern void SetCharacterObjDemoMotionMode(int, int, int, float);
extern char *GetScriptCharacterClass(int);
extern void isysRequestDeleteObj(int);
extern void FinishDemoCameraOrient(void *);
extern int get_main_cameraman(void);
extern int get_game_camera(int);
extern void end_stream_lws_movie_playing_game_camera(int);
extern void demoManEnd(int);
extern void jumphokoraflowDemoEnd(int);

static inline char *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static void func_00060F78(void *unused, int *w)
{
    int flow;
    int i;
    int obj;
    char *e;
    DemoEnt *ent;

    flow = *(int *)(*(char **)w + 0x40) + 1;
    for (i = 0; i < B_0018AF74; i++) {
        ent = B_0018AF70;
        ent += i;
        e = dldElem(&ent->h);
        if (e != 0)
            obj = *(int *)(e + 8);
        else
            obj = SCRGetFirstObj(gcGlobalVar + 0x2B4);
        SetCharacterObjDemoMotionMode(obj, 0, 0, 0.0f);
        *(int *)(GetScriptCharacterClass(obj) + 0x1204) = 0;
    }
    isysRequestDeleteObj(w[1]);
    FinishDemoCameraOrient((void *)w[0]);
    end_stream_lws_movie_playing_game_camera(get_game_camera(get_main_cameraman()));
    demoManEnd(B_0018AF64);
    jumphokoraflowDemoEnd(B_0018AF78 == 0 ? 0 : flow);
}
