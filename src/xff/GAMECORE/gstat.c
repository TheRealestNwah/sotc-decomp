#include "gamecore/gstat.h"

extern int __gameMode;
extern int gstatTimeAttackMode;
extern int vschedGameTime;
extern int DldSysUndefSymbol;
extern char rootPtn[];
extern char gcGlobalVar[];
extern int SH_HorseTypeDEFAULT[];
extern SavePointList SH_SavePointDEFAULT;
extern unsigned char B_00184890[];
extern unsigned char B_001848B0[];
extern unsigned char B_001884D0[];
extern Accessory B_00188540;
extern char B_00188550[];
extern Accessory D_0017A200[];
extern Accessory D_0017A250[];
extern Accessory D_0017A240[];
extern int D_0017A280;
extern int D_0017A284;
extern int D_0017A288;
extern Accessory *D_0017A28C;
extern Accessory *D_0017A290;
extern int D_0017A294;
extern int D_0017A298;
extern int D_0017A2A0;

extern void *memset(void *, int, unsigned int);
extern void *memcpy(void *, const void *, unsigned int);
extern void _gameFlagSet(int);
extern void _gameFlagCls(int);
extern int _gameFlagChk(int);
extern int _omakeSelectFlagChk(int);
extern void _omakeSelectFlagSet(int);
extern void _omakeSelectFlagCls(int);
extern int getHorseStandByMode(void);
extern void gameFlagCheckPointSave(void *, void *, void *, void *, void *, void *);
extern void gameFlagCheckPointLoad(void *, void *, void *, void *, void *, void *);
extern void backStageCheckPointSave(void *);
extern void backStageCheckPointLoad(void *);
extern void *getSprLogWorkAddress(void);
extern int getSprLogWorkSize(void);
extern void *getSprLogStatusAddress(void);
extern int getSprLogStatusSize(void);
extern void *SCRGetFirstObj(void *);
extern void gameflowSetJumpSekiban(int);
extern int getGameHardMode(void);
extern void SetDamageClassDamageTableType(int);
extern char *bossStatGetActiveBoss(void);
extern void stagemanager_loadstagecore(void *, int, int, int);
extern void stagemanager_unloadstagecore(int);
extern void stagemanager_restartstagecore(void *, int, int, int);
extern int stagemanager_getSegmentVariation(void);
extern void nico_hydePlayerByMagireManteau(void *, int);
extern void SaveLayoutObjGroupAllGeo(void);
extern char *GetLayoutClass(void *);
extern void backStageGobjSaveWithPos(void *, void *, void *);
extern void iosGetClock(long *);
extern int getSavedPlaceId(void);
extern int mcWrite(int, void *, int);
extern int mcRead(int, void *, int);
extern void setSavedClock(void *);
extern void setSavedGameTime(int);
extern void SetTimeAttackTimeFlag(int);
extern void omakeStatInit(int, void *, int);
extern void gameFlagInit(void);
extern void bossStatInit(void);
extern void backStageInit(void);
extern void time_attack_init_gstat_adrs(void);


void gameModeInit(void)
{
    __gameMode = 0;
    memset(B_00184890, 0, 0x20);
}

static void func_00018E00(int var, int flag)
{
    unsigned char *b;

    if (gstatTimeAttackMode != 0)
        return;
    if (flag == 0)
        _gameFlagSet(0x1C);
    else
        _gameFlagCls(0x1C);
    if (getHorseStandByMode())
        _gameFlagSet(0x1E);
    else
        _gameFlagCls(0x1E);
    b = B_001848B0;
    gameFlagCheckPointSave(b, b + 0x64, b + 0x1F4, b + 0x384, b + 0x6A4, b + 0x3C20);
    backStageCheckPointSave(b + 0x9C4);
    {
        unsigned char *d1 = b + 0xC10;
        void *s1 = getSprLogWorkAddress();
        memcpy(d1, s1, getSprLogWorkSize());
    }
    {
        unsigned char *d2 = b + 0x3C10;
        void *s2 = getSprLogStatusAddress();
        memcpy(d2, s2, getSprLogStatusSize());
    }
    b[0x3C1C] = var;
}

