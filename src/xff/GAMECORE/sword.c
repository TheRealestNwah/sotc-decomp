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
static void T_000C2620();
extern int SParticleSheetData_S_GLOW_CLEAR;
extern void GetCollisionDBGroupCallBack(void *group, void (*func)(), void *query);
extern void SetGeometryPointerGlobalState(void *geom, sceVu0FVECTOR a, sceVu0FVECTOR b);
extern void ConvertGeometryPointerZNormalMode(void *dst, void *src);
extern void boot_weakpoint_effect(sceVu0FVECTOR pos, float power, float a, float b);

typedef unsigned int u_long128 __attribute__((mode(TI)));

/* Collision query for the sword's glow: filled in by T_000C2620. */
typedef struct {
    int a;
    int b;
} SwordCollisionId;

typedef struct {
    u_long128 pos;
    float dist;
    int hit;
    int pad18;
    float power;
    unsigned long attr;
    int part;
    char pad2C[4];
    /* Passed on as a vector: trigger flag and weak-point index as ints,
       then the part's two damage values. */
    sceVu0FVECTOR hitPos;
    char geometry[0x50];
    SwordCollisionId col;
    char pad98[0x38];
} SwordGlowQuery;

typedef struct {
    char pad0[0x178];
    float time;
    char pad17C[0x1AC - 0x17C];
    int pause;
    char pad1B0[0x258 - 0x1B0];
    char colGroup[0x2B0 - 0x258];
    char playerList[0x360 - 0x2B0];
    u_long128 cameraDir;
} GcGlobalVar;

extern GcGlobalVar gcGlobalVar;

static void func_000C5468(int *done);

/* Not decompiled yet; named after their labels in the assembly. */
static void func_000C1440(sceVu0FVECTOR rot, sceVu0FVECTOR pos, float lineAngle, float ambient, float ambientLine, int boss);

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
static float D_0017B130 = 0.0f;
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

/* Moves `vol` towards `target` by at most 0.1. The original stores through
   the pointer but rereads `vol` by name in each branch. */
#define STEP_VOL(vol, target)             \
    {                                     \
        float *p = &(vol);                \
        float d = (target) - *p;          \
        if (ABS(d) > 0.1f) {              \
            *p = (vol) + SIGN(d) * 0.1f;  \
        } else {                          \
            *p = (vol) + d;               \
        }                                 \
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

static void func_000C1440(sceVu0FVECTOR rot, sceVu0FVECTOR pos, float lineAngle, float ambient, float ambientLine, int boss)
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
        func_000C1440(rot, m->pos, power * maxLineAngleWeak, ambientRatio, ambient, 1);
    } else {
        memset(zero, 0, sizeof(zero));
        zero[3] = 1.0f;
        memset(identity, 0, sizeof(identity));
        identity[3] = 1.0f;
        func_000C1440(identity, zero, 0.0f, 0.0f, 0.0f, 1);
    }
}

/* Weak-point query for the boss: aims the beam at the marker and glows on a hit. */
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
    float planeDot;
    float power;
    unsigned long attr;
    int part;
    char pad2C[4];
    /* Trigger flag and weak-point index as ints, then two damage values. */
    sceVu0FVECTOR target;
    char geometry[0x50];
    int surface[2];
    char pad98[0x18];
    sceVu0FVECTOR dir;
    float bestDot;
    char padC4[0xC];
} SwordBeamQuery;

extern int CheckSCRCharaAIWorkPtr(GameObj *obj);
extern unsigned long *GetCollisionDBAttributeAdr(void *geom);
extern int getGameHardMode(void);
extern int SCRGetBossWeakPointIndexFromColAttr(unsigned long attr, GameObj *boss);
extern void *SCRGetBossWork(GameObj *boss);
extern float GetBossPartsDamagePerParts(void *work, int part);
extern int chkBossTrigTurnOff(int trigger);
extern void iosLocalPrintf(const char *fmt, ...);
extern float *SCRGetBossPartsDamageFromIndex(GameObj *boss, int part);
extern void GetGeometryPointerWithCollisionDBDataGlobalPoint(void *dst, void *geom,
                                                             sceVu0FVECTOR point);

/* Collision attribute bits. */
#define ATTR_HARD_ONLY (0x8000UL << 41)
#define ATTR_WEAK_POINT (0xC000UL << 40)
#define ATTR_TRIGGER (0xF800UL << 20)

/* Distance between the xyz of two vectors. */
#define VU_DISTANCE(ret, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "lqc2 vf06, 0x0(%2)\n" \
                         "vsub.xyzw vf07, vf05, vf06\n" \
                         "vmul.xyz vf07, vf07, vf07\n" \
                         "vmulax.w ACC, vf00, vf07x\n" \
                         "vmadday.w ACC, vf00, vf07y\n" \
                         "vmaddz.w vf07, vf00, vf07z\n" \
                         "vsqrt Q, vf07w\n" \
                         "vwaitq\n" \
                         "cfc2 $2, $vi22\n" \
                         "mtc1 $2, %0\n" \
                         : "=f"(ret) : "r"(a), "r"(b) : "$2")

/* The helpers' debug strings are the file's first .rodata, so they stay with
   the callbacks. getWeakIndexWeak is unused, but its string is still emitted. */
static inline int getWeakIndexWeak(unsigned long weak)
{
    if (weak == (0x4000UL << 40)) {
        return 0;
    }
    if (weak == (0x8000UL << 40)) {
        return 1;
    }
    if (weak == (0xC000UL << 40)) {
        return 2;
    }
    iosLocalPrintf("break at function getWeakIndexWeak(basescript/src/sword.c:%d)\n", 666);
    return -1;
}

static inline int getWeakIndexTrigger(unsigned long trigger)
{
    if (trigger == (0xD800UL << 20)) {
        return 0;
    }
    if (trigger == (0xE000UL << 20)) {
        return 1;
    }
    if (trigger == (0xE800UL << 20)) {
        return 2;
    }
    if (trigger == (0xF000UL << 20)) {
        return 3;
    }
    if (trigger == (0xF800UL << 20)) {
        return 4;
    }
    iosLocalPrintf("break at function getWeakIndexTrigger(basescript/src/sword.c:%d)\n", 684);
    return -1;
}

static inline int getWeakIndex(unsigned long attr)
{
    int index = -1;

    if (attr & ATTR_WEAK_POINT) {
        index = ((attr & ATTR_WEAK_POINT) >> 54) - 1;
    } else if (attr & ATTR_TRIGGER) {
        index = getWeakIndexTrigger(attr & ATTR_TRIGGER) + 3;
    } else {
        iosLocalPrintf("break at function getWeakIndex(basescript/src/sword.c:%d)\n", 702);
    }
    return index;
}

