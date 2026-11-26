#ifndef GAMECORE_SCRIPT_MAIN_H
#define GAMECORE_SCRIPT_MAIN_H

/* GAMECORE script runner (src/xff/GAMECORE/script_main.c). Structs are padded
 * views: only the fields the group reads are named. The views of gcGlobalVar
 * stay local to script_main.c, because each function sees a differently
 * padded slice of it and gcGlobalVar belongs to another group. */

/* A script character class (GetCharacterClass, GetScriptCharacterClass). */
typedef struct {
    char pad0[0x370];
    short state;
    char pad372[0x534 - 0x372];
    signed char active;
    char pad535[0xD90 - 0x535];
    unsigned char riding;
    char padD91[0x1070 - 0xD91];
    int f1070;
    char pad1074[0x1170 - 0x1074];
    int f1170;
} ScrCharClass;

/* A script object, as the runner dispatches it by type. */
typedef struct {
    char pad0[0x8];
    unsigned char type;
} ScrObj;

void bootprogressivecheck(int a);
void execObjectWithNonTaskSwitch(ScrObj *obj);
void scrRun(void);
void scrRunM(int n);
void st_playObjAnim(void);
void SCRSetDispFlag(unsigned char *obj, int on);
void *GetSCRCharaAIWorkPtr(void *actor);
int CheckSCRCharaAIWorkPtr(int arg0);
void SCRSimpleExecCharaGeometry(int arg0);
void scrInit(void);
void __execScrLwsOri(void *actor);
void st_motionsyncanimation(void);
int AddDefaultAIGroup(int a, int b, int c, int d);
void *initdefaultaitask(void);
void _initstage(void);
void initstage(int a0, int a1, int a2, int a3, int t0, int t1);

#endif /* GAMECORE_SCRIPT_MAIN_H */