int gStatCheckPointLoad(void)
{
    unsigned char *b = B_001848B0;
    unsigned char *work = b + 0xC10;
    unsigned char *status = b + 0x3C10;

    gameFlagCheckPointLoad(b, b + 0x64, b + 0x1F4, b + 0x384, b + 0x6A4, b + 0x3C20);
    backStageCheckPointLoad(b + 0x9C4);
    {
        void *w = getSprLogWorkAddress();

        memcpy(w, work, getSprLogWorkSize());
    }
    {
        void *st = getSprLogStatusAddress();

        memcpy(st, status, getSprLogStatusSize());
    }
    if (_gameFlagChk(0x1C)) {
        if (SCRGetFirstObj(gcGlobalVar + 0x2B4) != 0)
            gStatUnloadHorseChara();
    } else if (_gameFlagChk(0x1E)) {
        gameflowSetJumpSekiban(1);
    }
    SetDamageClassDamageTableType(getGameHardMode());
    return B_001848B0[0x3C1C];
}

static inline void changeCore(int old, int id)
{
    if (old != 0) {
        if (id == old)
            return;
        stagemanager_unloadstagecore(old);
    }
    if (id != 0)
        stagemanager_loadstagecore(rootPtn, id, -1, 0);
}

static inline void setCore(int *slot, int id)
{
    if (id != *slot) {
        if (*slot != 0)
            stagemanager_unloadstagecore(*slot);
        if (id != 0)
            stagemanager_loadstagecore(rootPtn, id, -1, 0);
        *slot = id;
    }
}

void gStatLoadPlayerAccessories(void)
{
    char *boss = bossStatGetActiveBoss();
    Accessory *a;
    Accessory *b;
    Accessory *sel;

    for (a = D_0017A200; a->flag != 0; a++) {
        if (_omakeSelectFlagChk(a->flag))
            break;
    }
    for (b = D_0017A250; b->flag != 0; b++) {
        if (_omakeSelectFlagChk(b->flag)) {
            sel = b;
            goto found;
        }
    }
    if (boss != 0)
        b->id = *(int *)(boss + 0xB0);
    else
        b->id = 0xB9;
    sel = b;
found:
    changeCore(D_0017A28C->id, a->id);
    D_0017A28C = a;
    changeCore(D_0017A290 != 0 ? D_0017A290->id : 0, b->id);
    B_00188540 = *sel;
    D_0017A290 = &B_00188540;
    setCore(&D_0017A284, boss != 0 ? *(int *)(boss + 0xA8) : 0xB8);
    setCore(&D_0017A288, boss != 0 ? *(int *)(boss + 0xAC) : 0xB7);
    nico_hydePlayerByMagireManteau(SCRGetFirstObj(gcGlobalVar + 0x2B0), _omakeSelectFlagChk(7) != 0);
}

void gStatRestartPlayerChara(void)
{
    void *p;

    if (D_0017A280 != 0)
        stagemanager_restartstagecore(rootPtn, D_0017A280, -1, 0);
    if (D_0017A284 != 0)
        stagemanager_restartstagecore(rootPtn, D_0017A284, -1, 0);
    if (D_0017A288 != 0)
        stagemanager_restartstagecore(rootPtn, D_0017A288, -1, 0);
    if (D_0017A28C->id != 0)
        stagemanager_restartstagecore(rootPtn, D_0017A28C->id, -1, 0);
    if (D_0017A290->id != 0)
        stagemanager_restartstagecore(rootPtn, D_0017A290->id, -1, 0);
    if (D_0017A280 != 0) {
        p = SCRGetFirstObj(gcGlobalVar + 0x2B0);
        nico_hydePlayerByMagireManteau(p, _omakeSelectFlagChk(7) != 0);
    }
}

/* Selected horse type; this shape (base + 1 before the loop) returns ->core. */
static inline HorseType *getHorseType(void)
{
    HorseType *base = (HorseType *)SH_HorseTypeDEFAULT[4];
    int n = SH_HorseTypeDEFAULT[3];
    HorseType *e = base + 1;
    int i;

    n--;
    for (i = 0; i < n; i++, e++) {
        if (_omakeSelectFlagChk(e->flag))
            return e;
    }
    return base;
}

