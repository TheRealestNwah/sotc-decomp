/* basescript/src/sword.c: the sword's light beam, glow and weak-point effects.
 *
 * Inferred file boundaries and the source name are in docs/findings.md. The
 * functions not decompiled yet stay in the module's assembly; the statics
 * below are the file's whole .data block, in the original order. */

typedef struct GameObj GameObj;
typedef struct SpriteMenuObjDef SpriteMenuObjDef;

extern SpriteMenuObjDef *ScriptSpriteMenuObjDef_SPRITE_BOSS_LIFE_LAYOUT;
extern void _SCRStartSpriteMenuAnim(SpriteMenuObjDef *def, int a1, int a2, int a3, int *status,
                                    int t1);
extern int GAMEUTIL_is_player_obj(GameObj *obj);
extern void fadeout_weakpoint_effect(void);
extern void cancel_fadeout_weakpoint_effect(void);
extern void RequestCharacterMotionShiftFunc(GameObj *obj, void (*func)());
extern int SParticleSheetData_S_GLOW;
extern int SParticleSheetData_S_AURA;
extern int SParticleSheetData_S_FLARE;
extern int SParticleSheetData_S_LINE;
extern int SParticleSheetData_S_LINE_BOSS;
extern void *memset(void *dst, int c, unsigned int n);
extern int get_particle_effect_id_from_sheet(int sheet);
extern int boot_particle_emitter(int effect, void *param, void (*onEnd)(int *done), int *idOut);
extern void *get_particle_emitter_from_emitter_id(int id);
extern int is_loop_particle(int effect);
extern void end_particle_emitter(int effect, int id, int a2);

typedef struct {
    char pad0[0xC];
    float f0C;
    char pad10[0xC];
    float f1C;
    char pad20[0x20];
} ParticleParam;

extern int SeList_sword_test;
extern int sePlay3D(int se, void *pos, int a2, int a3);
extern void seSetVol(int handle, float vol);
extern void seStop(int handle);
extern GameObj *SCRGetFirstObj(void *list);
extern void nico_playerEndHoistSword(GameObj *obj);

typedef struct {
    char pad0[0x2B0];
    char playerList[1];
} GcGlobalVar;

extern GcGlobalVar gcGlobalVar;

static void func_000C5468(int *done);

/* Not decompiled yet; named after their labels in the assembly. */
extern void func_000C3BA0();
extern void func_000C5718();

static int bossSprStatus[4] = { 0, 0, 0, 0 };
static int D_0017B080[4] = { 0, 0, 0, 0 };
static float D_0017B090[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
static float minAmbient = 0.735f;
static float maxAmbient = 1.155f;
static float minAmbientLine = 0.735f;
static float maxAmbientLine = 1.26f;
static float minAngle = 0.0f;
static float maxAngle = 180.0f;
static float maxLineAngle = 75.0f;
static float minAmbientWeak = 0.63f;
static float maxAmbientWeak = 0.84f;
static float minAmbientLineWeak = 0.63f;
static float maxAmbientLineWeak = 0.84f;
static float minAngleWeak = 0.0f;
static float maxAngleWeak = 30.0f;
static float maxLineAngleWeak = 90.0f;
static float maxFogMulVal = 1.0f;
static float fogChangeSpeed = 0.15f;
static float swordLineWidthMax = 1.35f;
static float swordLineChangeSpeed = 0.1f;
static float swordLineChangeThreshold = 0.6f;
static float D_0017B0EC = 0.8f;
static float bossHPRatioBase = 0.7f;
static float D_0017B0F4 = 0.3f;
static float D_0017B0F8 = 1.0f;
static float D_0017B0FC = 1.0f;
static int D_0017B100 = 0;
static int D_0017B104 = 0;
static struct {
    void *pos;
    int se[3]; /* sound handles: sword hum, boss, weak point */
} swordSe = { 0, { 0, 0, 0 } };
static int D_0017B118 = 0;
static int D_0017B11C = 0;
static int D_0017B120 = 0;
static int D_0017B124 = 0;
static int D_0017B128 = 0;
static float D_0017B12C = 0.2f;
static int D_0017B130 = 0;
static float D_0017B134 = 0.2f;
static long swordFlareHitPlaneAttribute = 0;
static int D_0017B140[4] = { 0, 0, 0, 0 };
static int D_0017B150 = 0;
static int D_0017B154 = 0;
static struct {
    int id;
    void *emitter;
} swordEmitters[11] = { { 0 } };
static int swordEmitterCount = 0;
static float swordGlowDistMin = 3.0f;
static float swordGlowDistMax = 5.0f;
static int D_0017B1BC = 0;
static int D_0017B1C0[2] = { 0, 0 };
static float collisionGlowSpeed = 1.0f;
static float collisionGlowTime = 0.05f;
static float collisionPosOffset = 0.1f;
static int D_0017B1D4 = 0;
static float D_0017B1D8 = 1.0f;
static int D_0017B1DC = 0;
static int D_0017B1E0 = 0;
static int swordIndicateAimPoint = 0;
static float D_0017B1E8 = 1.0f;
static int D_0017B1EC = 0;

void BossSprStatusBegin(void)
{
    int *status = bossSprStatus;
    if (*status == 0) {
        *status = 1;
        _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_BOSS_LIFE_LAYOUT, 0, 0, 0, status, 0);
    }
}

