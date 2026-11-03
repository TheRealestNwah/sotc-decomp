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

typedef struct { char pad0[0xC]; int value; } SpritePartsDef;
typedef struct { char pad0[0x14]; int count; char pad18[0xAC]; float normalTime; float hardTime; } BossStatus;
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
extern SpritePartsDef *SpriteMenuGetPartsDefByHash(unsigned char *menu, int layer, int name);
extern BossStatus *time_attack_get_boss_status(void);
extern int getGameHardMode(void);
extern float time_attack_get_best_time(void);
extern const char RO_001808A0[];
extern const char RO_001808C0[];
extern const char RO_001808D8[];
extern const char RO_001808F8[];
extern GcGlobal gcGlobalVar;
extern TimeAttack g_TimeAttack;
extern const char RO_00180720[];
extern const char RO_00180740[];
extern void func_000C8628(void);
extern int SpriteMenuIsFadeCheckAllLayer(unsigned char *);
extern void SpriteMenuSetDispFlagAll(unsigned char *, int);

static inline int timeAttackInCheck(unsigned char *thread, TimeAttack *ta)
{
    switch (ta->state) {
    case 8:
    case 0xD:
        if (!SpriteMenuIsFadeCheckAllLayer(thread)) {
            SpriteMenuSetDispFlagAll(thread, 0);
            return 1;
        }
    }
    if (ta->flags & 0x2) {
        ta->flags &= ~0x2;
        SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180720)), 0);
        return 1;
    }
    return 0;
}

void timeAttackInScript(SpriteParam *parameters)
{
    SpriteParam local;
    unsigned char *thread;
    SpriteMenu *menu;
    int layer;
    TimeAttack *ta;
    BossStatus *boss;
    SpritePartsDef *parts;
    float limit;

    thread = isysGetThisSubThread();
    menu = GetSpriteMenuClass(thread);
    ta = &g_TimeAttack;
    ScrSpriteParamSetup(&local, parameters);
    boss = time_attack_get_boss_status();
    if (getGameHardMode()) {
        limit = boss->hardTime;
    } else {
        limit = boss->normalTime;
    }
    SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180720)), 1);
    SpriteMenuSetLayer(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180720)));
    layer = MakeStrHashValue(RO_00180720);
    SpriteMenuSetSelectMenuId(thread, SpriteMenuGetMenuIdByHash(thread, layer, MakeStrHashValue(RO_00180740)));
    layer = MakeStrHashValue(RO_00180720);
    SpriteMenuGetPartsDefByHash(thread, layer, MakeStrHashValue(RO_001808A0))->value = limit * 100.0f;
    layer = MakeStrHashValue(RO_00180720);
    parts = SpriteMenuGetPartsDefByHash(thread, layer, MakeStrHashValue(RO_001808C0));
    parts->value = time_attack_get_best_time() * 100.0f;
    layer = MakeStrHashValue(RO_00180720);
    SpriteMenuGetPartsDefByHash(thread, layer, MakeStrHashValue(RO_001808D8))->value = boss->count - 1;
    if (time_attack_get_best_time() != 0.0f && time_attack_get_best_time() <= limit) {
        SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_001808F8)), 1);
    }
    while (1) {
        menu->exec(thread, gcGlobalVar.speed, 1, func_000C8628, ta);
        if (timeAttackInCheck(thread, ta)) {
            break;
        }
        menu->draw(thread);
        scrRun();
    }
    ScrSpriteParamEnd(&local, 1);
}
