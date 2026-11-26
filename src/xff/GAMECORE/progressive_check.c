extern char *GetSCRCharaAIWorkPtr(void *);
extern void bootTexAlphaAnim(void *, void *, float, float);
extern int D_0017AF40[];
static inline int texAnimEnd(unsigned int *f, unsigned int on, unsigned int end)
{
    if (!(*f & end)) {
        if ((*f & on) == on)
            *f ^= on;
        *f |= end;
        return 1;
    }
    return 0;
}
typedef struct { char pad[0x168]; float x168; } GV;
extern GV gcGlobalVar;
extern void _optionWorkSet(int, int);
extern void graphFrameBufferReInitializeRequest(void);
extern void setAspect(int);
extern int *getProgressiveMode(void);
extern void scrRun(void);
extern void SpriteMenuSetDispFlag(void *, int, int);
extern void SpriteMenuSetLayer(void *, int);
extern void SpriteMenuSetSelectMenuId(void *, int);
#define GF(o) (gcGlobalVar.x168)
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

void SCRFuncPoseidonToothMiRTexAnimEnd(void *a)
{
    if (texAnimEnd((unsigned int *)(GetSCRCharaAIWorkPtr(a) + 0x41D4), 4, 8))
        bootTexAlphaAnim(a, D_0017AF40, 0.0f, -0.05f);
}

static void func_00094FE0(void *menu, int *w, int flag, int act)
{
    if (!(flag & 1))
        return;
    switch (w[1]) {
    case 0:
        switch (act) {
        case 1:
            _optionWorkSet(6, 0);
            graphFrameBufferReInitializeRequest();
            setAspect(-1);
            w[0] = 0;
            break;
        case 0:
            if (*getProgressiveMode() != 1) {
                *getProgressiveMode() = 1;
                _optionWorkSet(6, 1);
                graphFrameBufferReInitializeRequest();
                scrRun();
                setAspect(-1);
            }
            SpriteMenuSetDispFlag(menu, 0, 0);
            SpriteMenuSetDispFlag(menu, 1, 1);
            SpriteMenuSetLayer(menu, 1);
            w[1] = 1;
            ((float *)w)[2] = GF(0x168);
            ((float *)w)[3] = GF(0x168);
            break;
        }
        break;
    case 1:
        switch (act) {
        case 0:
            if (*getProgressiveMode() != 0) {
                *getProgressiveMode() = 0;
                _optionWorkSet(6, 0);
                graphFrameBufferReInitializeRequest();
                scrRun();
                setAspect(-1);
            }
            SpriteMenuSetDispFlag(menu, 1, 0);
            SpriteMenuSetDispFlag(menu, 0, 1);
            SpriteMenuSetLayer(menu, 0);
            SpriteMenuSetSelectMenuId(menu, 1);
            w[1] = 0;
            ((float *)w)[3] = GF(0x168) - 3.0f + 1.0f;
            break;
        case 1:
            w[1] = 0;
            w[0] = 0;
            break;
        }
        break;
    }
}

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

    st.start = (*(GcGlobal *)&gcGlobalVar).time - 3.0f;
    while (st.active) {
        ready = 3.0f <= (*(GcGlobal *)&gcGlobalVar).time - st.start;
        if (st.mode == 1 && 15.0f < (*(GcGlobal *)&gcGlobalVar).time - st.t8) {
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
            st.start = (*(GcGlobal *)&gcGlobalVar).time - 3.0f + 1.0f;
        }
        menu->exec(thread, (*(GcGlobal *)&gcGlobalVar).speed, ready | 4, func_00094FE0, &st);
        menu->draw(thread);
        scrRun();
    }
    ScrSpriteParamEnd(&local, 1);
}
