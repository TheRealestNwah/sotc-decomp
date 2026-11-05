typedef struct { int pad0; int *active; int pad8[2]; } SpriteParam;
typedef struct {
    char pad0[4];
    void *layout;
    char pad8[0x20];
    void (*exec)(unsigned char *, float, int, void (*)(void), void *);
} SpriteMenu;
typedef struct { char pad[0x180]; float dt; } GcGlobal;
typedef struct { float a; int b; float c; int state; } DispSw;
typedef struct { float cur; float prev; float target; float speed; } LifeBar;

extern unsigned char *isysGetThisSubThread(void);
extern SpriteMenu *GetSpriteMenuClass(unsigned char *);
extern void ScrSpriteParamSetup(SpriteParam *, SpriteParam *);
extern float getDemoBarFade(void);
extern float getFadeValue(void);
extern void SpriteMenuSetDispFlag(unsigned char *, int, int);
extern void scrRun(void);
extern GcGlobal gcGlobalVar;
extern DispSw B_0019CCD0[];
extern LifeBar D_0017B030;
extern int B_0019CD28;
extern int B_0019CD10;
extern int B_0019CD40;
extern int B_0019CD44;
extern int D_0017AFE8;
extern int D_0017AFEC;
extern int D_0017B040;
extern void func_000BCA80(float);
extern void func_000BED28(void *, float);
extern void func_000BEB28(float);

void playerlifebar_script(SpriteParam *parameters)
{
    SpriteParam local;
    unsigned char *thread;
    SpriteMenu *menu;
    void *layout;
    GcGlobal *g;
    int i;

    thread = isysGetThisSubThread();
    menu = GetSpriteMenuClass(thread);
    layout = menu->layout;
    ScrSpriteParamSetup(&local, parameters);
    D_0017B030.target = 1.0f;
    D_0017B030.prev = 1.0f;
    D_0017B030.cur = 1.0f;
    D_0017B030.speed = 0.0f;
    B_0019CD10 = 0;
    B_0019CD28 = 0;
    B_0019CD40 = 0;
    B_0019CD44 = 0;
    while (*local.active) {
        if (!(getDemoBarFade() == 1.0f && getFadeValue() == 0.0f) && D_0017AFEC == 0) {
            for (i = 0; i < 4; i++) {
                B_0019CCD0[i].b = 0;
                B_0019CCD0[i].state = 0;
                B_0019CCD0[i].c = 0;
                B_0019CCD0[i].a = 0;
            }
        }
        g = &gcGlobalVar;
        SpriteMenuSetDispFlag(thread, 0, D_0017AFE8);
        func_000BCA80(g->dt);
        menu->exec(thread, g->dt, 1, 0, 0);
        D_0017B040 = 0;
        if (D_0017AFE8 != 0) {
            func_000BED28(layout, g->dt);
            func_000BEB28(g->dt);
        }
        scrRun();
    }
}
