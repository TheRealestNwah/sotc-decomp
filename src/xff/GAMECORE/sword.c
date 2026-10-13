/* basescript/src/sword.c: the sword's light beam, glow and weak-point effects.
 *
 * Inferred file boundaries and the source name are in docs/findings.md. The
 * functions not decompiled yet stay in the module's assembly; the statics
 * below are the file's whole .data block, in the original order. */

typedef struct GameObj GameObj;
typedef float sceVu0FVECTOR[4] __attribute__((aligned(16)));
typedef int sceVu0IVECTOR[4] __attribute__((aligned(16)));

/* The sword's transform: position, then its direction at 0xB0. */
typedef struct {
    sceVu0FVECTOR pos;
    char pad10[0xA0];
    sceVu0FVECTOR dir;
} SwordMatrix;
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
extern int SParticleSheetData_S_REACTION;
extern int SParticleSheetData_S_REACTION_SUB;
extern void CopyGeometryPointer(void *dst, void *src);
extern void set_npe_blend_ratio_particle_emitter(int effect, int id, float ratio);
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

extern float iosGetSinf(float x);
extern int bossStatGetActiveBoss(void);
extern void GetQuaternionByAxisDirZY(sceVu0FVECTOR q, sceVu0FVECTOR dir, sceVu0FVECTOR up);

extern void gsRegBegin(void);
extern void gsReg(int reg, unsigned long value);
extern void gsRegEnd(void);
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern unsigned long getFrameBufferSizeFBP(void);
extern int getFrameBufferSizeTBP(void);
extern int getDrawBufferAddressFBP(void);
extern int getDrawBufferAddressTBP(void);

/* libgraph's register macros (sce/libgraph.h). */
#define SCE_GS_SET_FRAME(fbp, fbw, psm, fbmsk)     ((unsigned long)(fbp) | ((unsigned long)(fbw) << 16) | ((unsigned long)(psm) << 24)      | ((unsigned long)(fbmsk) << 32))
#define SCE_GS_SET_TEX0(tbp, tbw, psm, tw, th, tcc, tfx, cbp, cpsm, csm, csa, cld)                ((unsigned long)(tbp) | ((unsigned long)(tbw) << 14) | ((unsigned long)(psm) << 20)           | ((unsigned long)(tw) << 26) | ((unsigned long)(th) << 30) | ((unsigned long)(tcc) << 34)      | ((unsigned long)(tfx) << 35) | ((unsigned long)(cbp) << 37)                                | ((unsigned long)(cpsm) << 51) | ((unsigned long)(csm) << 55)                               | ((unsigned long)(csa) << 56) | ((unsigned long)(cld) << 61))
#define SCE_GS_SET_XYOFFSET(ofx, ofy) ((unsigned long)(ofx) | ((unsigned long)(ofy) << 32))
#define SCE_GS_SET_SCISSOR(scax0, scax1, scay0, scay1)                                        ((unsigned long)(scax0) | ((unsigned long)(scax1) << 16) | ((unsigned long)(scay0) << 32)      | ((unsigned long)(scay1) << 48))

extern void spriteTexFast(int x0, int y0, int x1, int y1, int rgb, int *uv, int *color, int a7);

extern int SeList_sword_test;
extern int sePlay3D(int se, void *pos, int a2, int a3);
extern void seSetVol(int handle, float vol);
extern void seStop(int handle);
extern void scrRun(void);
extern GameObj *SCRGetFirstObj(void *list);
extern void nico_playerEndHoistSword(GameObj *obj);
extern void nico_playerBeginHoistSword(GameObj *obj);
extern int getSelectWeapon(void);
extern int bossStatBootChk(void);
extern int SeList_sword_boss_test;
extern int SeList_sword_weak_test;
extern sceVu0FVECTOR B_0019CE70; /* in sword.c's .bss */
extern sceVu0FVECTOR B_0019CEB0;
extern sceVu0FVECTOR B_0019CEC0;
extern void T_000C2620();
extern int SParticleSheetData_S_GLOW_CLEAR;
extern void GetCollisionDBGroupCallBack(void *group, void (*func)(), void *query);
extern void SetGeometryPointerGlobalState(void *geom, sceVu0FVECTOR a, sceVu0FVECTOR b);
extern void ConvertGeometryPointerZNormalMode(void *dst, void *src);
extern void boot_weakpoint_effect(sceVu0FVECTOR pos, float power, float a, float b);

