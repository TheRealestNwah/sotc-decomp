typedef struct { char c[16]; } SpriteParam;

typedef struct {
    char pad0[0x28];
    void (*exec)(unsigned char *, float, int, void (*)(void), void *);
    void (*draw)(unsigned char *);
} SpriteMenu;

typedef struct {
    int pad0;
    int state;
    int busy;
    int flags;
    int pad10[2];
    int unk18;
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
extern const char RO_00180950[];
extern const char RO_00180970[];
extern void func_000C8CD8(void);
extern int SpriteMenuIsFadeCheckAllLayer(unsigned char *);
extern void SpriteMenuSetDispFlagAll(unsigned char *, int);

static inline int ReplayInCheck(unsigned char *thread, Replay *rp)
{
    switch (rp->state) {
    case 8:
    case 0xD:
        if (!SpriteMenuIsFadeCheckAllLayer(thread)) {
            SpriteMenuSetDispFlagAll(thread, 0);
            return 1;
        }
    }
    if (rp->flags & 0x2) {
        rp->flags &= ~0x2;
        SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180950)), 0);
        return 1;
    }
    return 0;
}

void ReplayInScript(SpriteParam *parameters)
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
    SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180950)), 1);
    SpriteMenuSetLayer(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180950)));
    layer = MakeStrHashValue(RO_00180950);
    SpriteMenuSetSelectMenuId(thread, SpriteMenuGetMenuIdByHash(thread, layer, MakeStrHashValue(RO_00180970)));
    while (1) {
        menu->exec(thread, gcGlobalVar.speed, 1, func_000C8CD8, rp);
        if (ReplayInCheck(thread, rp)) {
            break;
        }
        menu->draw(thread);
        scrRun();
    }
    ScrSpriteParamEnd(&local, 1);
}
