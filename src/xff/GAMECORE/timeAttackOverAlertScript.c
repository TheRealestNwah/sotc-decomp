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
extern const char RO_001807F0[];
extern const char RO_00180780[];
extern void func_000C8900(void);
extern void func_000C84F8(void);

static inline int timeAttackOverAlertCheck(unsigned char *thread, TimeAttack *ta)
{
    switch (ta->state) {
    case 8:
        SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_001807F0)), 0);
        return 1;
    case 4:
        SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_001807F0)), 0);
        ta->unk18 = 0;
        func_000C84F8();
        return 1;
    }
    if (ta->flags & 0x40) {
        ta->flags &= ~0x40;
        SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_001807F0)), 0);
        return 1;
    }
    return 0;
}

void timeAttackOverAlertScript(SpriteParam *parameters)
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
    SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_001807F0)), 1);
    SpriteMenuSetLayer(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_001807F0)));
    layer = MakeStrHashValue(RO_001807F0);
    SpriteMenuSetSelectMenuId(thread, SpriteMenuGetMenuIdByHash(thread, layer, MakeStrHashValue(RO_00180780)));
    while (1) {
        menu->exec(thread, gcGlobalVar.speed, 1, func_000C8900, ta);
        if (timeAttackOverAlertCheck(thread, ta)) {
            break;
        }
        menu->draw(thread);
        scrRun();
    }
    ScrSpriteParamEnd(&local, 1);
}