typedef unsigned int u_long128 __attribute__((mode(TI)));

/* Collision query for the sword's glow: filled in by T_000C2620. */
typedef struct {
    u_long128 pos;
    float dist;
    int hit;
    char pad18[4];
    float power;
    char pad20[0x10];
    sceVu0FVECTOR hitPos;
    char geometry[0x90];
} SwordGlowQuery;

typedef struct {
    char pad0[0x178];
    float time;
    char pad17C[0x258 - 0x17C];
    char colGroup[0x2B0 - 0x258];
    char playerList[1];
} GcGlobalVar;

extern GcGlobalVar gcGlobalVar;

static void func_000C5468(int *done);

/* Not decompiled yet; named after their labels in the assembly. */
static void func_000C1440(sceVu0FVECTOR rot, sceVu0FVECTOR pos, int a2, float lineAngle,
                          float ambient, float ambientLine);

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
static float D_0017B100 = 0.0f;
static float D_0017B104 = 0.0f;
static struct {
    void *pos;
    int se[3]; /* sound handles: sword hum, boss, weak point */
} swordSe = { 0, { 0, 0, 0 } };
static float humVolTarget = 0.0f;
static float glowVolTarget = 0.0f;
static float humVol = 0.0f;
static float glowVol = 0.0f;
static float D_0017B128 = 0.0f;
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
static struct {
    int id;
    char *emitter;
} glowClearEmitter = { 0, 0 };
static float collisionGlowSpeed = 1.0f;
static float collisionGlowTime = 0.05f;
static float collisionPosOffset = 0.1f;
static int D_0017B1D4 = 0;
static float D_0017B1D8 = 1.0f;
static int D_0017B1DC = 0;
static int D_0017B1E0 = 0;
static int swordIndicateAimPoint = 0;
static float D_0017B1E8 = 1.0f;
static int swordHoisted = 0;

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

#define CLAMP01(x) ((x) < 0.0f ? 0.0f : ((x) > 1.0f ? 1.0f : (x)))
#define SIGN(x) ((x) < 0.0f ? -1.0f : ((x) > 0.0f ? 1.0f : 0.0f))
#define ABS(x) ((x) < 0.0f ? -(x) : (x))

/* Moves `vol` towards `target` by at most 0.1. */
#define STEP_VOL(vol, target)        \
    do {                             \
        float d = (target) - (vol);  \
        if (ABS(d) > 0.1f) {         \
            (vol) += SIGN(d) * 0.1f; \
        } else {                     \
            (vol) += d;              \
        }                            \
    } while (0)

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

#ifdef NONMATCHING
/* The first clamp matches; the later ones (on the statics) branch differently. */
/* Sets the sword sound volumes from the glow power (0..1) and `scale`. */
static void func_000C0EB0(float power, float scale)
{
    if (D_0017B080[0] != 0) {
        return;
    }
    power = CLAMP01(power);

    glowVolTarget = (1.0f - power) * 0.8f * (scale * 1.25f) + 0.15f;
    glowVolTarget = CLAMP01(glowVolTarget);
    glowVolTarget = iosGetSinf(glowVolTarget * 0.25f * 3.1415926f);
    STEP_VOL(glowVol, glowVolTarget);
    if (swordSe.se[1] != 0) {
        seSetVol(swordSe.se[1], glowVol);
    }
    if (swordSe.se[2] != 0) {
        seSetVol(swordSe.se[2], glowVol);
    }

    humVolTarget = power * 0.8f * (scale * 1.25f) + 0.15f;
    humVolTarget = CLAMP01(humVolTarget);
    humVolTarget = iosGetSinf(humVolTarget * 0.25f * 3.1415926f);
    STEP_VOL(humVol, humVolTarget);
    if (swordSe.se[0] != 0) {
        seSetVol(swordSe.se[0], humVol);
    }
}
#else
extern void func_000C0EB0(float power, float scale);
#endif

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

