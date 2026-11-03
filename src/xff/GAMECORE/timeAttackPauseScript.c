typedef struct { char c[16]; } SpriteParam;

typedef struct {
    char pad0[0x28];
    void (*exec)(unsigned char *, float, int, void (*)(void), void *);
    void (*draw)(unsigned char *);
} SpriteMenu;

typedef struct {
    int pad0;
    int state;
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
extern void scriptIntrSignal(int);
extern int ScrIntrDef_MENU_CONTINUE;
extern void scrRun(void);
extern GcGlobal gcGlobalVar;
extern TimeAttack g_TimeAttack;
extern const char RO_00180750[];
extern const char RO_00180768[];
extern void func_000C5750(void);
extern int func_000C5880(unsigned char *menu, TimeAttack *ta);

void timeAttackPauseScript(SpriteParam *parameters)
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
    SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180750)), 1);
    SpriteMenuSetLayer(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180750)));
    layer = MakeStrHashValue(RO_00180750);
    SpriteMenuSetSelectMenuId(thread, SpriteMenuGetMenuIdByHash(thread, layer, MakeStrHashValue(RO_00180768)));
    while (menu->exec(thread, gcGlobalVar.speed, 1, func_000C5750, ta), !func_000C5880(thread, ta)) {
        menu->draw(thread);
        scrRun();
    }
    ScrSpriteParamEnd(&local, 1);
    if (ta->state < 3) {
    } else if (ta->state < 5) {
    } else if (ta->state == 9) {
        scriptIntrSignal(ScrIntrDef_MENU_CONTINUE);
    }
}
