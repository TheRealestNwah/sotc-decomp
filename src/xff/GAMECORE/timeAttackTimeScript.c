typedef struct { char c[16]; } SpriteParam;

typedef struct {
    char pad0[0x28];
    void (*exec)(unsigned char *, int, void (*)(void), void *, float);
    void (*draw)(unsigned char *);
} SpriteMenu;

typedef struct {
    char pad0[0xC];
    int value;
} SpritePartsDef;

typedef struct {
    int pad0[5];
    float time;
} TimeAttack;

typedef struct { char pad[0x180]; float speed; } GcGlobal;

extern void *isysGetThisSubThread(void);
extern SpriteMenu *GetSpriteMenuClass(unsigned char *);
extern void ScrSpriteParamSetup(SpriteParam *, SpriteParam *);
extern void ScrSpriteParamEnd(SpriteParam *, int);
extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern SpritePartsDef *SpriteMenuGetPartsDefByHash(unsigned char *menu, int layer, int name);
extern void SpriteMenuSetDispFlag(unsigned char *o, int i, int disp);
extern void scrRun(void);
extern GcGlobal gcGlobalVar;
extern TimeAttack g_TimeAttack;
extern const char RO_00180850[];
extern const char RO_00180868[];
extern const char RO_00180888[];
extern int func_000C5B78(unsigned char *menu, TimeAttack *ta, int *state);

void timeAttackTimeScript(SpriteParam *parameters)
{
    SpriteParam local;
    int state;
    unsigned char *thread;
    SpriteMenu *menu;
    int layer;
    TimeAttack *ta;

    thread = isysGetThisSubThread();
    menu = GetSpriteMenuClass(thread);
    state = 0;
    ta = &g_TimeAttack;
    ScrSpriteParamSetup(&local, parameters);
    layer = MakeStrHashValue(RO_00180850);
    SpriteMenuGetPartsDefByHash(thread, layer, MakeStrHashValue(RO_00180868))->value = 0;
    layer = MakeStrHashValue(RO_00180850);
    SpriteMenuGetPartsDefByHash(thread, layer, MakeStrHashValue(RO_00180888))->value = ta->time * 100.0f;
    SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue(RO_00180850)), 1);
    while (menu->exec(thread, 1, 0, ta, gcGlobalVar.speed), !func_000C5B78(thread, ta, &state)) {
        menu->draw(thread);
        scrRun();
    }
    ScrSpriteParamEnd(&local, 1);
}