/* Quaternion product, as inlined in the original game code. */
#define VU_QUAT_MUL(dst, a, b) \
    __asm__ __volatile__( \
        "lqc2 vf11, 0(%0)\n" \
        "lqc2 vf12, 0(%1)\n" \
        "vmul.xyzw vf13, vf11, vf12\n" \
        "vaddy.x vf13, vf13, vf13y\n" \
        "vaddz.x vf13, vf13, vf13z\n" \
        "vsubx.w vf13, vf13, vf13x\n" \
        "vmulw.xyz vf14, vf12, vf11w\n" \
        "vmulw.xyz vf15, vf11, vf12w\n" \
        "vopmula.xyz ACC, vf12, vf11\n" \
        "vopmsub.xyz vf16, vf11, vf12\n" \
        "vadd.xyz vf13, vf14, vf15\n" \
        "vadd.xyz vf13, vf13, vf16\n" \
        "sqc2 vf13, 0(%2)\n" \
        : : "r"(a), "r"(b), "r"(dst) : "memory")

extern int get_main_particle_effect_lod_from_sheet(int sheet);
extern int get_sub_particle_effect_lod_from_sheet(int sheet);
extern volatile float *get_top_particle_effect_from_lod(int lod);
extern void SetQuaternionByAxisRotateVWithNoRegularize(sceVu0FVECTOR q, short angle,
                                                      sceVu0FVECTOR axis);
extern sceVu0FVECTOR ZUnitVector;
extern sceVu0FVECTOR YUnitVector;
extern void fogSetFogColorMulRatio(float ratio);

typedef struct {
    int values[11];
} SwordSheets;
/* The original reuses the sheet initializer's scratch space for rotations. */
typedef union {
    SwordSheets initial;
    struct {
        sceVu0FVECTOR line;
        sceVu0FVECTOR z;
        sceVu0FVECTOR pad20;
        sceVu0FVECTOR y;
    } rotations;
} SwordScratch;