/* Surfaces marked hard-only light up only in hard mode, the rest only outside it. */
static inline int isIgnoredSurface(unsigned long attr)
{
    if (getGameHardMode()) {
        if (!(attr & ATTR_HARD_ONLY)) {
            return 1;
        }
    } else {
        if (attr & ATTR_HARD_ONLY) {
            return 1;
        }
    }
    return 0;
}

/* Inlined dot product of two vectors' xyz. */
#define VU_INNER_PRODUCT(ret, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "lqc2 vf06, 0x0(%2)\n" \
                         "vaddw.x vf07, vf00, vf00w\n" \
                         "vmul.xyz vf06, vf05, vf06\n" \
                         "vaddax.x ACC, vf00, vf06x\n" \
                         "vmadday.x ACC, vf07, vf06y\n" \
                         "vmaddz.x vf06, vf07, vf06z\n" \
                         "qmfc2 $2, vf06\n" \
                         "mtc1 $2, %0\n" \
                         : "=f"(ret) : "r"(a), "r"(b) : "$2")
/* Squared length of a vector's xyz. */
#define VU_SQUARE_LENGTH(ret, v) \
    __asm__ __volatile__("lqc2 vf07, 0x0(%1)\n" \
                         "vmul.xyz vf07, vf07, vf07\n" \
                         "vaddy.x vf07, vf07, vf07y\n" \
                         "vaddz.x vf07, vf07, vf07z\n" \
                         "qmfc2 $2, vf07\n" \
                         "mtc1 $2, %0\n" \
                         : "=f"(ret) : "r"(v) : "$2")
#define VU_SCALE_XYZW(dst, src, scale) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "qmtc2 %2, vf06\n" \
                         "vmulx.xyzw vf05, vf05, vf06x\n" \
                         "sqc2 vf05, 0x0(%0)\n" \
                         : : "r"(dst), "r"(src), "r"(scale) : "memory")
#define VU_ADD_XYZW(dst, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "lqc2 vf06, 0x0(%2)\n" \
                         "vadd.xyzw vf07, vf05, vf06\n" \
                         "sqc2 vf07, 0x0(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")

extern float SCRGetBossWeakPointAngleFromIndex(GameObj *boss, int part);
extern float iosGetCosf(float x);
extern int ClipCollisionDBDoubleSide(void *dst, void *start, void *end, void *geom);
extern float *GetCollisionDBPlane(void *geom);

/* Collision callback for the boss query: keeps the weak point or trigger
   surface the beam points at most directly, within its cone. */
static void T_000C1D80(void *geom, SwordBeamQuery *q)
{
    sceVu0FVECTOR boundary;
    sceVu0FVECTOR toHit;
    sceVu0FVECTOR dir;
    char clip[0x50];
    sceVu0FVECTOR end;
    GameObj *boss;
    unsigned long attr;
    int part;
    float power;
    float angle;
    float dot;
    float width;
    float dist;
    float *plane;
    float *damage;
    float hitDist;
    float planeDot;

    boss = SCRGetFirstObj(gcGlobalVar.playerList + 8);
    if (!CheckSCRCharaAIWorkPtr(boss)) {
        return;
    }
    attr = *GetCollisionDBAttributeAdr(geom);
    if (isIgnoredSurface(attr)) {
        return;
    }
    if (attr & ATTR_WEAK_POINT) {
        part = SCRGetBossWeakPointIndexFromColAttr(attr & ATTR_WEAK_POINT, boss);
        power = GetBossPartsDamagePerParts(SCRGetBossWork(boss), part);
        if (power > 0.0f) {
            power = bossHPRatioBase + (1.0f - bossHPRatioBase) * power;
        }
        power = CLAMP01(power);
        if (power == 0.0f) {
            return;
        }
    } else {
        int trigger;

        if ((attr & ATTR_TRIGGER) == 0) {
            return;
        }
        trigger = getWeakIndexTrigger(attr & ATTR_TRIGGER);
        part = SCRGetBossWeakPointIndexFromColAttr(attr & ATTR_TRIGGER, boss);
        if (chkBossTrigTurnOff(trigger)) {
            return;
        }
        power = 1.0f;
    }
    if (part == -1) {
        return;
    }
    angle = SCRGetBossWeakPointAngleFromIndex(boss, part);
    GetCollisionDBSurfBoundary(boundary, geom);
    VU_SUB_XYZ(toHit, boundary, &q->pos);
    VU0_NORMALIZE(dir, toHit);
    VU_INNER_PRODUCT(dot, dir, q->dir);
    width = CLAMP01(dot);
    width = width - swordLineChangeThreshold;
    width = CLAMP01(width);
    width = width / (1.0f - swordLineChangeThreshold);
    width = CLAMP01(width);
    D_0017B104 = power * swordLineWidthMax * width;
    if (!(iosGetCosf(angle * 0.5f * 0.017453294f) <= dot)) {
        return;
    }
    if (dot < q->bestDot) {
        return;
    }
    q->bestDot = dot;
    VU_SCALE_XYZW(end, q->dir, q->dist);
    VU_ADD_XYZW(end, &q->pos, end);
    VU_DISTANCE(dist, boundary, &q->pos);
    if (q->dist < dist) {
        return;
    }
    if (!ClipCollisionDBDoubleSide(clip, q, end, geom)) {
        return;
    }
    plane = GetCollisionDBPlane(geom);
    VU_SQUARE_LENGTH(hitDist, toHit);
    VU_INNER_PRODUCT(planeDot, plane, q->dir);
    q->hit = 1;
    q->dist = hitDist;
    q->planeDot = planeDot;
    q->power = power;
    q->attr = attr;
    q->part = part;
    {
        int index = getWeakIndex(attr);

        ((int *)q->target)[1] = index;
        ((int *)q->target)[0] = index >= 3;
    }
    damage = SCRGetBossPartsDamageFromIndex(boss, part);
    q->target[2] = damage[0x34 / 4];
    q->target[3] = damage[0x38 / 4];
    CopyGeometryPointer(q->geometry, clip);
    {
        int *dst = q->surface;

        dst[0] = ((int *)geom)[0];
        dst[1] = ((int *)geom)[1];
    }
}

static const SwordBeamQuery RO_00180600 = { .bestDot = -1.1f };

