typedef struct { char c[16]; } SpriteParam;

typedef struct {
    char pad0[0x28];
    void (*exec)(unsigned char *, float, int, void (*)(void), void *);
    void (*draw)(unsigned char *);
} SpriteMenu;

typedef struct { char pad[0x168]; float time; int pad16C; float speed; } GcGlobal;

typedef struct {
    int active;
    int mode;
    float t8;
    float start;
} ProgressiveCheck;

extern void *isysGetThisSubThread(void);
extern SpriteMenu *GetSpriteMenuClass(unsigned char *);
extern void ScrSpriteParamSetup(SpriteParam *, SpriteParam *);
extern void ScrSpriteParamEnd(SpriteParam *, int);
extern void SpriteMenuSetDispFlag(unsigned char *o, int i, int disp);
extern void SpriteMenuSetLayer(unsigned char *o, int layer);
extern void SpriteMenuSetSelectMenuId(unsigned char *menu, int id);
extern void scrRun(void);
extern GcGlobal gcGlobalVar;
extern void _optionWorkSet(int, int);
extern int *getProgressiveMode(void);
extern void graphFrameBufferReInitializeRequest(void);
extern void setAspect(int);
extern void func_00094FE0(void);

void progressive_check_script(SpriteParam *parameters)
{
    static const ProgressiveCheck init = { 1, 0, 0.0f, 0.0f };
    ProgressiveCheck st;
    SpriteParam local;
    unsigned char *thread;
    SpriteMenu *menu;
    int ready;

    thread = isysGetThisSubThread();
    menu = GetSpriteMenuClass(thread);
    st = init;
    ScrSpriteParamSetup(&local, parameters);
    _optionWorkSet(6, 0);
    SpriteMenuSetDispFlag(thread, 0, 1);
    SpriteMenuSetLayer(thread, 0);
    SpriteMenuSetSelectMenuId(thread, 1);

    st.start = gcGlobalVar.time - 3.0f;
    while (st.active) {
        ready = 3.0f <= gcGlobalVar.time - st.start;
        if (st.mode == 1 && 15.0f < gcGlobalVar.time - st.t8) {
            if (*getProgressiveMode() != 0) {
                *getProgressiveMode() = 0;
                _optionWorkSet(6, 0);
                graphFrameBufferReInitializeRequest();
                scrRun();
                setAspect(-1);
            }
            SpriteMenuSetDispFlag(thread, 1, 0);
            SpriteMenuSetDispFlag(thread, 0, 1);
            SpriteMenuSetLayer(thread, 0);
            SpriteMenuSetSelectMenuId(thread, 1);
            st.mode = 0;
            st.start = gcGlobalVar.time - 3.0f + 1.0f;
        }
        menu->exec(thread, gcGlobalVar.speed, ready | 4, func_00094FE0, &st);
        menu->draw(thread);
        scrRun();
    }
    ScrSpriteParamEnd(&local, 1);
}