static void func_000C1440(sceVu0FVECTOR rot, sceVu0FVECTOR pos, int boss, float lineAngle,
                         float ambient, float ambientLine)
{
    SwordSheets sheetList;
    SwordScratch scratch;
    int mainLod;
    int subLod;
    volatile float *mainEffect;
    volatile float *subEffect;
    float fog;
    float quarter;
    float one;
    short angle;
    int i;

    scratch.initial.values[0] = SParticleSheetData_S_GLOW;
    scratch.initial.values[1] = SParticleSheetData_S_AURA;
    scratch.initial.values[2] = SParticleSheetData_S_FLARE;
    scratch.initial.values[3] = SWORD_LINE(boss);
    scratch.initial.values[4] = SWORD_LINE(boss);
    scratch.initial.values[5] = SWORD_LINE(boss);
    scratch.initial.values[6] = SWORD_LINE(boss);
    scratch.initial.values[7] = SWORD_LINE(boss);
    scratch.initial.values[8] = SWORD_LINE(boss);
    scratch.initial.values[9] = SWORD_LINE(boss);
    scratch.initial.values[10] = SWORD_LINE(boss);
    sheetList = scratch.initial;

    mainLod = get_main_particle_effect_lod_from_sheet(SWORD_LINE(boss));
    subLod = get_sub_particle_effect_lod_from_sheet(SWORD_LINE(boss));
    mainEffect = get_top_particle_effect_from_lod(mainLod);
    subEffect = get_top_particle_effect_from_lod(subLod);
    if (D_0017B104 != D_0017B100) {
        D_0017B100 += (D_0017B104 - D_0017B100) * swordLineChangeSpeed;
    }
    /* Shared particle metadata is written before inspecting the emitter ID. */
    mainEffect[0x5C / 4] = D_0017B100 * 30.0f;
    subEffect[0x5C / 4] = D_0017B100 * 30.0f;
    if (*(volatile int *)&swordEmitters[0].id != 0) {
        SetGeometryPointerGlobalState((char *)swordEmitters[0].emitter + 0xD0,
                                      B_0019CEB0, B_0019CEC0);
        set_npe_blend_ratio_particle_emitter(sheetList.values[0], swordEmitters[0].id, 1.0f - ambient);
    }
    if (swordEmitters[1].id != 0) {
        SetGeometryPointerGlobalState((char *)swordEmitters[1].emitter + 0xD0, rot, pos);
        set_npe_blend_ratio_particle_emitter(sheetList.values[1], swordEmitters[1].id, 1.0f - ambient);
    }
    if (swordEmitters[2].id != 0) {
        SetGeometryPointerGlobalState((char *)swordEmitters[2].emitter + 0xD0, rot, pos);
        set_npe_blend_ratio_particle_emitter(sheetList.values[2], swordEmitters[2].id, 1.0f - ambient);
    }
    angle = (short)(lineAngle * 0.017453292f * 32768.0f / 3.1415926f);
    quarter = 0.78539815f;
    one = 1.0f;
    for (i = 3; i < 11; i++) {
        if (swordEmitters[i].id != 0) {
            short zAngle = (short)(i * quarter * 32768.0f / 3.1415926f);
            SetQuaternionByAxisRotateVWithNoRegularize(scratch.rotations.z, -zAngle, ZUnitVector);
            VU_QUAT_MUL(scratch.rotations.line, rot, scratch.rotations.z);
            SetQuaternionByAxisRotateVWithNoRegularize(scratch.rotations.y, -angle, YUnitVector);
            VU_QUAT_MUL(scratch.rotations.line, scratch.rotations.line, scratch.rotations.y);
            SetGeometryPointerGlobalState((char *)swordEmitters[i].emitter + 0xD0,
                                          scratch.rotations.line, pos);
            set_npe_blend_ratio_particle_emitter(sheetList.values[i], swordEmitters[i].id,
                                                 one - ambientLine);
        }
    }
    fog = 1.0f;
    if (D_0017B080[0] == 0) {
        fog = 1.0f - ambient * maxFogMulVal;
    }
    D_0017B0FC = fog;
    D_0017B0F8 += (fog - D_0017B0F8) * fogChangeSpeed;
    fogSetFogColorMulRatio(D_0017B0F8);
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

/* libvu0's sceVu0Normalize, inlined: dst = normalized xyz of src. */
#define VU0_NORMALIZE(dst, src)                             __asm__ __volatile__("lqc2 vf05, 0x0(%1)
"                                  "vmul.xyz vf07, vf05, vf05
"                           "vmulax.w ACC, vf00, vf07
"                            "vmadday.w ACC, vf00, vf07
"                           "vmaddz.w vf07, vf00, vf07
"                           "vrsqrt Q, vf00w, vf07w
"                              "vwaitq
"                                              "vmulq.xyz vf05, vf05, Q
"                             "sqc2 vf05, 0x0(%0)
"                                  :                                                       : "r"(dst), "r"(src)                                    : "memory")

static inline float ratio01(float x, float lo, float hi)
{
    float r = (x - lo) / (hi - lo);
    return CLAMP01(r);
}

/* Updating the input before clamping preserves the original register reuse. */
static inline float ratio01InPlace(float *x, float lo, float hi)
{
    *x = (*x - lo) / (hi - lo);
    return CLAMP01(*x);
}

static void func_000C1BA8(SwordMatrix *m, float power, float ambient)
{
    sceVu0FVECTOR dir;
    sceVu0FVECTOR rot;
    sceVu0FVECTOR zero;
    sceVu0FVECTOR identity;
    float ambientRatio;
    float scale;

    if (bossStatGetActiveBoss()) {
        VU0_NORMALIZE(dir, m->dir);
        GetQuaternionByAxisDirZY(rot, dir, D_0017B090);
        scale = ambient;
        ambientRatio = ratio01(ambient, minAmbientWeak, maxAmbientWeak);
        ambient = ratio01InPlace(&ambient, minAmbientLineWeak, maxAmbientLineWeak);
        /* Sounds use raw brightness; the emitters use the clamped ratios. */
        func_000C0EB0((power - D_0017B128) / (D_0017B12C - D_0017B128), scale);
        func_000C1440(rot, m->pos, 1, power * maxLineAngleWeak, ambientRatio, ambient);
    } else {
        memset(zero, 0, sizeof(zero));
        zero[3] = 1.0f;
        memset(identity, 0, sizeof(identity));
        identity[3] = 1.0f;
        func_000C1440(identity, zero, 1, 0.0f, 0.0f, 0.0f);
    }
}

/* Parked boss weak-point query: 193 words, 12 differing words. See issue #38. */
#ifdef NONMATCHING
extern void T_000C1D80();
extern void sprWeaponGetMarkerPos(sceVu0FVECTOR pos);
extern float GetAmbientBrightnessOfLayoutObject(GameObj *obj);
extern void GetCollisionDBSurfBoundary(sceVu0FVECTOR boundary, void *surface);
extern void boot_weakpoint_hit_effect(void *target, float power);
extern int ShockList_digi2;
extern void shockRequest(int shock);

#define VU_SUB_XYZ(dst, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n" \
                         "lqc2 vf06, 0(%2)\n" \
                         "vsub.xyz vf05, vf05, vf06\n" \
                         "sqc2 vf05, 0(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")