static void func_000C2318(GameObj *obj, u_long128 *pos, u_long128 *unusedDir)
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
    power = (brightness - minAmbientLineWeak) / (maxAmbientLineWeak - minAmbientLineWeak);
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
        float hi = maxAngleWeak * 0.017453292f;

        /* Map the best dot product to an angle, normalized to [lo, hi]. */
        dot = one - (dot + one) * 0.5f;
        func_000C1BA8((SwordMatrix *)&query, (angle * dot - lo) / (hi - lo), brightness);
    }
}

/* Collision callback for the glow query: keeps the nearest weak point or
   trigger surface that can currently light up. */
static void T_000C2620(void *geom, SwordGlowQuery *q)
{
    sceVu0FVECTOR boundary;
    GameObj *boss;
    unsigned long attr;
    int part;
    float power;
    float dist;
    float *damage;

    boss = SCRGetFirstObj(gcGlobalVar.playerList + 8);
    if (!CheckSCRCharaAIWorkPtr(boss)) {
        return;
    }
    attr = *GetCollisionDBAttributeAdr(geom);
    if (isIgnoredSurface(attr)) {
        return;
    }
    if (attr & ATTR_WEAK_POINT) {
        part = SCRGetBossWeakPointIndexFromColAttr(attr & ATTR_WEAK_POINT, boss);
        power = GetBossPartsDamagePerParts(SCRGetBossWork(boss), part);
        if (power > 0.0f) {
            power = bossHPRatioBase + (1.0f - bossHPRatioBase) * power;
        }
        power = CLAMP01(power);
        if (power == 0.0f) {
            return;
        }
    } else {
        int trigger;

        if ((attr & ATTR_TRIGGER) == 0) {
            return;
        }
        trigger = getWeakIndexTrigger(attr & ATTR_TRIGGER);
        part = SCRGetBossWeakPointIndexFromColAttr(attr & ATTR_TRIGGER, boss);
        if (chkBossTrigTurnOff(trigger)) {
            return;
        }
        power = 1.0f;
    }
    if (part == -1) {
        return;
    }
    GetCollisionDBSurfBoundary(boundary, geom);
    boundary[3] = 1.0f;
    VU_DISTANCE(dist, boundary, &q->pos);
    if (dist < q->dist) {
        int index;

        q->hit = 1;
        q->dist = dist;
        q->power = power;
        q->pad18 = 0;
        q->attr = attr;
        q->part = part;
        index = getWeakIndex(attr);
        ((int *)q->hitPos)[1] = index;
        ((int *)q->hitPos)[0] = index >= 3;
        damage = SCRGetBossPartsDamageFromIndex(boss, part);
        q->hitPos[2] = damage[0x34 / 4];
        q->hitPos[3] = damage[0x38 / 4];
        GetGeometryPointerWithCollisionDBDataGlobalPoint(q->geometry, geom, boundary);
        {
            SwordCollisionId *dst = &q->col;

            dst->a = ((SwordCollisionId *)geom)->a;
            dst->b = ((SwordCollisionId *)geom)->b;
        }
    }
}

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

/* Character collision fields used by the sword ray. */
typedef struct {
    char pad0[0x370];
    short collisionIndex;
    char pad372[0xE38 - 0x372];
    int *attributes;
} SwordCharacterCollision;

extern SwordCharacterCollision *GetCharacterClass(GameObj *obj);
extern int ClipCollisionDirectCallBack(void *geometry, void *start, void *end,
    int *attributes, int (*filter)(int, int), int a5, int a6, int (*hit)(void *), GameObj *boss);
extern long charrootdyn_getCollisionAttribute(void *geometry);
extern u_long128 *GetGeometryPointerSurfacePlane(void *geometry);
extern char B_0019CEE0[];
extern char rootPtn[];
static const char RO_001806D0[] = "boss_search_collision_effect";
extern void gcCreateScriptObj(void (*script)(SwordReaction *), SwordReaction *param,
    void *parent, int stackSize, int a4, int priority, const char *name);
static int T_000C5570(int a, int b);
static void func_000C5568(int *done);
static int T_000C5580(void *surface);

#define VU_SCALE_XYZ(dst, src, scale) \
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n" \
                         "qmtc2 %2, vf06\n" \
                         "vmulx.xyz vf05, vf05, vf06x\n" \
                         "sqc2 vf05, 0(%0)\n" \
                         : : "r"(dst), "r"(src), "r"(scale) : "memory")
#define VU_ADD_XYZ(dst, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n" \
                         "lqc2 vf06, 0(%2)\n" \
                         "vadd.xyz vf05, vf05, vf06\n" \
                         "sqc2 vf05, 0(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")

/* Keep emitter initialization in a semantic inline helper. The union view
   retains the original target-word store ordering with this compiler, and the
   sheet pointer (incremented before the index) the original loop scheduling. */
static inline void startSwordReaction(SwordReaction *reaction)
{
    int i;
    int sheets[2] = { SParticleSheetData_S_REACTION_SUB, SParticleSheetData_S_REACTION };
    int *sheet = sheets;

    reaction->active = 1;
    ((union { int i; float f; } *)&reaction->target)->f = 1.0f;
    for (i = 0; i < 2; sheet++, i++) {
        if (reaction->emitters[i].id == 0) {
            reaction->emitters[i].id = boot_particle_emitter(
                get_particle_effect_id_from_sheet(*sheet), reaction->geometry,
                func_000C5568, &reaction->active);
            reaction->emitters[i].emitter = get_particle_emitter_from_emitter_id(
                reaction->emitters[i].id);
        }
    }
    gcCreateScriptObj(func_000C2D20, reaction, rootPtn, 0x2000, 0, 8, RO_001806D0);
}

