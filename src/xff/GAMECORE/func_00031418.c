extern int DldSysUndefSymbol;
extern char gcGlobalVar[];
typedef struct { int a, b; unsigned int h; } Ent;
extern Ent *B_00188990;
extern int B_00188994;
extern void *SCRGetFirstObj(void *);
extern void SetCharacterObjDemoMotionMode(void *, int, int, float);
extern char *GetScriptCharacterClass(void *);
extern void isysRequestDeleteObj(void *);
extern void FinishDemoCameraOrient(void *);
extern void *get_main_cameraman(void);
extern void *get_game_camera(void *);
extern void end_stream_lws_movie_playing_game_camera(void *);
extern void activedemoflowDemoEnd(void);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static void func_00031418(void *unused, void **d)
{
    int i;

    for (i = 0; i < B_00188994; i++) {
        Ent *e = B_00188990 + i;
        char *r = dldResolve(&e->h);
        void *obj;

        if (r != 0)
            obj = *(void **)(r + 8);
        else
            obj = SCRGetFirstObj(gcGlobalVar + 0x2B4);
        SetCharacterObjDemoMotionMode(obj, 0, 0, 0.0f);
        *(int *)(GetScriptCharacterClass(obj) + 0x1204) = 0;
    }
    isysRequestDeleteObj(d[1]);
    FinishDemoCameraOrient(d[0]);
    end_stream_lws_movie_playing_game_camera(get_game_camera(get_main_cameraman()));
    activedemoflowDemoEnd();
    if (d[2] != 0)
        ((void (*)(void))d[2])();
}