typedef struct {
    u_long128 pos;
    float dist;
    int hit;
    char pad18[0x18];
    sceVu0FVECTOR target;
    char geometry[0x50];
    int surface[2];
    char pad98[0x18];
    sceVu0FVECTOR dir;
    float bestDot;
    char padC4[0xC];
} SwordBeamQuery;

extern const SwordBeamQuery RO_00180600;

static void func_000C2318(GameObj *obj, u_long128 *pos)
{
    SwordBeamQuery query = RO_00180600;
    sceVu0FVECTOR marker;
    float brightness = 100.0f;
    float power;
    int sheet;
    int mainLod;
    int subLod;
    float *mainEffect;
    float *subEffect;
    float minRadians;

    sprWeaponGetMarkerPos(marker);
    query.pos = *pos;
    if (getSelectWeapon() != 2) {
        brightness = GetAmbientBrightnessOfLayoutObject(obj);
    }
    if (brightness < 0.0f) {
        brightness = 0.0f;
    }
    VU_SUB_XYZ(query.dir, marker, pos);
    power = (brightness - minAmbientWeak) / (maxAmbientWeak - minAmbientWeak);
    query.dir[3] = 1.0f;
    power = CLAMP01(power);
    sheet = SParticleSheetData_S_LINE_BOSS;
    mainLod = get_main_particle_effect_lod_from_sheet(sheet);
    subLod = get_sub_particle_effect_lod_from_sheet(sheet);
    mainEffect = (float *)get_top_particle_effect_from_lod(mainLod);
    subEffect = (float *)get_top_particle_effect_from_lod(subLod);
    query.dist = subEffect[0x24 / 4] * subEffect[0x3C / 4]
        + (mainEffect[0x24 / 4] * mainEffect[0x3C / 4]
           - subEffect[0x24 / 4] * subEffect[0x3C / 4]) * power;
    VU0_NORMALIZE(query.dir, query.dir);
    GetCollisionDBGroupCallBack(gcGlobalVar.colGroup, T_000C1D80, &query);
    if (query.hit) {
        GetCollisionDBSurfBoundary((float *)(query.geometry + 0x40), query.surface);
        ConvertGeometryPointerZNormalMode(query.geometry, query.geometry);
        boot_weakpoint_effect(query.target, 1.0f, query.target[2], query.target[3]);
        boot_weakpoint_hit_effect(query.target, 1.0f);
        {
            int shocks[2] = { ShockList_digi2, ShockList_digi2 };
        if (gcGlobalVar.time - (float)D_0017B140[0] > (float)D_0017B140[1]) {
            shockRequest(shocks[0]);
            D_0017B140[0] = (int)gcGlobalVar.time;
        }
        }
    }
    {
        float one = 1.0f;
        float angle = 3.1415926f;
        float dot = query.bestDot;
        float lo = minAngleWeak * 0.017453292f;

        dot += one;
        dot *= 0.5f;
        dot = one - dot;
        angle *= dot;
        func_000C1BA8((SwordMatrix *)&query,
            (angle - lo) / (maxAngleWeak * 0.017453292f - lo), brightness);
    }
}
#endif

/* Glow strength for a hit at `dist`: 1 at the minimum distance, 0 at the maximum. */
#define GLOW_POWER(power, dist, scale)                                                 \
    {                                                                               \
        float r;                                                                       \
        float sc = (scale);                                                            \
        (power) = ((dist) - swordGlowDistMin) / (swordGlowDistMax - swordGlowDistMin); \
        r = CLAMP01(power);                                                            \
        (power) = (1.0f - r) * sc;                                                     \
    }
#define UPDATE_GLOW_CLEAR(power)                                                            \
    {                                                                                    \
        if (glowClearEmitter.id != 0) {                                                     \
            SetGeometryPointerGlobalState(glowClearEmitter.emitter + 0xD0, B_0019CEB0,      \
                                          B_0019CEC0);                                      \
            set_npe_blend_ratio_particle_emitter(SParticleSheetData_S_GLOW_CLEAR,               \
                                                 glowClearEmitter.id, 1.0f - (power));                      \
        }                                                                                   \
    }