/* Cast the sword ray and start or refresh its collision glow reaction. */
static void func_000C2EB0(sceVu0FVECTOR pos, u_long128 *dir, float power)
{
    sceVu0FVECTOR end;
    sceVu0FVECTOR normal;
    sceVu0FVECTOR offset;
    sceVu0FVECTOR rotation;
    GameObj *player;
    GameObj *boss;
    SwordCharacterCollision *character;
    int sheet;
    int mainLod;
    int subLod;
    float *mainEffect;
    float *subEffect;
    float range;
    char *geometry;
    SwordReaction *reaction;

    player = SCRGetFirstObj(gcGlobalVar.playerList);
    if (player == 0) {
        return;
    }
    character = GetCharacterClass(player);
    sheet = SParticleSheetData_S_LINE;
    mainLod = get_main_particle_effect_lod_from_sheet(sheet);
    subLod = get_sub_particle_effect_lod_from_sheet(sheet);
    mainEffect = (float *)get_top_particle_effect_from_lod(mainLod);
    subEffect = (float *)get_top_particle_effect_from_lod(subLod);
    range = subEffect[9] * subEffect[15]
        + (mainEffect[9] * mainEffect[15] - subEffect[9] * subEffect[15]) * power;
    *(u_long128 *)end = *dir;
    VU0_NORMALIZE(&end, &end);
    VU_SCALE_XYZ(&end, &end, range);
    VU_ADD_XYZ(&end, &end, pos);
    ((float *)&end)[3] = 1.0f;
    boss = SCRGetFirstObj(gcGlobalVar.playerList + 4);
    geometry = B_0019CEE0;
    if (!ClipCollisionDirectCallBack(geometry, pos, &end,
        character->attributes + character->collisionIndex, T_000C5570, 0, 0,
        T_000C5580, boss)) {
        return;
    }
    swordFlareHitPlaneAttribute = charrootdyn_getCollisionAttribute(geometry);
    *(u_long128 *)normal = *GetGeometryPointerSurfacePlane(geometry);
    VU_SCALE_XYZ(offset, &normal, collisionPosOffset);
    VU_ADD_XYZ(geometry + 0x40, geometry + 0x40, offset);
    GetQuaternionByAxisDirZY(rotation, (float *)&normal, D_0017B090);
    reaction = (SwordReaction *)(geometry - 0x10);
    SetGeometryPointerGlobalState(geometry, rotation, (float *)(geometry + 0x40));
    /* Reusing the pointer keeps the emitter slots addressed from the reaction
       (the compiler otherwise folds them into geometry + 0x50). */
    geometry = (char *)reaction;
    if (reaction->active == 0) {
        startSwordReaction(reaction);
    } else if (reaction->target <= 1.0f) {
        ((union { int i; float f; } *)&reaction->target)->f = 1.0f;
    }
}

/* Inlined dot product of two vectors' xyz. */
#define VU_INNER_PRODUCT(ret, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "lqc2 vf06, 0x0(%2)\n" \
                         "vaddw.x vf07, vf00, vf00w\n" \
                         "vmul.xyz vf06, vf05, vf06\n" \
                         "vaddax.x ACC, vf00, vf06x\n" \
                         "vmadday.x ACC, vf07, vf06y\n" \
                         "vmaddz.x vf06, vf07, vf06z\n" \
                         "qmfc2 $2, vf06\n" \
                         "mtc1 $2, %0\n" \
                         : "=f"(ret) : "r"(a), "r"(b) : "$2")

extern void bossStatGetBossCloudPos(sceVu0FVECTOR pos, int boss);

/* The EE ABI assigns integer and float arguments in separate register
   sequences. Keeping the integer flag last reproduces call scheduling. */
/* Aims the sword beam at the active boss's cloud: sets the beam angle, line
   width and sounds, and starts a collision reaction once it's on target. */
static void func_000C3198(GameObj *obj, u_long128 *pos, u_long128 *unusedDir)
{
    sceVu0FVECTOR dir;
    sceVu0FVECTOR cloud;
    sceVu0FVECTOR rot;
    sceVu0FVECTOR marker;
    float brightness;
    float dot;
    float power;
    float ambientRatio;
    float lineRatio;
    float width;
    int boss;
    int sheet;
    int mainLod;
    int subLod;

    boss = bossStatGetActiveBoss();
    if (boss == 0) {
        return;
    }
    brightness = 100.0f;
    if (getSelectWeapon() != 2) {
        brightness = GetAmbientBrightnessOfLayoutObject(obj);
    }
    if (brightness < 0.0f) {
        brightness = 0.0f;
    }
    bossStatGetBossCloudPos(cloud, boss);
    VU_SUB_XYZ(cloud, cloud, pos);
    VU0_NORMALIZE(cloud, cloud);
    sprWeaponGetMarkerPos(marker);
    VU_SUB_XYZ(dir, marker, pos);
    VU0_NORMALIZE(dir, dir);
    GetQuaternionByAxisDirZY(rot, dir, D_0017B090);
    VU_INNER_PRODUCT(dot, dir, cloud);
    VU_INNER_PRODUCT(power, dir, cloud);
    {
        float one = 1.0f;
        float angle = 3.1415926f;
        float lo = minAngle * 0.017453292f;
        float hi = maxAngle * 0.017453292f;

        power = one - (power + one) * 0.5f;
        power = (angle * power - lo) / (hi - lo);
        power = CLAMP01(power);
    }
    ambientRatio = ratio01(brightness, minAmbient, maxAmbient);
    lineRatio = ratio01(brightness, minAmbientLine, maxAmbientLine);
    sheet = SParticleSheetData_S_LINE;
    mainLod = get_main_particle_effect_lod_from_sheet(sheet);
    subLod = get_sub_particle_effect_lod_from_sheet(sheet);
    get_top_particle_effect_from_lod(mainLod);
    get_top_particle_effect_from_lod(subLod);
    width = CLAMP01(dot);
    width = width - swordLineChangeThreshold;
    width = CLAMP01(width);
    width = width / (1.0f - swordLineChangeThreshold);
    width = CLAMP01(width);
    D_0017B104 = swordLineWidthMax * width;
    func_000C0EB0((power - D_0017B130) / (D_0017B134 - D_0017B130), lineRatio);
    func_000C1440(rot, pos, power * maxLineAngle, ambientRatio, lineRatio, 0);
    if (power < 0.01f) {
        func_000C2EB0(pos, dir, lineRatio);
        if (D_0017B1E8 >= 0.01f && D_0017B0F4 < lineRatio) {
            int shocks[2] = { ShockList_digi2, ShockList_digi2 };
            /* These pointers give the original's register assignment. */
            GcGlobalVar *g = &gcGlobalVar;
            int *timers = D_0017B140;
            int *timer = timers + 2;

            if (g->time - (float)*timer > (float)timers[3]) {
                shockRequest(shocks[1]);
                *timer = (int)g->time;
            }
        }
        D_0017B1E8 = power;
    } else {
        D_0017B1E8 = 1.0f;
    }
}


extern void func_000C3198(GameObj *obj, u_long128 *pos, u_long128 *dir);

