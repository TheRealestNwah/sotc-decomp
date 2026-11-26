typedef struct {
    char pad[0x24];
    float radius;
    float scale;
    char pad2C[0x8];
} AnimalType;
typedef struct {
    char pad[0x10];
    AnimalType *types;
} AnimalTypeTable;
typedef struct {
    char pad[0x10];
    float minRadius;
    short type;
    char pad16[0x8];
    unsigned short flags;
    float maxRadius;
} SpawnParam;
extern AnimalTypeTable SH_SmallAnimalTypeDEFAULT;
extern void AI_GetRandomCylinderOfs(float *, float, float, float, float);
static inline void vecAddXYZ(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}
/* Main script loop of the snake (bag) boss's body. Each frame it resets the script
   control, clears the front/centre/back flags at +0x5A80/84/88, then walks the character's parts
   (stride 0x80): a deflating motion (F/M/B_DEFLATE0/1) of a part starts the matching SCRSnakeFade
   control, and while the damage class is in state 1/2/4 a *_DEFLATE_SWELLING part hit at the right
   attack point (0x20 front, 0x180 centre, 0x190 back) plays the fade effect. Never returns (loops on
   scrRunM). */
typedef struct {
    char pad0[4];
    int ctrl;
}
ScriptCtrlDef;
extern int MotionKind_SNAKE_C_B_DEFLATE0;
extern int MotionKind_SNAKE_C_B_DEFLATE1;
extern int MotionKind_SNAKE_C_B_DEFLATE_SWELLING;
extern int MotionKind_SNAKE_C_F_DEFLATE0;
extern int MotionKind_SNAKE_C_F_DEFLATE1;
extern int MotionKind_SNAKE_C_F_DEFLATE_SWELLING;
extern int MotionKind_SNAKE_C_M_DEFLATE0;
extern int MotionKind_SNAKE_C_M_DEFLATE1;
extern int MotionKind_SNAKE_C_M_DEFLATE_SWELLING;
extern int ScriptAnimationObjDef_SNAKE_BAG_FADE_EFF;
extern ScriptCtrlDef *ScriptCtrlDef_SCRSnakeFadeBack;
extern ScriptCtrlDef *ScriptCtrlDef_SCRSnakeFadeCenter;
extern ScriptCtrlDef *ScriptCtrlDef_SCRSnakeFadeFront;
extern void CharaCtrlResetAllScriptCtrlStatus(int);
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern char *GetCharacterClass(int);
extern char *GetDamageClass(int);
extern void SCRExecBossPostProcess(int);
extern void SCRExecBossPreProcess(int);
extern void _SCRPlayLWSWithTargetAttackedPoint(int, int);
extern int isysGetThisSubThread(void);
extern int nico_GetCharacterAttackedGPAttr(int, int);
extern void scrRunM(int);
extern void updateScriptDataSystem(int);
extern char rootPtn[];
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern void isysJumpSubThread(void (*)(void), void *);
extern int SCRGetSizeOfBossWork(void *);
extern int SCRCharaInitBossWork(int, void *);
extern void SCRReleaseBossWork(void);
extern void SetScriptCharacterObjReleaseCallBackFunc(void *, void (*)(void), int);
extern char *GetScriptClass(void *);
extern void initScriptDataSystem(void *, int);
extern void getWormIKWork(void *);
typedef struct {
    char pad0[0x1AC];
    int mode;
} LayoutClass;
typedef struct {
    char pad0[0x409C];
    int status;
} SCRWork;
extern int SCRModeStatus_SNAKE_ROUTE_PATROL_MIDDLE;
extern int SCRModeStatus_SNAKE_ROUTE_PATROL_TAKE_OFF;
extern LayoutClass *GetLayoutClass(void);
extern SCRWork *getSCRDataCtrlWork(void *);

static void func_000BBED8(void *obj);

int NamazuInitFunc(float *pos, void *a1, void *a2, SpawnParam *p, int force)
{
    AnimalType *types = SH_SmallAnimalTypeDEFAULT.types;
    float ofs[4];
    float rmin, rmax, s;
    int ret = 0;

    if (p == 0)
        return ret;
    if (types == 0)
        return ret;
    if ((p->flags & 1) && !force) {
        rmax = 0.0f;
        rmin = rmax;
    } else {
        float r = types[p->type].radius;
        float a = p->minRadius;
        float b = p->maxRadius * 0.6f;

        rmin = r < a ? r : a;
        rmax = r < b ? r : b;
    }
    s = types[p->type].scale;
    AI_GetRandomCylinderOfs(ofs, rmin * s, rmin, rmax * s, rmax);
    vecAddXYZ(pos, pos, ofs);
    return ret;
}

