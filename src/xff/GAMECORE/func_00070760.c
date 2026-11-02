extern int ScriptCtrlDef_SCRPlayerSightOnTurnLeft;
extern int ScriptCtrlDef_SCRHorseSightOnTurnLeft;
extern int ScriptCtrlDef_SCRPlayerSightOnTurnRight;
extern int ScriptCtrlDef_SCRHorseSightOnTurnRight;
extern void func_000708E0(void *, int, int);

static void func_00070760(void *a)
{
    func_000708E0(a, ScriptCtrlDef_SCRPlayerSightOnTurnLeft, ScriptCtrlDef_SCRHorseSightOnTurnLeft);
}

static void func_00070788(void *a)
{
    func_000708E0(a, ScriptCtrlDef_SCRPlayerSightOnTurnRight, ScriptCtrlDef_SCRHorseSightOnTurnRight);
}