void BossSprStatusEnd(void)
{
    bossSprStatus[0] = 0;
}

/* Starts the sword's sounds at `pos`, silent; bossSe/weakSe 0 stops that one. */
static void func_000C0D48(int bossSe, int weakSe, void *pos)
{
    int handle;

    if (swordSe.se[0] == 0) {
        swordSe.pos = pos;
        swordSe.se[0] = sePlay3D(SeList_sword_test, pos, 0, 0);
    }
    if (bossSe != 0 && swordSe.se[1] == 0) {
        handle = sePlay3D(bossSe, pos, 0, 0);
        swordSe.se[1] = handle;
        if (handle != 0) {
            seSetVol(handle, 0.0f);
        }
    } else {
        if (swordSe.se[1] != 0) {
            seStop(swordSe.se[1]);
        }
        swordSe.se[1] = 0;
    }
    if (weakSe != 0 && swordSe.se[2] == 0) {
        handle = sePlay3D(weakSe, pos, 0, 0);
        swordSe.se[2] = handle;
        if (handle != 0) {
            seSetVol(handle, 0.0f);
        }
    } else {
        if (swordSe.se[2] != 0) {
            seStop(swordSe.se[2]);
        }
        swordSe.se[2] = 0;
    }
    if (swordSe.se[0] != 0) {
        seSetVol(swordSe.se[0], 0.0f);
    }
}

/* The particle sheet of each emitter slot. */
#define SWORD_LINE(boss) ((boss) ? SParticleSheetData_S_LINE_BOSS : SParticleSheetData_S_LINE)
#define SWORD_SHEETS(boss)                                                                        {                                                                                                 SParticleSheetData_S_GLOW, SParticleSheetData_S_AURA, SParticleSheetData_S_FLARE,                 SWORD_LINE(boss), SWORD_LINE(boss), SWORD_LINE(boss), SWORD_LINE(boss),                       SWORD_LINE(boss), SWORD_LINE(boss), SWORD_LINE(boss), SWORD_LINE(boss)                }

/* Boots the sword's particle emitters that aren't running. */
static void func_000C11E8(int boss)
{
    int sheets[11] = SWORD_SHEETS(boss);
    ParticleParam param;
    int i;

    memset(&param, 0, sizeof(param));
    param.f0C = 1.0f;
    param.f1C = 1.0f;
    for (i = 0; i < 11; i++) {
        if (swordEmitters[i].id == 0) {
            swordEmitters[i].id = boot_particle_emitter(
                get_particle_effect_id_from_sheet(sheets[i]), &param, func_000C5468,
                &swordEmitters[i].id);
            swordEmitterCount++;
            swordEmitters[i].emitter = get_particle_emitter_from_emitter_id(swordEmitters[i].id);
        }
    }
}

/* Ends the sword's looping particle emitters. */
static void func_000C1998(int boss)
{
    int sheets[11] = SWORD_SHEETS(boss);
    int i;

    for (i = 0; i < 11; i++) {
        if (swordEmitters[i].id != 0
            && is_loop_particle(get_particle_effect_id_from_sheet(sheets[i]))) {
            end_particle_emitter(get_particle_effect_id_from_sheet(sheets[i]), swordEmitters[i].id,
                                 0);
        }
    }
    D_0017B080[0] = 1;
}

/* Written out in each function: a static helper isn't inlined at -O2. */
#define STOP_SWORD_SE()                        do {                                           if (swordSe.se[0] != 0) {                      seStop(swordSe.se[0]);                     swordSe.se[0] = 0;                     }                                          if (swordSe.se[1] != 0) {                      seStop(swordSe.se[1]);                     swordSe.se[1] = 0;                     }                                          if (swordSe.se[2] != 0) {                      seStop(swordSe.se[2]);                     swordSe.se[2] = 0;                     }                                      } while (0)

