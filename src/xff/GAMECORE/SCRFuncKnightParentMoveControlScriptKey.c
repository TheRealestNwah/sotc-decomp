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

#ifdef NONMATCHING /* 3 diffs: the ScriptCtrlDef load swaps $v0/$v1 (lui into $v0, pointer into $v1 in the Original); everything else matches. The permuter found nothing better in 1350 iterations */
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
            CharaCtrlSetScriptCtrlStatus(chara, ScriptCtrlDef_SCRKnightMoveStop[1]);
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
#endif
