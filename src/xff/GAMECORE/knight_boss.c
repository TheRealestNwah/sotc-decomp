extern char rootPtn[];
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern void isysJumpSubThread(void (*)(void), void *);
extern int SCRGetSizeOfBossWork(void *);
extern int SCRCharaInitBossWork(int, void *);
extern void SCRReleaseBossWork(void);
extern void SetScriptCharacterObjReleaseCallBackFunc(void *, void (*)(void), int);
extern char *GetScriptClass(void *);
extern void initScriptDataSystem(void *, int);
extern int *GameObject_KNIGHT_ARM_PARTS;
extern int *GameObject_KNIGHT_ARM_BREAK;
extern int *GameObject_KNIGHT_NECK_PARTS;
extern int *GameObject_KNIGHT_NECK_BREAK;
extern int _gameFlagChk(int);
extern void _SCRStartLWS(int, int, int, int *);
/* Knight arm/neck break: starts the PARTS LWS, rebuilds each break part's geometry from the node quaternion (VU0 basis from the quaternion, run twice) and starts the BREAK LWS, then sets the game flags. One local struct {pos, rot, q} pins the frame (pos +0, rot +0x10, q +0x20). */
typedef struct {
    char p0[8];
    int id;
}
GameObj;
typedef struct {
    float x, y, z, w;
} Vec;
extern GameObj *SkelFocusDef_KNIGHT_UDE_R;
extern GameObj *SkelFocusDef_KNIGHT_NECK;
extern char YUnitVector[];
extern int chkGameFlagForGameObj(int);
extern int setGameFlagForGameObj(int);
extern void GetMotionNodeQuaternionPos(void *, void *, void *, int, int);
extern void StabilizeToYRotQuaternion(void *);
extern int SCRSetLWSGeometryWithZY(int, int, void *, void *, void *);
extern char *GetSCRCharaAIWorkPtr(void *);
extern char *getSCRDataCtrlWork(void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void *getPlayerColCont2(int);
extern int ColCont2_IsColStatus(void *, long, long);
extern int *ScriptCtrlDef_SCRKnightMoveStop;
extern int *ScriptCtrlDef_SCRKnightShackHead;
extern int *ScriptCtrlDef_SCRKnightShackBody;
extern int *ScriptCtrlDef_SCRKnightShackArmRight;
extern int *ScriptCtrlDef_SCRKnightShackArmLeft;
typedef struct { char pad[0x180]; float dt; } GcGlobal;
extern GcGlobal gcGlobalVar;
#define DT (gcGlobalVar.dt)
#define COL(a) ColCont2_IsColStatus(getPlayerColCont2(*(int *)(scr + 0x4078)), 0x3F0, (a))
extern void SCRExecBossPreProcess(int);
extern void SCRExecBossPostProcess(int);
extern void updateScriptDataSystem(void *);
extern void scrRunM(int);
extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));

static void func_00063820(int *boss);

void nico_KnightBossStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, SCRGetSizeOfBossWork(th) + 0x41F3);
    char *c;
    int *w;
    int r;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = (int *)_SCRMallocAlign(part, 0x41C0, 0x10);
    *(int **)(c + 0x1200) = w;
    r = SCRCharaInitBossWork(part, th);
    *w = r;
    SetScriptCharacterObjReleaseCallBackFunc(th, SCRReleaseBossWork, r);
    CharaCtrlResetCtrlStatus(th);
    initScriptDataSystem(th, *(int *)(GetScriptClass(th) + 0x48));
    w[0x41B0 / 4] = 0;
    w[0x41B4 / 4] = 0;
    w[0x41B8 / 4] = 0;
    if (_gameFlagChk(0x10A)) {
        _SCRStartLWS(GameObject_KNIGHT_ARM_PARTS[2], -1, 1, 0);
        _SCRStartLWS(GameObject_KNIGHT_ARM_BREAK[2], -1, 1, 0);
    }
    if (_gameFlagChk(0x10B)) {
        _SCRStartLWS(GameObject_KNIGHT_NECK_PARTS[2], -1, 1, 0);
        _SCRStartLWS(GameObject_KNIGHT_NECK_BREAK[2], -1, 1, 0);
    }
    isysJumpSubThread(func_00063820, w);
}