void CancelSwordEffect(void)
{
    if (SCRGetFirstObj(gcGlobalVar.playerList) == 0) {
        return;
    }
    if (D_0017B150 != 0) {
        func_000C1998(1);
        STOP_SWORD_SE();
    } else if (D_0017B154 != 0) {
        func_000C1998(0);
        STOP_SWORD_SE();
    }
    nico_playerEndHoistSword(SCRGetFirstObj(gcGlobalVar.playerList));
    D_0017B1EC = 0;
}

int CheckSwordIndicateAimPoint(GameObj *obj)
{
    if (GAMEUTIL_is_player_obj(obj) == 1) {
        return swordIndicateAimPoint;
    }
    return 0;
}

long GetSwordFlareHitPlaneAttribute(void)
{
    return swordFlareHitPlaneAttribute;
}

float *getMinAmbient(void) { return &minAmbient; }
float *getMaxAmbient(void) { return &maxAmbient; }
float *getMinAmbientLine(void) { return &minAmbientLine; }
float *getMaxAmbientLine(void) { return &maxAmbientLine; }
float *getMinAngle(void) { return &minAngle; }
float *getMaxAngle(void) { return &maxAngle; }
float *getMaxLineAngle(void) { return &maxLineAngle; }
float *getMinAmbientWeak(void) { return &minAmbientWeak; }
float *getMaxAmbientWeak(void) { return &maxAmbientWeak; }
float *getMinAmbientLineWeak(void) { return &minAmbientLineWeak; }
float *getMaxAmbientLineWeak(void) { return &maxAmbientLineWeak; }
float *getMinAngleWeak(void) { return &minAngleWeak; }
float *getMaxAngleWeak(void) { return &maxAngleWeak; }
float *getMaxLineAngleWeak(void) { return &maxLineAngleWeak; }
float *getMaxFogMulVal(void) { return &maxFogMulVal; }
float *getFogChangeSpeed(void) { return &fogChangeSpeed; }
float *getSwordLineWidthMax(void) { return &swordLineWidthMax; }
float *getSwordLineChangeSpeed(void) { return &swordLineChangeSpeed; }
float *getSwordLlineChangeThreshold(void) { return &swordLineChangeThreshold; }
float *getBossHPRatioBase(void) { return &bossHPRatioBase; }

static void func_000C5468(int *done)
{
    *done = 0;
    if (--swordEmitterCount > 0) {
        return;
    }
    if (swordSe.se[0] != 0) {
        seStop(swordSe.se[0]);
        swordSe.se[0] = 0;
    }
    if (swordSe.se[1] != 0) {
        seStop(swordSe.se[1]);
        swordSe.se[1] = 0;
    }
    if (swordSe.se[2] != 0) {
        seStop(swordSe.se[2]);
        swordSe.se[2] = 0;
    }
    D_0017B150 = 0;
    D_0017B154 = 0;
    D_0017B0F8 = 1.0f;
    D_0017B080[0] = 0;
}

float *getSwordGlowDistMin(void) { return &swordGlowDistMin; }
float *getSwordGlowDistMax(void) { return &swordGlowDistMax; }
float *getCollisionGlowSpeed(void) { return &collisionGlowSpeed; }
float *getCollisionGlowTime(void) { return &collisionGlowTime; }
float *getCollisionPosOffset(void) { return &collisionPosOffset; }

static void func_000C5568(int *done)
{
    *done = 0;
}

static int T_000C5570(int a, int b)
{
    return a != b;
}

void checkChangeWeaponTypeSwordToOther(int from, int to)
{
    /* Nested ifs: `from > 0 && from < 4` would be folded into one unsigned
       range check, which the original doesn't have. */
    if (to == from) {
        return;
    }
    if (from < 4) {
        if (from > 0) {
            if (to < 4) {
                if (to > 0) {
                    return;
                }
            }
            fadeout_weakpoint_effect();
            return;
        }
    }
    if (to < 4) {
        if (to > 0) {
            cancel_fadeout_weakpoint_effect();
        }
    }
}

void SCRDirectionalArrowBegin(GameObj *obj)
{
    RequestCharacterMotionShiftFunc(obj, func_000C3BA0);
}

void SCRDirectionalArrowEnd(GameObj *obj)
{
    RequestCharacterMotionShiftFunc(obj, func_000C5718);
}