static inline void loadHorseChara(int arg)
{
    int core = getHorseType()->core;

    if (D_0017A294 != 0) {
        if (core == D_0017A294)
            goto done;
        stagemanager_unloadstagecore(D_0017A294);
    }
    if (core != 0)
        stagemanager_loadstagecore(rootPtn, core, arg, 0);
done:
    D_0017A294 = getHorseType()->core;
}

void gStatReloadHorseChara(void)
{
    gStatRestartHorseChara();
    if (getHorseType()->core != D_0017A294)
        loadHorseChara(-1);
}

void gStatCheckPointSave(void)
{
    int variation;
    void *horse;

    variation = stagemanager_getSegmentVariation();
    horse = SCRGetFirstObj(gcGlobalVar + 0x2B4);
    SaveLayoutObjGroupAllGeo();
    func_00018E00(variation, horse != 0);
}

void gStatChekcPointSaveHookPlayerHorsePos(void *ppos, void *pdir, void *hpos, void *hdir, int arg)
{
    void *player = SCRGetFirstObj(gcGlobalVar + 0x2B0);
    void *horse = SCRGetFirstObj(gcGlobalVar + 0x2B4);

    SaveLayoutObjGroupAllGeo();
    backStageGobjSaveWithPos(*(void **)(GetLayoutClass(player) + 0x1A4), ppos, pdir);
    if (horse != 0 && hpos != 0)
        backStageGobjSaveWithPos(*(void **)(GetLayoutClass(horse) + 0x1A4), hpos, hdir);
    func_00018E00(arg, horse != 0);
}

void gStatOmakeSave(void)
{
    gameFlagCheckPointSave(0, 0, 0, 0, 0, B_001884D0);
}

SavePoint *gStatPlaceIdToSavePoint(int place)
{
    int i = 0;
    int n = SH_SavePointDEFAULT.n;
    SavePoint *s = SH_SavePointDEFAULT.list;
    for (; i < n; i++, s++) {
        if (s->place == place)
            return s;
    }
    return 0;
}

int gStatMcSave(int port)
{
    long clk;
    int t = vschedGameTime;
    int r;

    iosGetClock(&clk);
    B_001848B0[0x3C20] = getSavedPlaceId();
    *(long *)(B_001848B0 + 0x3C48) = clk;
    *(int *)(B_001848B0 + 0x3C34) = t;
    r = mcWrite(port, B_001848B0, 0x3C90);
    if (r == 0) {
        setSavedClock(&clk);
        setSavedGameTime(t);
    }
    return r;
}

int gStatMcLoad(int port)
{
    int r = mcRead(port, B_001848B0, 0x3C90);
    if (r == 0) {
        vschedGameTime = *(int *)(B_001848B0 + 0x3C34);
        setSavedClock(B_001848B0 + 0x3C48);
    }
    return r;
}

void *gStatGetOmakeStatAdrs(void)
{
    return B_001884D0;
}

int gStatSaveDataGameFlagChk(int n)
{
    return (B_001848B0[n / 8] >> (n & 7)) & 1;
}

void gStatGObjDispOn(Gobj *g)
{
    g->disp = 1;
}

void gStatGObjDispOff(Gobj *g)
{
    g->disp = 0;
}

int gStatGObjDispChk(Gobj *g)
{
    return g->disp;
}

int gStatGobjDispGflagChk(Gobj *g)
{
    int f = g->flag;
    if (f == 0)
        return 0;
    if (!g->cls)
        return _gameFlagChk(f);
    return _gameFlagChk(f) == 0;
}

void gStatGobjDispGflagSet(Gobj *g)
{
    int f = g->flag;
    if (f != 0) {
        if (!g->cls)
            _gameFlagSet(f);
        else
            _gameFlagCls(f);
    }
}

void gStatGobjDispGflagCls(Gobj *g)
{
    if (g->flag != 0) {
        if (g->cls == 1)
            _gameFlagSet(g->flag);
        else
            _gameFlagCls(g->flag);
    }
}

void gStatSetGObjAdrs(Gobj *g, int adrs)
{
    g->adrs = adrs;
}

int gStatGetGObjAdrs(Gobj *g)
{
    return g->adrs;
}

void gStatStartTimeAttack(void)
{
    gstatTimeAttackMode = 2;
    SetTimeAttackTimeFlag(1);
}