/* libvu0's sceVu0ApplyMatrix, inlined: dst = m * v. */
#define VU_APPLY_MATRIX(dst, m, v) \
    __asm__ __volatile__("lqc2 vf08, 0x0(%2)\n" \
                         "lqc2 vf14, 0x0(%1)\n" \
                         "lqc2 vf15, 0x10(%1)\n" \
                         "lqc2 vf16, 0x20(%1)\n" \
                         "lqc2 vf17, 0x30(%1)\n" \
                         "vmulax.xyzw ACC, vf14, vf08x\n" \
                         "vmadday.xyzw ACC, vf15, vf08y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf08z\n" \
                         "vmaddw.xyzw vf10, vf17, vf08w\n" \
                         "sqc2 vf10, 0x0(%0)\n" \
                         : : "r"(dst), "r"(m), "r"(v) : "memory")

typedef union {
    u_long128 q;
    struct {
        float x, y, z, w;
    } v;
} SwordVec;

/* Preserve the script's original vector literals while it stays in assembly.
   When enabled, its local initializers below emit these same read-only bytes. */
#ifndef NONMATCHING
static const float RO_001806F0[4] = { -1.0f, 0.0f, 0.0f, 1.0f };
static const float RO_00180700[4] = { 0.0f, 0.0f, 0.1f, 1.0f };
#endif

typedef struct {
    char pad0[0x144];
    struct {
        char pad0[0x260];
        unsigned long flags;
    } *info;
} SwordHitLayout;

typedef struct {
    char pad0[0xC0];
    char geometry[0x124 - 0xC0];
    int hasGeometry;
    char pad128[0x158 - 0x128];
    sceVu0FVECTOR *matrix;
} SwordLayout;

extern void *isysGetThisSubThread(void);
/* The script and display paths use different views of the returned layout. */
extern void *GetLayoutClass(GameObj *obj);
extern void nico_weaponUpdateGeometry(SwordLayout *layout);
extern void FlushCollisionWork(GameObj *obj);
extern int isSeamlessStage(void);
extern void GetQuaternionFromMatrix(sceVu0FVECTOR q, sceVu0FVECTOR *m);
extern sceVu0FVECTOR XUnitVector;
extern sceVu0FVECTOR IdentityQuaternion;
extern sceVu0FVECTOR ZeroPoint;
extern void SetGeometryPointerNodePosState(void *geom, GameObj *obj, int node, sceVu0FVECTOR rot,
                                           sceVu0FVECTOR pos);
extern float iosGetATan2fExact(float y, float x);
extern float iosGetCosf(float x);
extern void iosApplyRotMatrix(sceVu0FVECTOR dst, sceVu0FVECTOR *m, sceVu0FVECTOR src);
extern int isWeaponTargetMarker(GameObj *obj);
extern int CheckSCRCharaAIWorkPtr(GameObj *obj);
extern GameObj *GetGeometryPointerObject(void *geom);
extern int _omakeSelectFlagChk(int flag);
extern void SetLayoutObjAccessSwitch(GameObj *obj, int on);

#ifdef NONMATCHING
/* Parked: 290 words vs the original 288. The rotation addresses (rotX/rotZ)
   get callee-saved registers instead of the D_0017B150/D_0017B154 high parts
   and `origin`. See issue #51. */
/* The sword's script thread: each frame, places the sword's lights and runs
   the beam update for the current target. */
void nico_swordstart(void)
{
    GameObj *obj = isysGetThisSubThread();
    SwordLayout *layout = GetLayoutClass(obj);
    sceVu0FVECTOR pos;
    sceVu0FVECTOR dir;
    sceVu0FVECTOR dirLocal = { -1.0f, 0.0f, 0.0f, 1.0f };
    sceVu0FVECTOR origin = { 0.0f, 0.0f, 0.0f, 1.0f };
    sceVu0FVECTOR tip = { 0.0f, 0.0f, 0.1f, 1.0f };
    sceVu0FVECTOR rotX;
    sceVu0FVECTOR rotZ;
    SwordVec a;
    SwordVec b;
    SwordHitLayout *hit;

    for (;;) {
        swordFlareHitPlaneAttribute = 0;
        if (gcGlobalVar.pause == 0) {
            nico_weaponUpdateGeometry(layout);
            FlushCollisionWork(obj);
        }
        if (isSeamlessStage()) {
            VU_APPLY_MATRIX(B_0019CEC0, layout->matrix, tip);
            GetQuaternionFromMatrix(B_0019CEB0, layout->matrix);
            SetQuaternionByAxisRotateVWithNoRegularize(rotX, -0x8000, XUnitVector);
            VU_QUAT_MUL(B_0019CEB0, B_0019CEB0, rotX);
            SetQuaternionByAxisRotateVWithNoRegularize(rotZ, -0x8000, ZUnitVector);
            VU_QUAT_MUL(B_0019CEB0, B_0019CEB0, rotZ);
            SetGeometryPointerNodePosState(B_0019CE70, obj, 0, IdentityQuaternion, ZeroPoint);
            if (D_0017B154 != 0 || D_0017B150 != 0) {
                float t;

                a.q = *(u_long128 *)dir;
                b.q = gcGlobalVar.cameraDir;
                a.v.z += a.v.y;
                b.v.z += b.v.y;
                VU0_NORMALIZE(&a, &a);
                VU0_NORMALIZE(&b, &b);
                t = iosGetCosf(iosGetATan2fExact(a.v.z, a.v.x) * 8.0f);
                t += 1.0f;
                t *= 0.5f;
                t = (t + (iosGetSinf(iosGetATan2fExact(-b.v.z, b.v.x)) + 1.0f) * 0.5f) * 0.5f;
                origin[2] = t * 0.55f * D_0017B0EC + -0.55f;
            }
            VU_APPLY_MATRIX(pos, layout->matrix, origin);
            iosApplyRotMatrix(dir, layout->matrix, dirLocal);
            if (D_0017B154 != 0) {
                func_000C3198(obj, (u_long128 *)pos, (u_long128 *)dir);
            } else if (D_0017B150 != 0) {
                if (isWeaponTargetMarker(SCRGetFirstObj(gcGlobalVar.playerList))) {
                    func_000C2318(obj, (u_long128 *)pos, (u_long128 *)dir);
                }
            } else {
                D_0017B104 = 0.0f;
                D_0017B100 = 0.0f;
            }
            if (CheckSCRCharaAIWorkPtr(SCRGetFirstObj(gcGlobalVar.playerList + 8))) {
                func_000C29B0((u_long128 *)pos);
            } else if (glowClearEmitter.id != 0) {
                set_npe_blend_ratio_particle_emitter(SParticleSheetData_S_GLOW_CLEAR,
                                                     glowClearEmitter.id, 1.0f);
            }
            hit = layout->hasGeometry ? (SwordHitLayout *)GetLayoutClass(GetGeometryPointerObject(layout->geometry)) : 0;
            if ((hit != 0 && (hit->info->flags & 0x30)) || _omakeSelectFlagChk(7)) {
                SetLayoutObjAccessSwitch(obj, 0);
            } else {
                SetLayoutObjAccessSwitch(obj, 1);
            }
        }
        scrRun();
    }
}
#endif

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

