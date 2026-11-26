#ifndef GAMECORE_GSTAT_H
#define GAMECORE_GSTAT_H

/* GAMECORE game status (src/xff/GAMECORE/gstat.c): checkpoints, memory card
 * saves, player/horse characters and accessories, game objects' display
 * flags. Structs are padded views: only the fields the group reads are named. */

typedef struct {
    int flag;
    int id;
    float toPlayer;
    float toBoss;
} Accessory;

typedef struct {
    int a;
    int b;
    int flag;
    int adrs;
    unsigned int disp : 1;
    unsigned int cls : 1;
} Gobj;

typedef struct {
    int core;
    int flag;
    int stage;
    unsigned int obj;
    int set;
} HorseType;

typedef struct {
    signed char a;
    signed char place;
    char pad[0x42];
} SavePoint;

typedef struct {
    char pad[0xC];
    int n;
    SavePoint *list;
} SavePointList;

void gameModeInit(void);
int gStatCheckPointLoad(void);
void gStatLoadPlayerAccessories(void);
void gStatRestartPlayerChara(void);
void gStatReloadHorseChara(void);
void gStatCheckPointSave(void);
void gStatChekcPointSaveHookPlayerHorsePos(void *ppos, void *pdir, void *hpos, void *hdir, int arg);
void gStatOmakeSave(void);
SavePoint *gStatPlaceIdToSavePoint(int place);
int gStatMcSave(int port);
int gStatMcLoad(int port);
void *gStatGetOmakeStatAdrs(void);
int gStatSaveDataGameFlagChk(int n);
void gStatGObjDispOn(Gobj *g);
void gStatGObjDispOff(Gobj *g);
int gStatGObjDispChk(Gobj *g);
int gStatGobjDispGflagChk(Gobj *g);
void gStatGobjDispGflagSet(Gobj *g);
void gStatGobjDispGflagCls(Gobj *g);
void gStatSetGObjAdrs(Gobj *g, int adrs);
int gStatGetGObjAdrs(Gobj *g);
void gStatStartTimeAttack(void);
void gStatStopTimeAttack(void);
float gStatGetPlayerAccessoriesDamgeRaitoToPlayer(void);
float gStatGetPlayerAccessoriesDamgeRaitoToBoss(void);
void gStatLoadPlayerChara(int a);
void gStatUnloadPlayerChara(void);
int gStatGetHorseDemoStageIndex(void);
int gStatGetHorseDemoISYSObj(void);
void gStatLoadHorseChara(int arg);
void gStatUnloadHorseChara(void);
void gStatRestartHorseChara(void);
void gStatLoadAdvertiseHorseChara(void);
void gStatUnloadAdvertiseHorseChara(void);
void gStatInit(void);
void gStatInitNotOmakeInit(void);

#endif /* GAMECORE_GSTAT_H */