void gStatStopTimeAttack(void)
{
    gstatTimeAttackMode = 3;
    SetTimeAttackTimeFlag(0);
}

float gStatGetPlayerAccessoriesDamgeRaitoToPlayer(void)
{
    float r = 1.0f;
    float total;

    if (D_0017A28C != 0)
        r = D_0017A28C->toPlayer;
    total = r;
    if (D_0017A290 != 0)
        total *= D_0017A290->toPlayer;
    return total;
}

float gStatGetPlayerAccessoriesDamgeRaitoToBoss(void)
{
    float r = 1.0f;
    float total;

    if (D_0017A28C != 0)
        r = D_0017A28C->toBoss;
    total = r;
    if (D_0017A290 != 0)
        total *= D_0017A290->toBoss;
    return total;
}

void gStatLoadPlayerChara(int a)
{
    int id = 0xB6;
    int c = D_0017A280;
    if (c != 0) {
        if (c == id)
            goto done;
        if (c != 0)
            stagemanager_unloadstagecore(c);
    }
    stagemanager_loadstagecore(rootPtn, 0xB6, a, 0);
done:
    D_0017A280 = 0xB6;
    gStatLoadPlayerAccessories();
}

void gStatUnloadPlayerChara(void)
{
    int id;
    int id2;

    id = D_0017A28C->id;
    if (id != 0)
        stagemanager_unloadstagecore(id);
    D_0017A28C = D_0017A240;
    id2 = *(int *)&D_0017A290->id; /* an int load, not a struct-member load: keeps the original schedule */
    if (id2 != 0)
        stagemanager_unloadstagecore(id2);
    D_0017A290 = 0;
    if (D_0017A284 != 0) {
        stagemanager_unloadstagecore(D_0017A284);
        D_0017A284 = 0;
    }
    if (D_0017A288 != 0) {
        stagemanager_unloadstagecore(D_0017A288);
        D_0017A288 = 0;
    }
    if (D_0017A280 != 0)
        stagemanager_unloadstagecore(D_0017A280);
    D_0017A280 = 0;
}

/* Selected horse type; this shape (base kept, e advanced inside) returns ->stage. */
static inline HorseType *findHorse(void)
{
    int *sh = SH_HorseTypeDEFAULT;
    int n = sh[3];
    HorseType *e = (HorseType *)sh[4];
    HorseType *base = e;
    int i;

    n--;
    e++;

    for (i = 0; i < n; i++, e++) {
        if (_omakeSelectFlagChk(e->flag))
            return e;
    }
    return base;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

int gStatGetHorseDemoStageIndex(void)
{
    return findHorse()->stage;
}

int gStatGetHorseDemoISYSObj(void)
{
    char *p = dldResolve(&findHorse()->obj);
    int r = 0;

    if (p != 0)
        r = *(int *)(p + 8);
    return r;
}

void gStatLoadHorseChara(int arg)
{
    loadHorseChara(arg);
}

void gStatUnloadHorseChara(void)
{
    if (D_0017A294 != 0) {
        stagemanager_unloadstagecore(D_0017A294);
    }
    D_0017A294 = 0;
}

void gStatRestartHorseChara(void)
{
    int s = D_0017A294;
    if (s != 0)
        stagemanager_restartstagecore(rootPtn, s, -1, 0);
}

void gStatLoadAdvertiseHorseChara(void)
{
    _omakeSelectFlagSet(findHorse()->set);
}

void gStatUnloadAdvertiseHorseChara(void)
{
    HorseType *e = findHorse();

    if (e->set != 0)
        _omakeSelectFlagSet(e->set);
    else
        _omakeSelectFlagCls(e->flag);
}

void gStatInit(void)
{
    omakeStatInit(D_0017A2A0, D_0017A298 != 0 ? B_00188550 : 0, 0);
    gameFlagInit();
    bossStatInit();
    backStageInit();
    time_attack_init_gstat_adrs();
    func_00018E00(0, 1);
}

void gStatInitNotOmakeInit(void)
{
    gameFlagInit();
    bossStatInit();
    backStageInit();
    time_attack_init_gstat_adrs();
    func_00018E00(0, 1);
}
