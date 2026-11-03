typedef struct { int pad0[2]; float *time; int pad1; } SpriteParam;

typedef struct {
    char pad0[0x28];
    void (*exec)(unsigned char *, float, int, void (*)(void), void *);
    void (*draw)(unsigned char *);
} SpriteMenu;

typedef struct { char pad[0x168]; float time; int pad16C; float speed; } GcGlobal;

extern void *isysGetThisSubThread(void);
extern SpriteMenu *GetSpriteMenuClass(unsigned char *);
extern void ScrSpriteParamSetup(SpriteParam *, SpriteParam *);
extern void ScrSpriteParamEnd(SpriteParam *, int);
extern void SpriteMenuSetDispFlagAll(unsigned char *, int);
extern void SpriteMenuSetLayer(unsigned char *o, int layer);
extern int SpriteMenuIsFadeCheckAllLayer(unsigned char *);
extern void scrRun(void);
extern GcGlobal gcGlobalVar;
extern void func_00051AB8(void);

void EndMessageScript(SpriteParam *parameters)
{
    SpriteParam local;
    int running;
    unsigned char *thread;
    SpriteMenu *menu;
    GcGlobal *g;
    float start;
    float time;

    thread = isysGetThisSubThread();
    menu = GetSpriteMenuClass(thread);
    g = &gcGlobalVar;
    running = 1;
    start = g->time;
    ScrSpriteParamSetup(&local, parameters);
    time = *local.time;
    SpriteMenuSetDispFlagAll(thread, 1);
    SpriteMenuSetLayer(thread, 0);
    while (running) {
        if (time > 0.0f) {
            if (time <= gcGlobalVar.time - start) {
                running = 0;
            }
        }
        menu->exec(thread, gcGlobalVar.speed, time <= 0.0f, func_00051AB8, &running);
        menu->draw(thread);
        scrRun();
    }
    SpriteMenuSetDispFlagAll(thread, 0);
    while (SpriteMenuIsFadeCheckAllLayer(thread)) {
        menu->exec(thread, gcGlobalVar.speed, 0, 0, 0);
        menu->draw(thread);
        scrRun();
    }
    ScrSpriteParamEnd(&local, 1);
}
