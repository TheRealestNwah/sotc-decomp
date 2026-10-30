extern int *ScriptCtrlDef_SCRStop;
extern int *ScriptCtrlDef_SCRGoL;
extern int *ScriptCtrlDef_SCRGoR;
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void func_00106C80(void **, int);

static void func_00106B68(void **chara, int command, float angle)
{
    switch (command) {
    case 3:
        CharaCtrlSetScriptCtrlStatus(chara[2], ScriptCtrlDef_SCRStop[1]);
        return;
    case 0:
        if (!(1.5707962f < __builtin_fabsf(angle))) {
            func_00106C80(chara, 1);
            return;
        }
        if (!(0 <= angle)) {
            CharaCtrlSetScriptCtrlStatus(chara[2], ScriptCtrlDef_SCRGoL[1]);
            return;
        }
        CharaCtrlSetScriptCtrlStatus(chara[2], ScriptCtrlDef_SCRGoR[1]);
        return;
    case 2:
        func_00106C80(chara, 1);
        return;
    case 5:
        if (0 <= angle) {
            CharaCtrlSetScriptCtrlStatus(chara[2], ScriptCtrlDef_SCRGoR[1]);
            return;
        }
        CharaCtrlSetScriptCtrlStatus(chara[2], ScriptCtrlDef_SCRGoL[1]);
        break;
    case 1:
    case 4:
        break;
    }
}