static void func_000631A0(void *character)
{
    struct {
        Vec pos;
        Vec rot;
        Vec q;
    } L __attribute__((aligned(16)));

    if (chkGameFlagForGameObj((*(GameObj * *)&GameObject_KNIGHT_ARM_BREAK)->id) == 0) {
        _SCRStartLWS((*(GameObj * *)&GameObject_KNIGHT_ARM_PARTS)->id, -1, 6, 0);
        _SCRStartLWS((*(GameObj * *)&GameObject_KNIGHT_NECK_PARTS)->id, -1, 6, 0);
        GetMotionNodeQuaternionPos(&L.q, &L.pos, character, SkelFocusDef_KNIGHT_UDE_R->id, 1);
        StabilizeToYRotQuaternion(&L.q);
        __asm__ __volatile__("lqc2 vf4, 0x0(%0)
"
                             "vmul.xyzw vf5, vf4, vf4
"
                             "vmr32.xyzw vf6, vf4
"
                             "vmul.xyzw vf7, vf6, vf4
"
                             "vmr32.xyzw vf6, vf6
"
                             "vmul.xyzw vf8, vf6, vf4
"
                             "vsubx.z vf6, vf0, vf5x
"
                             "vsuby.z vf6, vf6, vf5y
"
                             "vaddw.y vf6, vf7, vf7w
"
                             "vsuby.x vf6, vf8, vf8y
"
                             "vsub.w vf6, vf0, vf0
"
                             "vadd.w vf5, vf0, vf0
"
                             "vmulw.xyz vf6, vf6, vf5w
"
                             "vaddw.z vf6, vf6, vf0w
"
                             "sqc2 vf6, 0x0(%1)
"
                             :
                             : "r"(&L.q), "r"(&L.rot)
                             : "memory");
        SCRSetLWSGeometryWithZY((*(GameObj * *)&GameObject_KNIGHT_ARM_BREAK)->id, 0, &L.pos, &L.rot, YUnitVector);
        GetMotionNodeQuaternionPos(&L.q, &L.pos, character, SkelFocusDef_KNIGHT_NECK->id, 0);
        StabilizeToYRotQuaternion(&L.q);
        __asm__ __volatile__("lqc2 vf4, 0x0(%0)
"
                             "vmul.xyzw vf5, vf4, vf4
"
                             "vmr32.xyzw vf6, vf4
"
                             "vmul.xyzw vf7, vf6, vf4
"
                             "vmr32.xyzw vf6, vf6
"
                             "vmul.xyzw vf8, vf6, vf4
"
                             "vsubx.z vf6, vf0, vf5x
"
                             "vsuby.z vf6, vf6, vf5y
"
                             "vaddw.y vf6, vf7, vf7w
"
                             "vsuby.x vf6, vf8, vf8y
"
                             "vsub.w vf6, vf0, vf0
"
                             "vadd.w vf5, vf0, vf0
"
                             "vmulw.xyz vf6, vf6, vf5w
"
                             "vaddw.z vf6, vf6, vf0w
"
                             "sqc2 vf6, 0x0(%1)
"
                             :
                             : "r"(&L.q), "r"(&L.rot)
                             : "memory");
        SCRSetLWSGeometryWithZY((*(GameObj * *)&GameObject_KNIGHT_NECK_BREAK)->id, 0, &L.pos, &L.rot, YUnitVector);
        _SCRStartLWS((*(GameObj * *)&GameObject_KNIGHT_ARM_BREAK)->id, -1, 6, 0);
        _SCRStartLWS((*(GameObj * *)&GameObject_KNIGHT_NECK_BREAK)->id, -1, 6, 0);
        setGameFlagForGameObj((*(GameObj * *)&GameObject_KNIGHT_ARM_BREAK)->id);
        setGameFlagForGameObj((*(GameObj * *)&GameObject_KNIGHT_NECK_BREAK)->id);
    }
}

int SCRFuncKnightParentMoveControlScriptKey(void *chara, float waitTime, float moveTime, float stopTime)
{
    char *ai;
    char *scr;
    int flag;
    float t;
    float u;
    int n;

    ai = GetSCRCharaAIWorkPtr(chara);
    scr = getSCRDataCtrlWork(chara);
    flag = *(int *)(ai + 0x41B0);
    if (flag & 2) {
        t = *(float *)(ai + 0x41B4);
        if (t < stopTime) {
            u = t + DT;
            *(float *)(ai + 0x41B4) = u;
            t = u;
        }
        if (stopTime <= t) {
            register int *p asm("$3") = ScriptCtrlDef_SCRKnightMoveStop; /* pins the pointer to $v1 like the Original */

            CharaCtrlSetScriptCtrlStatus(chara, p[1]);
            flag = *(int *)(ai + 0x41B0);
        }
        if (flag & 1) {
            *(float *)(ai + 0x41B4) += DT;
            if (moveTime + stopTime <= *(float *)(ai + 0x41B4)) {
                n = flag ^ 3;
                *(float *)(ai + 0x41B4) = 0.0f;
                *(int *)(ai + 0x41B0) = n;
                flag = n;
            }
        }
    }
    if (flag & 4) {
        *(float *)(ai + 0x41B8) += DT;
        __asm__ volatile("" ::: "memory");
        if (COL(0x10) || COL(0x20)) {
            *(float *)(ai + 0x41B8) += DT;
        }
        if (waitTime <= *(float *)(ai + 0x41B8)) {
            *(float *)(ai + 0x41B8) = 0.0f;
            *(int *)(ai + 0x41B0) ^= 4;
        }
    } else {
        if (COL(0x10) || COL(0x20)) {
            CharaCtrlSetScriptCtrlStatus(chara, ScriptCtrlDef_SCRKnightShackHead[1]);
        }
        if (COL(0x160) || COL(0x170) || COL(0x180) || COL(0x190) || COL(0x1A0) || COL(0x1C0) || COL(0x1E0) ||
            COL(0x1F0) || COL(0x50)) {
            CharaCtrlSetScriptCtrlStatus(chara, ScriptCtrlDef_SCRKnightShackBody[1]);
        }
        if (COL(0x60) || COL(0xE0) || COL(0xF0) || COL(0xA0) || COL(0xB0) || COL(0x40)) {
            CharaCtrlSetScriptCtrlStatus(chara, ScriptCtrlDef_SCRKnightShackArmRight[1]);
        }
        if (COL(0x80) || COL(0x100) || COL(0x110) || COL(0xC0) || COL(0xD0)) {
            CharaCtrlSetScriptCtrlStatus(chara, ScriptCtrlDef_SCRKnightShackArmLeft[1]);
        }
    }
}

static void func_00063820(int *boss)
{
    isysGetThisSubThread();
    for (;;) {
        void *th = isysGetThisSubThread();

        SCRExecBossPreProcess(*boss);
        CharaCtrlResetAllScriptCtrlStatus(th);
        updateScriptDataSystem(th);
        isysGetThisSubThread();
        SCRExecBossPostProcess(*boss);
        scrRunM(1);
    }
}

void SCRKnightBossPartsBroken(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_000631A0);
}