#ifdef NONMATCHING
/* Parked: DispWithSwordBlur and DispWithTorchBlur (identical but for the blade
   tip offset) compile to 616 of the original 629 words. The structure matches;
   loop-invariant hoisting and constant sharing differ (the original keeps 1.0f
   shared between quat[3] and the alpha clamps, and doesn't hoist the 0.5f
   colour or the stack addresses used before the loop). See issue #55. */
typedef sceVu0FVECTOR sceVu0FMATRIX[4];

/* Inverse of a rigid transform: transposed rotation, rotated negated translation. */
#define VU_INVERSE_MATRIX(dst, src) \
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n" \
                         "vsubw.x vf25, vf00, vf00w\n" \
                         "vmulx.xyz vf28, vf24, vf25x\n" \
                         "vsub.w vf28, vf28, vf28\n" \
                         "lq $8, 0x0(%1)\n" \
                         "lq $9, 0x10(%1)\n" \
                         "lq $10, 0x20(%1)\n" \
                         "qmfc2 $11, vf00\n" \
                         "pextlw $12, $9, $8\n" \
                         "pextuw $13, $9, $8\n" \
                         "pextlw $14, $11, $10\n" \
                         "pextuw $15, $11, $10\n" \
                         "pcpyld $8, $14, $12\n" \
                         "pcpyud $9, $12, $14\n" \
                         "pcpyld $10, $15, $13\n" \
                         "pcpyud $11, $13, $15\n" \
                         "qmtc2 $8, vf24\n" \
                         "qmtc2 $9, vf25\n" \
                         "qmtc2 $10, vf26\n" \
                         "vmulax.xyzw ACC, vf24, vf28x\n" \
                         "vmadday.xyzw ACC, vf25, vf28y\n" \
                         "vmaddaz.xyzw ACC, vf26, vf28z\n" \
                         "vmaddw.xyzw vf29, vf00, vf28w\n" \
                         "vsub.w vf29, vf29, vf29\n" \
                         "vadd.w vf29, vf29, vf00\n" \
                         "sqc2 vf24, 0x0(%0)\n" \
                         "sqc2 vf25, 0x10(%0)\n" \
                         "sqc2 vf26, 0x20(%0)\n" \
                         "sqc2 vf29, 0x30(%0)\n" \
                         : : "r"(dst), "r"(src) \
                         : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory")
/* dst = a * b */
#define VU_MUL_MATRIX(dst, a, b) \
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n" \
                         "lqc2 vf15, 0x10(%1)\n" \
                         "lqc2 vf16, 0x20(%1)\n" \
                         "lqc2 vf17, 0x30(%1)\n" \
                         "lqc2 vf24, 0x0(%2)\n" \
                         "lqc2 vf25, 0x10(%2)\n" \
                         "lqc2 vf26, 0x20(%2)\n" \
                         "lqc2 vf27, 0x30(%2)\n" \
                         "vmulax.xyzw ACC, vf14, vf24x\n" \
                         "vmadday.xyzw ACC, vf15, vf24y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf24z\n" \
                         "vmaddw.xyzw vf24, vf17, vf24w\n" \
                         "vmulax.xyzw ACC, vf14, vf25x\n" \
                         "vmadday.xyzw ACC, vf15, vf25y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf25z\n" \
                         "vmaddw.xyzw vf25, vf17, vf25w\n" \
                         "vmulax.xyzw ACC, vf14, vf26x\n" \
                         "vmadday.xyzw ACC, vf15, vf26y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf26z\n" \
                         "vmaddw.xyzw vf26, vf17, vf26w\n" \
                         "vmulax.xyzw ACC, vf14, vf27x\n" \
                         "vmadday.xyzw ACC, vf15, vf27y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf27z\n" \
                         "vmaddw.xyzw vf27, vf17, vf27w\n" \
                         "sqc2 vf24, 0x0(%0)\n" \
                         "sqc2 vf25, 0x10(%0)\n" \
                         "sqc2 vf26, 0x20(%0)\n" \
                         "sqc2 vf27, 0x30(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")
/* libvu0's sceVu0ApplyMatrix, inlined: dst = m * v. */
#define VU_APPLY_MATRIX(dst, m, v) \
    __asm__ __volatile__("lqc2 vf08, 0x0(%2)\n" \
                         "lqc2 vf14, 0x0(%1)\n" \
                         "lqc2 vf15, 0x10(%1)\n" \
                         "lqc2 vf16, 0x20(%1)\n" \
                         "lqc2 vf17, 0x30(%1)\n" \
                         "vmulax.xyzw ACC, vf14, vf08x\n" \
                         "vmadday.xyzw ACC, vf15, vf08y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf08z\n" \
                         "vmaddw.xyzw vf10, vf17, vf08w\n" \
                         "sqc2 vf10, 0x0(%0)\n" \
                         : : "r"(dst), "r"(m), "r"(v) : "memory")
/* Inlined dot product of two vectors' xyz. */
#define VU_INNER_PRODUCT(ret, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "lqc2 vf06, 0x0(%2)\n" \
                         "vaddw.x vf07, vf00, vf00w\n" \
                         "vmul.xyz vf06, vf05, vf06\n" \
                         "vaddax.x ACC, vf00, vf06x\n" \
                         "vmadday.x ACC, vf07, vf06y\n" \
                         "vmaddz.x vf06, vf07, vf06z\n" \
                         "qmfc2 $2, vf06\n" \
                         "mtc1 $2, %0\n" \
                         : "=f"(ret) : "r"(a), "r"(b) : "$2")
/* dst = a x b (xyz), w cleared. */
#define VU_OUTER_PRODUCT(dst, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "lqc2 vf06, 0x0(%2)\n" \
                         "vopmula.xyz ACC, vf05, vf06\n" \
                         "vopmsub.xyz vf07, vf06, vf05\n" \
                         "vsub.w vf07, vf07, vf07\n" \
                         "sqc2 vf07, 0x0(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")
