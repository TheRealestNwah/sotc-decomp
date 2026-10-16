extern int *ScriptCtrlDef_SCRSlowDown;
extern int *ScriptCtrlDef_SCRStop;
extern char *GetCharacterClass(void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);

int _sendStopKeyMoveWork(void *o, int *w, int slow)
{
    char *c = GetCharacterClass(o);

    if (w[1] != 0)
        return 0;
    if (*(int *)(c + 0x750) == w[8])
        return 1;
    if (slow != 0)
        CharaCtrlSetScriptCtrlStatus(o, ScriptCtrlDef_SCRSlowDown[1]);
    else
        CharaCtrlSetScriptCtrlStatus(o, ScriptCtrlDef_SCRStop[1]);
    return 0;
}
