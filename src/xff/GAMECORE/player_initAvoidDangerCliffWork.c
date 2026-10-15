typedef int s128 __attribute__((mode(TI)));
typedef unsigned int u128 __attribute__((mode(TI)));
extern void CharaCtrlResetScriptCtrlStatus(int, int);
extern void CopyGeometryPointer(void *, void *);
extern void *GetLayoutClass(int);
extern unsigned char InitialGeometryPointer[];
extern void *ScriptCtrlDef_SCRPlayerFallDanger;
extern void *ScriptCtrlDef_SCRPlayerHellDanger;

void player_initAvoidDangerCliffWork(int arg0, void *arg1)
{
    (*(int *)((char *)(arg1) + 0)) = 0;
    CopyGeometryPointer(arg1 + 0x10, InitialGeometryPointer);
    CopyGeometryPointer(arg1 + 0x70, InitialGeometryPointer);
    (*(s128 *)((char *)(arg1) + 0x50)) = (s128) *(*(s128 **)((char *)(GetLayoutClass(arg0)) + 0x134));
    CharaCtrlResetScriptCtrlStatus(arg0, (*(int *)((char *)(ScriptCtrlDef_SCRPlayerFallDanger) + 4)));
    CharaCtrlResetScriptCtrlStatus(arg0, (*(int *)((char *)(ScriptCtrlDef_SCRPlayerHellDanger) + 4)));
}
