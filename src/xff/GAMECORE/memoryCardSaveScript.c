typedef struct { char c[16]; } SpriteParam;

typedef struct {
    char pad0[0x28];
    void (*exec)(unsigned char *, float, int, int, int);
    void (*draw)(unsigned char *);
} SpriteMenu;

typedef struct {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
    int x14;
    int x18;
    int x1C;
    int x20;
    int x24;
    int x28;
    int x2C;
    int x30;
    char pad34[0x700 - 0x34];
    signed char *x700;
} McWork;

typedef struct { char pad[0x170]; float speed; } GcGlobal;

typedef struct { float x, y, z, w; } __attribute__((aligned(16))) VECTOR;
typedef struct { float x, y, z; } ROT;

typedef struct {
    signed char area;
    signed char b1;
    signed char mode;
    char pad3[0x14 - 3];
    float px, py, pz;
    float pry;
    float hx, hy, hz;
    float hry;
} SavePoint;

extern unsigned char *isysGetThisSubThread(void);
extern SpriteMenu *GetSpriteMenuClass(unsigned char *);
extern void ScrSpriteParamSetup(SpriteParam *, SpriteParam *);
extern void ScrSpriteParamEnd(SpriteParam *, int);
extern void controllerAlertDisable(int);
extern void _gameFlagSet(int);
extern int _gameFlagChk(int);
extern void _gameFlagCls(int);
extern int getClearGameHotStartFlag(void);
extern SavePoint *gStatPlaceIdToSavePoint(int);
extern void gStatCheckPointSave(void);
extern void gStatChekcPointSaveHookPlayerHorsePos(VECTOR *, ROT *, VECTOR *, ROT *, int);
extern void YattsukeGetSeamlessAreaCenter(VECTOR *, int);
extern void *memset(void *, int, unsigned int);
extern void gameModeSet(int);
extern void gameModeCls(int);
extern void scrRun(void);
extern void *SCRGetFirstObj(void *);
extern void CharaCtrlSetOutsideScriptCtrlStatus(void *, int);
extern int func_000661D0(unsigned char *, SpriteMenu *, McWork *);
extern char *ScriptCtrlDef_SCRPlayerPrayEnd;
extern GcGlobal gcGlobalVar;
extern McWork B_0018AF98;
extern int D_0017AD10;
extern int vschedGameTimeExec;

static inline void vecAddXYZ(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

/* Save-script menu: the menu state stores keep their source order, and the
   script pointer from local.c + 8 is read into a temporary first so gcc
   schedules its load ahead of the global address setup. */
void memoryCardSaveScript(SpriteParam *parameters)
{
    SpriteParam local;
    VECTOR center;
    VECTOR ppos;
    VECTOR a;
    ROT b;
    VECTOR hpos;
    VECTOR c;
    unsigned char *thread;
    SpriteMenu *menu;
    int wasExec;
    int place;
    SavePoint *sp;
    int mode;

    thread = isysGetThisSubThread();
    menu = GetSpriteMenuClass(thread);
    wasExec = vschedGameTimeExec != 0;
    controllerAlertDisable(1);
    ScrSpriteParamSetup(&local, parameters);
    if (wasExec)
        vschedGameTimeExec = 0;
    {
    signed char *x7 = *(signed char **)(local.c + 8);
    D_0017AD10 = 1;
    B_0018AF98.x0 = 0;
    B_0018AF98.x4 = 0;
    B_0018AF98.xC = -1;
    B_0018AF98.x8 = -1;
    B_0018AF98.x10 = 0;
    B_0018AF98.x14 = 0;
    B_0018AF98.x1C = 0;
    B_0018AF98.x20 = 0;
    B_0018AF98.x24 = -1;
    B_0018AF98.x28 = -1;
    B_0018AF98.x30 = 0;
    B_0018AF98.x700 = x7;
    }
    if (B_0018AF98.x700 != 0) {
        if (*(int *)(B_0018AF98.x700 + 4) != 0)
            _gameFlagSet(*(int *)(B_0018AF98.x700 + 4));
    }
    place = B_0018AF98.x700 != 0 ? B_0018AF98.x700[1] : 99;
    if (place != 99 && !_gameFlagChk(0x1B) && !getClearGameHotStartFlag())
        _gameFlagSet(0x1A);
    if (B_0018AF98.x700 != 0) {
        sp = gStatPlaceIdToSavePoint(place);
        if (sp != 0 && !(sp->px == 0.0f && sp->py == 0.0f && sp->pz == 0.0f)) {
            memset(&a, 0, sizeof(a));
            a.x = -sp->px;
            a.y = sp->py;
            a.z = -sp->pz;
            ppos = a;
            b.x = 0.0f;
            b.y = sp->pry;
            b.z = 0.0f;
            *(ROT *)&a = b;
            memset(&c, 0, sizeof(c));
            c.x = -sp->hx;
            c.y = sp->hy;
            c.z = -sp->hz;
            hpos = c;
            ((ROT *)&c)->x = 0.0f;
            ((ROT *)&c)->y = sp->hry;
            ((ROT *)&c)->z = 0.0f;
            b = *(ROT *)&c;
            mode = 1;
            if (_gameFlagChk(0x1B) == 0)
                mode = sp->mode;
            YattsukeGetSeamlessAreaCenter(&center, sp->area);
            vecAddXYZ(&ppos, &center, &ppos);
            vecAddXYZ(&hpos, &center, &hpos);
            gStatChekcPointSaveHookPlayerHorsePos(&ppos, (ROT *)&a, &hpos, &b, mode);
        } else {
            gStatCheckPointSave();
        }
    }
    _gameFlagCls(0x1A);
    gameModeSet(1);
    while (!func_000661D0(thread, menu, &B_0018AF98)) {
        menu->exec(thread, gcGlobalVar.speed, 1, 0, 0);
        menu->draw(thread);
        scrRun();
    }
    gameModeCls(1);
    CharaCtrlSetOutsideScriptCtrlStatus(SCRGetFirstObj((char *)&gcGlobalVar + 0x2B0), *(int *)(ScriptCtrlDef_SCRPlayerPrayEnd + 4));
    if (wasExec)
        vschedGameTimeExec = 1;
    ScrSpriteParamEnd(&local, 1);
    controllerAlertDisable(0);
}
