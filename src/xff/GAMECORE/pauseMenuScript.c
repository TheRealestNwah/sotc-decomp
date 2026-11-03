typedef struct { int pad0[2]; int arg; int padC; } SpriteParam;
typedef struct { char pad0[0x28]; void (*exec)(unsigned char *, float, int, void (*)(void), void *); void (*draw)(unsigned char *); } SpriteMenu;
typedef struct { char pad[0x170]; float speed; } GcGlobal;
typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    int arg;
} PauseMenu;

extern unsigned char *isysGetThisSubThread(void);
extern SpriteMenu *GetSpriteMenuClass(unsigned char *);
extern void ScrSpriteParamSetup(SpriteParam *, SpriteParam *);
extern void ScrSpriteParamEnd(SpriteParam *, int);
extern int getGameClearCnt(void);
extern int GetNumOmakeItem(void);
extern int MakeStrHashValue(char *);
extern int SpriteMenuGetLayerNoByHash(unsigned char *, int);
extern void SpriteMenuSetDispFlag(unsigned char *, int, int);
extern void SpriteMenuSetLayer(unsigned char *, int);
extern void scrRun(void);
extern GcGlobal gcGlobalVar;
extern char RO_0017E1B0[];
extern char RO_0017E1C8[];
extern int func_00075210(unsigned char *, SpriteMenu *, PauseMenu *);
extern void func_000755C8(void);

static inline int pauseMenuGetLayer(unsigned char *thread)
{
    if (getGameClearCnt() > 0 && GetNumOmakeItem() > 0) {
        return SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_0017E1B0));
    }
    return SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_0017E1C8));
}

void pauseMenuScript(SpriteParam *parameters)
{
    PauseMenu pm;
    SpriteParam local;
    unsigned char *thread;
    SpriteMenu *menu;

    thread = isysGetThisSubThread();
    menu = GetSpriteMenuClass(thread);
    ScrSpriteParamSetup(&local, parameters);
    SpriteMenuSetDispFlag(thread, pauseMenuGetLayer(thread), 1);
    SpriteMenuSetLayer(thread, pauseMenuGetLayer(thread));
    pm.unk8 = 1;
    pm.unk0 = 1;
    pm.unk4 = 1;
    pm.unkC = 0;
    pm.arg = local.arg;
    while (!func_00075210(thread, menu, &pm)) {
        menu->exec(thread, gcGlobalVar.speed, pm.unk8 ? pm.unk4 : 0, func_000755C8, &pm);
        menu->draw(thread);
        scrRun();
    }
    ScrSpriteParamEnd(&local, 1);
}
