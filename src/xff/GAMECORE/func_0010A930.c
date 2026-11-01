extern int *ScriptCtrlDef_SCRAccel;
extern int *ScriptCtrlDef_SCRDash;
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern int func_0010A540(void *, void *);

static void func_0010A930(char *o, void *arg)
{
    char *p = *(char **)(o + 0xCC);

    CharaCtrlSetScriptCtrlStatus(*(int *)(o + 8), ScriptCtrlDef_SCRAccel[1]);
    if (func_0010A540(o, arg) != 0) {
        CharaCtrlSetScriptCtrlStatus(*(int *)(o + 8), ScriptCtrlDef_SCRDash[1]);
        return;
    }
    if (*(float *)(p + 0x40) < *(float *)(o + 0xAC)) {
        *(int *)(*(char **)(o + 0x14) + 0x5E4) = 0;
    }
}
