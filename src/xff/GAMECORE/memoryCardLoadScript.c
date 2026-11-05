typedef struct { char c[16]; } SpriteParam;

typedef struct {
    char pad0[0x28];
    void (*exec)(unsigned char *, float, int, void *, void *);
    void (*draw)(unsigned char *);
} SpriteMenu;

typedef struct {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
    int x14;
    int x18;
    int x1C;
    int x20;
    int x24;
    int x28;
    int x2C;
    int x30;
} McWork;

typedef struct { char pad[0x170]; float speed; } GcGlobal;

extern unsigned char *isysGetThisSubThread(void);
extern SpriteMenu *GetSpriteMenuClass(unsigned char *);
extern void ScrSpriteParamSetup(SpriteParam *, SpriteParam *);
extern void ScrSpriteParamEnd(SpriteParam *, int);
extern void PauseGame(int);
extern void ReleaseGame(int);
extern void SpriteMenuSetLayerPriorityAllLayer(unsigned char *, int);
extern int SpriteMenuIsFadeCheckAllLayer(unsigned char *);
extern void scrRun(void);
extern long *gStatGetOmakeStatAdrs(void);
extern void setNowLoadingMessageDisplayFlag(int);
extern void fadeOut(float, int, int);
extern void LoadWaitCancel(int);
extern void func_00068020(void);
extern int func_000685E0(unsigned char *, SpriteMenu *, McWork *);
extern GcGlobal gcGlobalVar;
extern McWork B_0018AF98;
extern int D_0017AD18;

void memoryCardLoadScript(SpriteParam *parameters)
{
    SpriteParam local;
    unsigned char *thread;
    SpriteMenu *menu;
    int done;

    thread = isysGetThisSubThread();
    menu = GetSpriteMenuClass(thread);
    ScrSpriteParamSetup(&local, parameters);
    D_0017AD18 = 1;
    B_0018AF98.x0 = 0;
    B_0018AF98.x4 = 0;
    B_0018AF98.xC = -1;
    B_0018AF98.x8 = -1;
    B_0018AF98.x10 = 0;
    B_0018AF98.x14 = 0;
    B_0018AF98.x1C = 0;
    B_0018AF98.x20 = 0;
    B_0018AF98.x24 = -1;
    B_0018AF98.x28 = -1;
    B_0018AF98.x30 = 0;
    PauseGame(1);
    SpriteMenuSetLayerPriorityAllLayer(thread, 4);
    do {
        func_00068020();
        done = func_000685E0(thread, menu, &B_0018AF98);
        menu->exec(thread, gcGlobalVar.speed, 1, 0, 0);
        menu->draw(thread);
        scrRun();
    } while (!done);
    if (B_0018AF98.x20 != 0) {
        while (SpriteMenuIsFadeCheckAllLayer(thread)) {
            menu->exec(thread, gcGlobalVar.speed, 0, 0, 0);
            menu->draw(thread);
            scrRun();
        }
        ScrSpriteParamEnd(&local, B_0018AF98.x20);
        if ((int)(*gStatGetOmakeStatAdrs() >> 8) & 1) {
            setNowLoadingMessageDisplayFlag(1);
            fadeOut(1.0f, 1, 0);
            LoadWaitCancel(0);
        } else {
            LoadWaitCancel(1);
        }
    } else {
        ScrSpriteParamEnd(&local, 0);
        LoadWaitCancel(0);
    }
    ReleaseGame(1);
}
