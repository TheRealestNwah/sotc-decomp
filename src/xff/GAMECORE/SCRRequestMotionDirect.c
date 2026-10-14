extern void CharaCtrlSetScriptCtrlStatus();

void SCRRequestMotionDirect(int a, int *b)
{
    if (b != 0) {
        CharaCtrlSetScriptCtrlStatus(a, b[1]);
    }
}