/* dst = a * t + b * (1 - t) (xyz). */
#define VU_INTER_VECTOR(dst, a, b, t) \
    __asm__ __volatile__("mfc1 $8, %3\n" \
                         "qmtc2 $8, vf07\n" \
                         "lqc2 vf05, 0x0(%1)\n" \
                         "lqc2 vf06, 0x0(%2)\n" \
                         "vsubx.w vf08, vf00, vf07x\n" \
                         "vmulax.xyz ACC, vf05, vf07x\n" \
                         "vmaddw.xyz vf05, vf06, vf08w\n" \
                         "sqc2 vf05, 0x0(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b), "f"(t) : "$8", "memory")
/* dst = rotation of quaternion q applied to v, plus the translation t. */
#define VU_QUAT_ROT_TRANS(dst, q, v, t) \
    __asm__ __volatile__("lqc2 vf08, 0x0(%2)\n" \
                         "lqc2 vf18, 0x0(%3)\n" \
                         "vmove.w vf18, vf00\n" \
                         "vaddw.xyz vf12, vf00, vf00w\n" \
                         "lqc2 vf11, 0x0(%1)\n" \
                         "vmr32.w vf14, vf00\n" \
                         "vmr32.w vf15, vf00\n" \
                         "vmr32.w vf16, vf00\n" \
                         "vopmula.xyz ACC, vf11, vf12\n" \
                         "vmadd.xyz vf11, vf00, vf00\n" \
                         "vmadd.xyz vf10, vf11, vf12\n" \
                         "vmul.xyz vf13, vf11, vf10\n" \
                         "vopmula.xyz ACC, vf11, vf10\n" \
                         "vmaddw.xyz vf15, vf10, vf11w\n" \
                         "vmsubw.xyz vf16, vf10, vf11w\n" \
                         "vopmula.xyz ACC, vf13, vf12\n" \
                         "vmadd.xyz vf17, vf13, vf12\n" \
                         "vopmula.xyz ACC, vf15, vf12\n" \
                         "vmadd.xyz vf15, vf00, vf00\n" \
                         "vsub.xyz vf14, vf12, vf17\n" \
                         "vmove.yz vf17, vf14\n" \
                         "vmove.y vf14, vf16\n" \
                         "vmove.y vf16, vf15\n" \
                         "vmove.y vf15, vf17\n" \
                         "vmove.z vf14, vf15\n" \
                         "vmove.z vf15, vf16\n" \
                         "vmove.z vf16, vf17\n" \
                         "vmulax.xyzw ACC, vf14, vf08x\n" \
                         "vmadday.xyzw ACC, vf15, vf08y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf08z\n" \
                         "vmaddw.xyzw vf10, vf18, vf08w\n" \
                         "sqc2 vf10, 0x0(%0)\n" \
                         : : "r"(dst), "r"(q), "r"(v), "r"(t) : "memory")
#define VU_SCALE_XYZW(dst, src, scale) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "qmtc2 %2, vf06\n" \
                         "vmulx.xyzw vf05, vf05, vf06x\n" \
                         "sqc2 vf05, 0x0(%0)\n" \
                         : : "r"(dst), "r"(src), "r"(scale) : "memory")

typedef struct {
    char pad0[0x90];
    sceVu0FVECTOR scale;
    char padA0[0x15C - 0xA0];
    sceVu0FVECTOR *blurMatrix;
    char pad160[0x168 - 0x160];
    sceVu0FVECTOR *matrix;
    sceVu0FVECTOR *worldMatrix;
} WeaponLayout;

extern void DispLayoutObjModel(void);
extern int GetResetCameraFlagForDisplay(void);
extern void glEnable(int cap);
extern void glDisable(int cap);
extern void glLoadMatrixf(void *m);
extern sceVu0FMATRIX UnitMatrix;
extern void iosScaleMatrixV(sceVu0FMATRIX dst, sceVu0FMATRIX src, sceVu0FVECTOR scale);
extern void iosDlPushLayer(int layer);
extern void iosDlPopLayer(void);
extern void glZOffset(float offset);
extern float iosGetACosfExact(float x);
extern void CompletePlaneD(sceVu0FVECTOR plane, sceVu0FVECTOR point);
extern float GetPointDistanceFromPlane(sceVu0FVECTOR plane, sceVu0FVECTOR point);
extern void SetQuaternionByAxisRotateV(sceVu0FVECTOR q, short angle, sceVu0FVECTOR axis);
extern void iosgluGetViewCoordPosition(float *dst, sceVu0FVECTOR pos);
extern void glBegin(int mode);
extern void glEnd(void);
extern void glColor4f(float r, float g, float b, float a);
extern void glTexCoord2f(float s, float t);
extern void glVertex3fv(float *v);

/* Draws the blur trail of a weapon swing: a fan of quads swept from the
   blade's previous to its current position, textured with the frame buffer. */
