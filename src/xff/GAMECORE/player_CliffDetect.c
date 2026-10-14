extern void *GetCharacterClass(void *);

extern void CharaCtrlResetScriptCtrlStatus(void *, int);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern int func_0007E608(int, void *, int, int);
extern void *ScriptCtrlDef_SCRPlayerFallDanger;

void player_CliffDetect(void *arg0, int arg1) {
    void *temp_s0;

    temp_s0 = GetCharacterClass(arg0);
    CharaCtrlResetScriptCtrlStatus(arg0, (*(int *)((char *)(ScriptCtrlDef_SCRPlayerFallDanger) + 4)));
    if (func_0007E608(arg1 + 0x10, temp_s0 + 0xE20, (*(int *)((char *)(temp_s0) + 0x138)), (*(int *)((char *)(temp_s0) + 0x134))) != 0) {
        CharaCtrlSetScriptCtrlStatus(arg0, (*(int *)((char *)(ScriptCtrlDef_SCRPlayerFallDanger) + 4)));
    }
}
