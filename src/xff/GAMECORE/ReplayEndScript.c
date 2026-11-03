typedef struct { char c[16]; } SpriteParam;

typedef struct {
    char pad0[0x28];
    void (*exec)(unsigned char *, float, int, void (*)(void), void *);
    void (*draw)(unsigned char *);
} SpriteMenu;

typedef struct {
    int pad0;
    int state;
} Replay;

typedef struct { char pad[0x170]; float speed; } GcGlobal;

extern void *isysGetThisSubThread(void);
extern SpriteMenu *GetSpriteMenuClass(unsigned char *);
extern void ScrSpriteParamSetup(SpriteParam *, SpriteParam *);
extern void ScrSpriteParamEnd(SpriteParam *, int);
extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern void SpriteMenuSetDispFlag(unsigned char *o, int i, int disp);
extern void SpriteMenuSetLayer(unsigned char *o, int layer);
extern int SpriteMenuGetMenuIdByHash(unsigned char *menu, int layer, int name);
extern void SpriteMenuSetSelectMenuId(unsigned char *menu, int id);
extern void scriptIntrSignal(int);
extern int ScrIntrDef_GAME_CANCEL;
extern void scrRun(void);
extern GcGlobal gcGlobalVar;
extern Replay g_Replay;
extern const char RO_001809F8[];
extern const char RO_00180970[];
extern void func_000C8EC0(void);
extern int func_000C72E0(unsigned char *menu, Replay *rp);

void ReplayEndScript(SpriteParam *parameters)
{
    SpriteParam local;
    unsigned char *thread;
    SpriteMenu *menu;
    int layer;
    Replay *rp;

    thread = isysGetThisSubThread();
    menu = GetSpriteMenuClass(thread);
    rp = &g_Replay;
    ScrSpriteParamSetup(&local, parameters);
    SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_001809F8)), 1);
    SpriteMenuSetLayer(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_001809F8)));
    layer = MakeStrHashValue(RO_001809F8);
    SpriteMenuSetSelectMenuId(thread, SpriteMenuGetMenuIdByHash(thread, layer, MakeStrHashValue(RO_00180970)));
    while (menu->exec(thread, gcGlobalVar.speed, 1, func_000C8EC0, rp), !func_000C72E0(thread, rp)) {
        menu->draw(thread);
        scrRun();
    }
    ScrSpriteParamEnd(&local, 1);
    if (rp->state == 0xB)
        scriptIntrSignal(ScrIntrDef_GAME_CANCEL);
}