#define DISP_WEAPON_BLUR(holder, weapon, tipOffset)                                         \
    {                                                                                     \
        sceVu0FMATRIX m;                                                                  \
        sceVu0FVECTOR p0;                                                                 \
        sceVu0FVECTOR p1;                                                                 \
        sceVu0FVECTOR p2;                                                                 \
        sceVu0FVECTOR p3;                                                                 \
        sceVu0FVECTOR base;                                                               \
        sceVu0FVECTOR tip;                                                                \
        sceVu0FVECTOR axis;                                                               \
        sceVu0FVECTOR d0;                                                                 \
        sceVu0FVECTOR d1;                                                                 \
        sceVu0FVECTOR mid0;                                                               \
        sceVu0FVECTOR mid1;                                                               \
        sceVu0FVECTOR plane;                                                              \
        sceVu0FVECTOR tmp;                                                                \
        sceVu0FVECTOR center;                                                             \
        sceVu0FVECTOR quat;                                                               \
        sceVu0FVECTOR rot;                                                                \
        sceVu0FVECTOR prev0;                                                              \
        sceVu0FVECTOR prev1;                                                              \
        float uv0[4];                                                                     \
        float uv1[4];                                                                     \
        sceVu0FVECTOR rel0;                                                               \
        sceVu0FVECTOR rel1;                                                               \
        sceVu0FVECTOR cur0;                                                               \
        sceVu0FVECTOR cur1;                                                               \
        WeaponLayout *h;                                                                  \
        WeaponLayout *w;                                                                  \
        float angle;                                                                      \
        float d;                                                                          \
        int i;                                                                            \
                                                                                          \
        DispLayoutObjModel();                                                             \
        h = GetLayoutClass(holder);                                                       \
        w = GetLayoutClass(weapon);                                                       \
        if (GetResetCameraFlagForDisplay() == 0) {                                        \
            float z0 = 0.05f;                                                             \
            float z1 = (tipOffset);                                                       \
                                                                                          \
            glEnable(0);                                                                  \
            glEnable(0x14);                                                               \
            glDisable(2);                                                                 \
            glEnable(3);                                                                  \
            glDisable(8);                                                                 \
            glLoadMatrixf(UnitMatrix);                                                    \
            VU_INVERSE_MATRIX(m, h->matrix);                                              \
            VU_MUL_MATRIX(m, w->worldMatrix, m);                                          \
            iosScaleMatrixV(m, m, h->scale);                                              \
            iosDlPushLayer(0x17);                                                         \
            base[0] = 0.0f;                                                               \
            base[1] = 0.0f;                                                               \
            base[2] = z0;                                                                 \
            base[3] = 1.0f;                                                               \
            tip[0] = 0.0f;                                                                \
            tip[1] = 0.0f;                                                                \
            tip[2] = z1;                                                                  \
            tip[3] = 1.0f;                                                                \
            func_000C3CF8();                                                              \
            glZOffset(1.05f);                                                             \
            VU_APPLY_MATRIX(p2, h->blurMatrix, base);                                     \
            VU_APPLY_MATRIX(p3, h->blurMatrix, tip);                                      \
            VU_APPLY_MATRIX(p0, m, base);                                                 \
            VU_APPLY_MATRIX(p1, m, tip);                                                  \
            VU_SUB_XYZ(d0, p3, p2);                                                       \
            VU0_NORMALIZE(d0, d0);                                                        \
            VU_SUB_XYZ(d1, p1, p0);                                                       \
            VU0_NORMALIZE(d1, d1);                                                        \
            VU_INNER_PRODUCT(d, d0, d1);                                                  \
            angle = iosGetACosfExact(d);                                                  \
            VU_OUTER_PRODUCT(axis, d0, d1);                                               \
            VU_INTER_VECTOR(mid0, p0, p2, 0.5f);                                          \
            VU_INTER_VECTOR(mid1, p1, p3, 0.5f);                                          \
            VU_SUB_XYZ(plane, p2, p0);                                                    \
            VU0_NORMALIZE(plane, plane);                                                  \
            CompletePlaneD(plane, mid0);                                                  \
            VU_SUB_XYZ(tmp, p3, p1);                                                      \
            VU0_NORMALIZE(tmp, tmp);                                                      \
            VU_OUTER_PRODUCT(tmp, tmp, axis);                                             \
            VU_INNER_PRODUCT(d, plane, tmp);                                              \
            if (d < 0.0f ? d < -0.001f : d > 0.001f) {                                    \
                VU_SCALE_XYZW(tmp, tmp, -GetPointDistanceFromPlane(plane, mid1) / d);     \
                VU_ADD_XYZ(center, mid1, tmp);                                            \
                memset(quat, 0, sizeof(quat));                                            \
                quat[3] = 1.0f;                                                           \
                SetQuaternionByAxisRotateV(rot, -(int)(angle * 0.1f * 32768.0f / 3.1415926f), \
                                           axis);                                         \
                VU_SUB_XYZ(rel0, p2, center);                                             \
                VU_SUB_XYZ(rel1, p3, center);                                             \
                iosgluGetViewCoordPosition(uv0, p2);                                      \
                uv0[0] = (uv0[0] + 256.0f) * 256.0f / getDrawScreenWidth();               \
                uv0[1] = (uv0[1] + 224.0f) * 256.0f / getDrawScreenHeight();              \
                iosgluGetViewCoordPosition(uv1, p3);                                      \
                uv1[0] = (uv1[0] + 256.0f) * 256.0f / getDrawScreenWidth();               \
                uv1[1] = (uv1[1] + 224.0f) * 256.0f / getDrawScreenHeight();              \
                for (i = 0; i < 10; i++) {                                                \
                    VU_QUAT_ROT_TRANS(cur0, quat, rel0, center);                          \
                    VU_QUAT_ROT_TRANS(cur1, quat, rel1, center);                          \
                    VU_QUAT_MUL(quat, rot, quat);                                         \
                    if (i > 0) {                                                          \
                        float a0 = (9 - i) * 0.1f * 1.6f;                                 \
                        float a1 = (10 - i) * 0.1f * 1.6f;                                \
                                                                                          \
                        if (!(a0 <= 1.0f)) {                                              \
                            a0 = 1.0f;                                                    \
                        }                                                                 \
                        a0 *= 0.8f;                                                       \
                        if (!(a1 <= 1.0f)) {                                              \
                            a1 = 1.0f;                                                    \
                        }                                                                 \
                        a1 *= 0.8f;                                                       \
                        glBegin(5);                                                       \
                        glColor4f(0.5f, 0.5f, 0.5f, a0 * 0.3f);                           \
                        glTexCoord2f(uv1[0], uv1[1]);                                     \
                        glVertex3fv(cur1);                                                \
                        glColor4f(0.5f, 0.5f, 0.5f, a0);                                  \
                        glTexCoord2f(uv0[0], uv0[1]);                                     \
                        glVertex3fv(cur0);                                                \
                        glColor4f(0.5f, 0.5f, 0.5f, a1 * 0.3f);                           \
                        glTexCoord2f(uv1[0], uv1[1]);                                     \
                        glVertex3fv(prev1);                                               \
                        glColor4f(0.5f, 0.5f, 0.5f, a1);                                  \
                        glTexCoord2f(uv0[0], uv0[1]);                                     \
                        glVertex3fv(prev0);                                               \
                        glEnd();                                                          \
                    }                                                                     \
                    *(u_long128 *)prev0 = *(u_long128 *)cur0;                             \
                    *(u_long128 *)prev1 = *(u_long128 *)cur1;                             \
                }                                                                         \
            }                                                                             \
            glZOffset(1.0f);                                                              \
            glDisable(0);                                                                 \
            glDisable(0x14);                                                              \
            glEnable(2);                                                                  \
            glEnable(3);                                                                  \
            glDisable(8);                                                                 \
            iosDlPopLayer();                                                              \
        }                                                                                 \
    }

void DispWithSwordBlur(GameObj *weapon, GameObj *holder)
{
    DISP_WEAPON_BLUR(holder, weapon, -0.55f);
}

void DispWithTorchBlur(GameObj *weapon, GameObj *holder)
{
    DISP_WEAPON_BLUR(holder, weapon, -0.8f);
}
#endif

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
