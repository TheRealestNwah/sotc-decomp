typedef struct { int pad0; int status; } CtrlDef;
extern char gcGlobalVar[];
extern CtrlDef *ScriptCtrlDef_SCRPlayerHorseNear;
extern CtrlDef *ScriptCtrlDef_SCRPlayerHorseMiddleDistance;
extern CtrlDef *ScriptCtrlDef_SCRPlayerHorseFar;
extern CtrlDef *ScriptCtrlDef_SCRPlayerHorsePat;
extern CtrlDef *ScriptCtrlDef_SCRPlayerHorseDead;
extern int ControlMode_HORSE_DEFAULT;
extern int ControlMode_HORSE_DEATH;
extern int ControlMode_HORSE_DEATH_DOWN;
extern int isysGetThisSubThread(void);
extern int SCRGetFirstObj(void *);
extern char *GetLayoutClass(int);
extern char *GetCharacterClass(int);
extern void CharaCtrlSetScriptCtrlStatus(int, int);

static void func_000764B0(char *self)
{
    int th = isysGetThisSubThread();
    int horse = SCRGetFirstObj(gcGlobalVar + 0x2B4);
    char *l1;
    char *l2;
    float dist;
    char *cfg;

    if (horse != 0) {
    l1 = GetLayoutClass(th);
    l2 = GetLayoutClass(horse);
    __asm__ __volatile__("lqc2 vf5, 0x0(%2)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         ".word 0x4A2703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dist) : "r"(*(char **)(l2 + 0x134)), "r"(*(char **)(l1 + 0x134)) : "$2", "memory");
    cfg = *(char **)(self + 0x184);
    if (dist <= *(float *)(cfg + 0x50)) {
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRPlayerHorseNear->status);
    } else if (dist <= *(float *)(cfg + 0x4C)) {
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRPlayerHorseMiddleDistance->status);
    } else {
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRPlayerHorseFar->status);
    }
    if (dist < 3.0f && ControlMode_HORSE_DEFAULT == *(int *)(GetCharacterClass(horse) + 0x750)) {
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRPlayerHorsePat->status);
    }
    if (ControlMode_HORSE_DEATH == *(int *)(GetCharacterClass(horse) + 0x750) ||
        ControlMode_HORSE_DEATH_DOWN == *(int *)(GetCharacterClass(horse) + 0x750)) {
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRPlayerHorseDead->status);
    }
    } else {
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRPlayerHorseFar->status);
    }
}
