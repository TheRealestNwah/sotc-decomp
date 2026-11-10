typedef struct { int pad0; int status; } ScriptCtrlDef;

extern ScriptCtrlDef *ScriptCtrlDef_SCRAccel;
extern ScriptCtrlDef *ScriptCtrlDef_SCRDash;
extern ScriptCtrlDef *ScriptCtrlDef_SCRStopL;
extern ScriptCtrlDef *ScriptCtrlDef_SCRStopR;
extern ScriptCtrlDef *ScriptCtrlDef_SCRFastL;
extern ScriptCtrlDef *ScriptCtrlDef_SCRFastR;
extern ScriptCtrlDef *ScriptCtrlDef_SCRStop;
extern ScriptCtrlDef *ScriptCtrlDef_SCRBack;
extern ScriptCtrlDef *ScriptCtrlDef_SCRTransL;
extern ScriptCtrlDef *ScriptCtrlDef_SCRTransR;
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern float adjustAnglePI(float);
extern float fabsf(float);

static void func_0010F710(char *c, int mode)
{
    char *s = *(char **)(c + 0xCC);
    float a;
    float b;
    float d;

    switch (mode) {
    case 0:
        if (*(int *)(*(char **)(c + 0x14) + 0x750) != *(int *)(s + 0x20))
            return;
        CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRAccel->status);
        if (*(int *)(s + 0x30) != 0)
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRDash->status);
        return;
    case 2:
        a = *(float *)(c + 0x158);
        b = -a;
        d = adjustAnglePI(*(float *)(c + 0x1DC) - a);
        if (*(int *)(s + 0x9C) != 0 && fabsf(*(float *)(c + 0x158)) > 1.5707963f &&
            fabsf(d - b) >= 3.1415927f)
            a = *(float *)(c + 0x1DC);
        if (0.0f <= a)
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRStopR->status);
        else
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRStopL->status);
        return;
    case 1:
        if (0.0f <= *(float *)(c + 0x158))
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRFastR->status);
        else
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRFastL->status);
        return;
    case 3:
        CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRStop->status);
        return;
    case 4:
        CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRBack->status);
        return;
    case 5:
        CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRStop->status);
        return;
    case 6:
        if (0.0f <= *(float *)(c + 0x130)) {
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRTransR->status);
            return;
        } else
            CharaCtrlSetScriptCtrlStatus(*(int *)(c + 8), ScriptCtrlDef_SCRTransL->status);

    }
}

