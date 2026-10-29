extern void CharaCtrlSetScriptCtrlStatus(void *, int);
void SCRRequestMotionDirect(void *actor, int *request)
{
    if (request != 0)
        CharaCtrlSetScriptCtrlStatus(actor, request[1]);
}
