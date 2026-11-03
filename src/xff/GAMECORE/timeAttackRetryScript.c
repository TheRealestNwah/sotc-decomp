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
} TimeAttack;

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
extern TimeAttack g_TimeAttack;
extern const char RO_001807C8[];
extern const char RO_00180740[];
extern void func_000C8730(void);
extern void timeAttackPauseScriptBegin(void);
extern void scriptIntrSignal(int);
extern int ScrIntrDef_TIMEATTACK_RETRY;

static inline int timeAttackRetryCheck(unsigned char *thread, TimeAttack *ta)
{
    switch (ta->state) {
    case 8:
        SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_001807C8)), 0);
        return 1;
    case 2:
        SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_001807C8)), 0);
        timeAttackPauseScriptBegin();
        return 1;
    }
    if (ta->flags & 0x8) {
        ta->flags &= ~0x8;
        SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_001807C8)), 0);
        return 1;
    }
    return 0;
}

void timeAttackRetryScript(SpriteParam *parameters)
{
    SpriteParam local;
    unsigned char *thread;
    SpriteMenu *menu;
    int layer;
    TimeAttack *ta;

    thread = isysGetThisSubThread();
    menu = GetSpriteMenuClass(thread);
    ta = &g_TimeAttack;
    ScrSpriteParamSetup(&local, parameters);
    SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_001807C8)), 1);
    SpriteMenuSetLayer(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_001807C8)));
    layer = MakeStrHashValue(RO_001807C8);
    SpriteMenuSetSelectMenuId(thread, SpriteMenuGetMenuIdByHash(thread, layer, MakeStrHashValue(RO_00180740)));
    while (1) {
        menu->exec(thread, gcGlobalVar.speed, 1, func_000C8730, ta);
        if (timeAttackRetryCheck(thread, ta)) {
            break;
        }
        menu->draw(thread);
        scrRun();
    }
    ScrSpriteParamEnd(&local, 1);
    if (ta->state == 8) {
        scriptIntrSignal(ScrIntrDef_TIMEATTACK_RETRY);
    }
}
