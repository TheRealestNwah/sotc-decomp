typedef struct { int pad0; int *active; int pad8[2]; } SpriteParam;
typedef struct {
    char pad0[4];
    void *layout;
    char pad8[0x20];
    void (*exec)(unsigned char *, float, int, void (*)(void), void *);
} SpriteMenu;
typedef struct { char pad[0x180]; float dt; } GcGlobal;
typedef struct { float a; int b; float c; int state; } DispSw;
typedef struct {
    float hp;
    float hp_shown;
    float hp_target;
    int timer;
} BossLifeBar;

extern unsigned char *isysGetThisSubThread(void);
extern SpriteMenu *GetSpriteMenuClass(unsigned char *);
extern void ScrSpriteParamSetup(SpriteParam *, SpriteParam *);
extern float getDemoBarFade(void);
extern float getFadeValue(void);
extern int bossStatBootChk(void);
extern void SpriteMenuSetDispFlag(unsigned char *, int, int);
extern void scrRun(void);
extern GcGlobal gcGlobalVar;
extern DispSw B_0019CCD0[];
extern BossLifeBar D_0017B050;
extern int D_0017AFE8;
extern int D_0017AFEC;
extern int D_0017B060;
extern void func_000BFD78(void *, float);

void bosslifebar_script(SpriteParam *parameters)
{
    SpriteParam local;
    unsigned char *thread;
    SpriteMenu *menu;
    void *layout;
    GcGlobal *g;
    int disp;
    int i;

    thread = isysGetThisSubThread();
    menu = GetSpriteMenuClass(thread);
    layout = menu->layout;
    ScrSpriteParamSetup(&local, parameters);
    while (*local.active) {
        if (!(getDemoBarFade() == 1.0f && getFadeValue() == 0.0f) && D_0017AFEC == 0) {
            for (i = 0; i < 4; i++) {
                B_0019CCD0[i].b = 0;
                B_0019CCD0[i].state = 0;
                B_0019CCD0[i].c = 0;
                B_0019CCD0[i].a = 0;
            }
        }
        disp = 0;
        if (D_0017AFE8 != 0 && 0.0f < D_0017B050.hp_target) {
            disp = bossStatBootChk() == 1;
        }
        g = &gcGlobalVar;
        SpriteMenuSetDispFlag(thread, 0, disp);
        menu->exec(thread, g->dt, 0, 0, 0);
        D_0017B060 = 0;
        if (bossStatBootChk() == 1 && D_0017AFE8 != 0) {
            func_000BFD78(layout, g->dt);
        }
        scrRun();
    }
}
