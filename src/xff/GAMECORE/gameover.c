typedef struct { char c[16]; } SpriteParam;

typedef struct {
    char pad0[0x28];
    void (*exec)(unsigned char *, float, int, void *, void *);
    void (*draw)(unsigned char *);
} SpriteMenu;

typedef struct { char pad[8]; int tex; } PartsParam;

typedef struct { char pad[0x170]; float speed; char pad2[0x144]; char objs[1]; } GcGlobal;

extern unsigned char *isysGetThisSubThread(void);
extern SpriteMenu *GetSpriteMenuClass(unsigned char *);
extern void ScrSpriteParamSetup(SpriteParam *, void *);
extern void ScrSpriteParamEnd(SpriteParam *, int);
extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern void SpriteMenuSetDispFlag(unsigned char *o, int i, int disp);
extern void SpriteMenuSetLayer(unsigned char *o, int layer);
extern void SpriteMenuSetDefaultSelectMenu(unsigned char *menu, int layer, int id);
extern void SpriteMenuSetPadEventCallback(unsigned char *menu, int layer, void *cb);
extern int SpriteMenuGetLayerStatus(unsigned char *menu, int layer);
extern PartsParam *SpriteMenuGetPartsParamByHashStr(void *, const char *, const char *);
extern int bossStatBootChk(void);
extern void *SCRGetFirstObj(void *);
extern char *SCRGetBossTypeDef(void *);
extern int texSearchMopByName(const char *);
extern void bgmStartGameOver(void);
extern void bgmEndGameOver(void);
extern void fadeOut(int, int, float);
extern int fadeChkStat(int);
extern void gameflowSelectGameoverMenu(int);
extern void scrRun(void);
extern int *DldSysUndefSymbol;
extern GcGlobal gcGlobalVar;
extern int D_0017ABB8;
extern void func_00055308(void *, void *, int, int);
extern void func_00055350(void *, void *, int, int);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

void gameover(void *parameters)
{
    SpriteParam local;
    unsigned char *thread;
    SpriteMenu *menu;
    PartsParam *parts;
    int loop = 1;
    int result = 0;
    int active;

    thread = isysGetThisSubThread();
    menu = GetSpriteMenuClass(thread);
    ScrSpriteParamSetup(&local, parameters);
    parts = SpriteMenuGetPartsParamByHashStr(thread, "GAME_OVER_BG", "GO_BG_sizeaffect");
    if (bossStatBootChk() == 1) {
        char *def = SCRGetBossTypeDef(SCRGetFirstObj(gcGlobalVar.objs));

        parts->tex = 0;
        if (def != 0) {
            char *p = dldResolve((unsigned int *)(def + 0x10));

            if (p != 0)
                parts->tex = *(int *)(p + 0xC);
        }
        if (parts->tex == 0)
            parts->tex = texSearchMopByName("game_over_bg_default");
    } else {
        parts->tex = texSearchMopByName("game_over_bg_default");
    }
    SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue("GAME_OVER_BG")), 1);
    SpriteMenuSetPadEventCallback(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue("GAME_OVER")), func_00055308);
    SpriteMenuSetPadEventCallback(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue("GAME_END_ALERT")), func_00055350);
    SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue("GAME_OVER")), 1);
    SpriteMenuSetLayer(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue("GAME_OVER")));
    SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue("GAME_END_ALERT")), 0);
    SpriteMenuSetDefaultSelectMenu(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue("GAME_OVER")), 0);
    SpriteMenuSetDefaultSelectMenu(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue("GAME_END_ALERT")), 0);
    bgmStartGameOver();
    D_0017ABB8 = 0;
    do {
        active = 0;
        switch (D_0017ABB8) {
        case 0:
        case 5:
            active = 1;
            break;
        default:
            active = 0;
            break;
        case 1:
            active = 0;
            fadeOut(0, 1, 1.0f);
            D_0017ABB8 = 3;
            break;
        case 2:
            active = 0;
            SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue("GAME_END_ALERT")), 1);
            SpriteMenuSetLayer(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue("GAME_END_ALERT")));
            D_0017ABB8 = 4;
            break;
        case 3:
            active = 0;
            if (fadeChkStat(2) != 0) {
                loop = 0;
                result = 0;
            }
            break;
        case 4:
            active = 0;
            if (SpriteMenuGetLayerStatus(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue("GAME_END_ALERT"))) == 3)
                D_0017ABB8 = 5;
            break;
        case 6:
            active = 0;
            fadeOut(0, 1, 1.0f);
            D_0017ABB8 = 8;
            break;
        case 7:
            active = 0;
            SpriteMenuSetDispFlag(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue("GAME_END_ALERT")), 0);
            SpriteMenuSetLayer(thread, SpriteMenuGetLayerNoByHash(thread, MakeStrHashValue("GAME_OVER")));
            D_0017ABB8 = 0;
            break;
        case 8:
            active = 0;
            if (fadeChkStat(2) != 0) {
                bgmEndGameOver();
                loop = 0;
                result = 1;
            }
            break;
        }
        menu->exec(thread, gcGlobalVar.speed, active, 0, 0);
        menu->draw(thread);
        scrRun();
    } while (loop);
    gameflowSelectGameoverMenu(result);
    ScrSpriteParamEnd(&local, 1);
}
