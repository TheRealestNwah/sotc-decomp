typedef struct { char c[16]; } SpriteParam;

typedef struct {
    char pad0[0x28];
    void (*exec)(unsigned char *, float, int, void (*)(void), void *);
    void (*draw)(unsigned char *);
} SpriteMenu;

typedef struct {
    unsigned char *thread;
    int state;
    int busy;
    int flags;
    int pad10[3];
    int layerIdx;
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
extern void scrRun(void);
extern GcGlobal gcGlobalVar;
extern Replay g_Replay;
extern const char *g_strReplayPauseLayerDef[];
extern const char RO_001809A0[];
extern void func_000C6DC8(void);
extern int func_000C7080(unsigned char *, Replay *);
extern void scriptIntrSignal(int);
extern int ScrIntrDef_MENU_CONTINUE;

void ReplayPauseScript(SpriteParam *parameters)
{
    SpriteParam local;
    unsigned char *thread;
    SpriteMenu *menu;
    int layer;
    Replay *rp;
    const char *name;

    thread = isysGetThisSubThread();
    menu = GetSpriteMenuClass(thread);
    rp = &g_Replay;
    name = g_strReplayPauseLayerDef[g_Replay.layerIdx];
    ScrSpriteParamSetup(&local, parameters);
    rp->thread = thread;
    SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(name)), 1);
    SpriteMenuSetLayer(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(name)));
    layer = MakeStrHashValue(name);
    SpriteMenuSetSelectMenuId(thread, SpriteMenuGetMenuIdByHash(thread, layer, MakeStrHashValue(RO_001809A0)));
    while (1) {
        menu->exec(thread, gcGlobalVar.speed, 1, func_000C6DC8, rp);
        if (func_000C7080(thread, rp)) {
            break;
        }
        menu->draw(thread);
        scrRun();
    }
    ScrSpriteParamEnd(&local, 1);
    switch (rp->state) {
    case 3:
    case 4:
        break;
    case 9:
        scriptIntrSignal(ScrIntrDef_MENU_CONTINUE);
        break;
    }
}