static void func_000BBB50(char *boss)
{
    int self = isysGetThisSubThread();

    for (;;) {
        int i = 0;
        int t = isysGetThisSubThread();
        char *part;
        char *damage;

        SCRExecBossPreProcess(*(int *)boss);
        CharaCtrlResetAllScriptCtrlStatus(t);
        updateScriptDataSystem(t);
        part = (char *)*(int *)(GetCharacterClass(self) + 0x30C);
        *(int *)(boss + 0x5A80) = 0;
        *(int *)(boss + 0x5A84) = 0;
        *(int *)(boss + 0x5A88) = 0;
        damage = GetDamageClass(self);
        while (i < *(int *)(GetCharacterClass(self) + 0x3FC)) {
            if (*(int *)(part + 0x44) != -2) {
                if (*(int *)(boss + 0x5A8C) == 0) {
                    if (MotionKind_SNAKE_C_F_DEFLATE0 == *(int *)(part + 4) || MotionKind_SNAKE_C_F_DEFLATE1 == *(int *)(part + 4)) {
                        *(int *)(boss + 0x5A80) = 1;
                        CharaCtrlSetScriptCtrlStatus(self, ScriptCtrlDef_SCRSnakeFadeFront->ctrl);
                    } else if (MotionKind_SNAKE_C_M_DEFLATE0 == *(int *)(part + 4) || MotionKind_SNAKE_C_M_DEFLATE1 == *(int *)(part + 4)) {
                        *(int *)(boss + 0x5A84) = 1;
                        CharaCtrlSetScriptCtrlStatus(self, ScriptCtrlDef_SCRSnakeFadeCenter->ctrl);
                    } else if (MotionKind_SNAKE_C_B_DEFLATE0 == *(int *)(part + 4) || MotionKind_SNAKE_C_B_DEFLATE1 == *(int *)(part + 4)) {
                        *(int *)(boss + 0x5A88) = 1;
                        CharaCtrlSetScriptCtrlStatus(self, ScriptCtrlDef_SCRSnakeFadeBack->ctrl);
                    }
                }
                if (damage != 0) {
                    int st = *(int *)(damage + 0x60);

                    if (st == 1 || st == 4 || st == 2) {

                        if (MotionKind_SNAKE_C_F_DEFLATE_SWELLING == *(int *)(part + 4)) {
                            if (nico_GetCharacterAttackedGPAttr(self, 0x3F0) == 0x20) {
                                CharaCtrlSetScriptCtrlStatus(self, ScriptCtrlDef_SCRSnakeFadeFront->ctrl);
                                _SCRPlayLWSWithTargetAttackedPoint(ScriptAnimationObjDef_SNAKE_BAG_FADE_EFF, self);
                            }
                        } else if (MotionKind_SNAKE_C_M_DEFLATE_SWELLING == *(int *)(part + 4)) {
                            if (nico_GetCharacterAttackedGPAttr(self, 0x3F0) == 0x180) {
                                CharaCtrlSetScriptCtrlStatus(self, ScriptCtrlDef_SCRSnakeFadeCenter->ctrl);
                                _SCRPlayLWSWithTargetAttackedPoint(ScriptAnimationObjDef_SNAKE_BAG_FADE_EFF, self);
                            }
                        } else if (MotionKind_SNAKE_C_B_DEFLATE_SWELLING == *(int *)(part + 4) &&
                                   nico_GetCharacterAttackedGPAttr(self, 0x3F0) == 0x190) {
                            CharaCtrlSetScriptCtrlStatus(self, ScriptCtrlDef_SCRSnakeFadeBack->ctrl);
                            _SCRPlayLWSWithTargetAttackedPoint(ScriptAnimationObjDef_SNAKE_BAG_FADE_EFF, self);
                        }
                    }
                }
            }
            i++;
            part += 0x80;
        }
        *(int *)(boss + 0x5A8C) = 0;
        func_000BBED8(self);
        isysGetThisSubThread();
        SCRExecBossPostProcess(*(int *)boss);
        scrRunM(1);
    }
}

void nico_snakeCBossStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, SCRGetSizeOfBossWork(th) + 0x5AD3);
    char *c;
    int *w;
    int r;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = (int *)_SCRMallocAlign(part, 0x5AA0, 0x10);
    *(int **)(c + 0x1200) = w;
    r = SCRCharaInitBossWork(part, th);
    *w = r;
    SetScriptCharacterObjReleaseCallBackFunc(th, SCRReleaseBossWork, r);
    CharaCtrlResetCtrlStatus(th);
    initScriptDataSystem(th, *(int *)(GetScriptClass(th) + 0x48));
    getWormIKWork(th);
    w[0x5A80 / 4] = 0;
    w[0x5A84 / 4] = 0;
    w[0x5A88 / 4] = 0;
    w[0x5A8C / 4] = 0;
    w[0x5A90 / 4] = 0;
    isysJumpSubThread(func_000BBB50, w);
}

static void func_000BBED8(void *obj)
{
    LayoutClass *l = GetLayoutClass();
    SCRWork *w = getSCRDataCtrlWork(obj);

    l->mode = 0;
    if (w) {
        if (w->status == SCRModeStatus_SNAKE_ROUTE_PATROL_MIDDLE ||
            w->status == SCRModeStatus_SNAKE_ROUTE_PATROL_TAKE_OFF)
            l->mode = 10;
    }
}