/* Lights the weak point the sword points at, and fades the glow-clear emitter. */
static void func_000C29B0(u_long128 *pos)
{
    SwordGlowQuery q;
    SwordGlowQuery init;
    float power;

    memset(&init, 0, sizeof(init));
    init.dist = swordGlowDistMax;
    q = init;
    q.pos = *pos;
    GetCollisionDBGroupCallBack(gcGlobalVar.colGroup, T_000C2620, &q);
    if (q.hit) {
        GLOW_POWER(power, q.dist, q.power);
        UPDATE_GLOW_CLEAR(power);
        ConvertGeometryPointerZNormalMode(q.geometry, q.geometry);
        boot_weakpoint_effect(q.hitPos, power, q.hitPos[2], q.hitPos[3]);
    } else {
        GLOW_POWER(power, 0.0f, 0.0f);
        UPDATE_GLOW_CLEAR(power);
    }
}

/* A glow reaction on something the sword hits. */
typedef struct {
    int active;
    float target;
    float value;
    float time;
    char geometry[0x50];
    struct {
        int id;
        char *emitter;
    } emitters[2];
} SwordReaction;

/* Moves the reaction's value towards its target and updates its two emitters.
   Returns 1 once the value has arrived. */
static int func_000C2BE0(SwordReaction *r)
{
    int sheets[2] = { SParticleSheetData_S_REACTION_SUB, SParticleSheetData_S_REACTION };
    int done = 0;
    float d;
    int i;

    r->value += (r->target - r->value) * collisionGlowSpeed;
    d = r->value - r->target;
    if (ABS(d) < 0.01f) {
        r->value = r->target;
        done = 1;
    }
    for (i = 0; i < 2; i++) {
        if (r->emitters[i].id != 0) {
            CopyGeometryPointer(r->emitters[i].emitter + 0xD0, r->geometry);
            set_npe_blend_ratio_particle_emitter(sheets[i], r->emitters[i].id, 1.0f - r->value);
        }
    }
    return done;
}

/* Clear both 32-bit words of an emitter slot, including its pointer. */
static inline void resetReactionEmitter(int *slot)
{
    slot[0] = 0;
    slot[1] = 0;
}

/* Script thread for a glow reaction: runs until it has faded out, then ends
   its emitters and resets it. */
static void func_000C2D20(SwordReaction *r)
{
    int i;
    int j;

    r->time = gcGlobalVar.time;
    while (r->active != 0) {
        if (func_000C2BE0(r)) {
            if (r->target == 0.0f) {
                r->active = 0;
            } else if (gcGlobalVar.time - r->time > collisionGlowTime) {
                r->target = 0.0f;
            }
        } else {
            r->time = gcGlobalVar.time;
        }
        scrRun();
    }
    {
        int sheets[2] = { SParticleSheetData_S_REACTION_SUB, SParticleSheetData_S_REACTION };

        for (i = 0; i < 2; i++) {
            if (r->emitters[i].id != 0
                && is_loop_particle(get_particle_effect_id_from_sheet(sheets[i]))) {
                end_particle_emitter(get_particle_effect_id_from_sheet(sheets[i]),
                                     r->emitters[i].id, 0);
            }
        }
    }
    /* Clear the status word alongside the float controls. This access keeps
       the original store order with the historical compiler. */
    *(float *)&r->active = 0.0f;
    r->target = 0.0f;
    r->value = 0.0f;
    r->time = gcGlobalVar.time;
    for (j = 0; j < 2; j++) {
        resetReactionEmitter((int *)&r->emitters[j]);
    }
}

/* Written out in each function: a static helper isn't inlined at -O2. */
#define STOP_SWORD_SE()            \
    do {                           \
        if (swordSe.se[0] != 0) {  \
            seStop(swordSe.se[0]); \
            swordSe.se[0] = 0;     \
        }                          \
        if (swordSe.se[1] != 0) {  \
            seStop(swordSe.se[1]); \
            swordSe.se[1] = 0;     \
        }                          \
        if (swordSe.se[2] != 0) {  \
            seStop(swordSe.se[2]); \
            swordSe.se[2] = 0;     \
        }                          \
    } while (0)

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
    swordHoisted = 0;
}

/* Motion callback: raises the sword and starts its effects if a sword is selected. */
static void func_000C3BA0(void)
{
    int weapon = getSelectWeapon();

    if (weapon < 4) {
        if (weapon > 0) {
            goto sword;
        }
    }
    swordHoisted = 0;
    return;
sword:
    if (swordHoisted == 0) {
        if (D_0017B150 == 0 && D_0017B154 == 0) {
            if (bossStatBootChk() > 0) {
                if (D_0017B150 == 0) {
                    func_000C11E8(1);
                    D_0017B150 = 1;
                    func_000C0D48(SeList_sword_boss_test, SeList_sword_weak_test,
                                  B_0019CE70);
                    D_0017B1D4 = 0;
                    D_0017B1D8 = 1.0f;
                    D_0017B1DC = 0;
                    D_0017B1E0 = 0;
                }
            } else if (D_0017B154 == 0) {
                func_000C11E8(0);
                D_0017B154 = 1;
                func_000C0D48(SeList_sword_boss_test, 0, B_0019CE70);
            }
        }
        swordIndicateAimPoint = 0;
        nico_playerBeginHoistSword(SCRGetFirstObj(gcGlobalVar.playerList));
    }
    swordHoisted = 1;
}

/* Copies the frame buffer into a 256x256 texture area, then restores the
   drawing environment (GS registers set directly). */
static void func_000C3CF8(void)
{
    int width;
    int height;
    int center = 0x800;
    int texOfs = 4;

    gsRegBegin();
    width = getDrawScreenWidth();
    height = getDrawScreenHeight();
    gsReg(0x4C, SCE_GS_SET_FRAME(getFrameBufferSizeFBP(), 4, 0, 0));
    gsReg(0x18, 0x0000780000007800);
    gsReg(0x40, 0x00FF000000FF0000);
    gsReg(0x4A, 0);
    gsReg(0x3B, 0x0000008000000080);
    gsReg(0x47, 0x31001);
    gsReg(0x42, 0x44);
    gsReg(0x14, 0x60);
    {
        sceVu0IVECTOR rect = { -center, -center, center * 2, center * 2 };
        sceVu0IVECTOR color = { 0x80, 0x80, 0x80, 0x80 };
        sceVu0IVECTOR uv = { texOfs, texOfs, width << 4, height << 4 };

        gsReg(6, SCE_GS_SET_TEX0(getDrawBufferAddressTBP(), width / 64, 1, 9, 9, 1, 0, 0, 0, 0, 0, 0));
        spriteTexFast(rect[0], rect[1], rect[2], rect[3], 0xFFFFFF, uv, color, 0);
    }
    gsReg(0x47, 0x5000D);
    gsReg(6, SCE_GS_SET_TEX0(getFrameBufferSizeTBP(), texOfs, 0, 8, 8, 1, 0, 0, 0, 0, 0, 0));
    gsReg(0x4C, SCE_GS_SET_FRAME(getDrawBufferAddressFBP(), (width >> 6) & 0x3F, 0, 0));
    gsReg(0x18, SCE_GS_SET_XYOFFSET((center - width / 2) << 4, (center - height / 2) << 4));
    gsReg(0x40, SCE_GS_SET_SCISSOR(0, width - 1, 0, height - 1));
    gsReg(8, 5);
    gsRegEnd();
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

extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

/* Filter collision surfaces by the packed material and reaction flags. */
static int T_000C5580(void *surface)
{
    unsigned long attribute = *GetCollisionDBAttributeAdr(surface);
    unsigned long flags = attribute & (0xF800UL << 20);
    unsigned long material = attribute & 0x7C000000UL;
    unsigned long mode = attribute & (0xF000UL << 30);
    unsigned long blocked = attribute & (0x8E00UL << 38);

    if (blocked != 0) {
        return 1;
    }
    if (material == 0x04000000UL || material == 0x64000000UL
        || material == 0x68000000UL || material == 0x6C000000UL || material == 0x24000000UL) {
        return 0;
    }
    if (flags == (0xE000UL << 18) || flags == (0x8000UL << 18)
        || flags == (0xB800UL << 20) || flags == (0xC000UL << 18)
        || flags == (0xA000UL << 19) || flags == (0xA000UL << 18)
        || mode == (0x8000UL << 28)) {
        return 0;
    }
    return 1;
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

static void func_000C5718(void);

void SCRDirectionalArrowEnd(GameObj *obj)
{
    RequestCharacterMotionShiftFunc(obj, func_000C5718);
}

/* Motion callback that puts the sword away. */
static void func_000C5718(void)
{
    CancelSwordEffect();
}
