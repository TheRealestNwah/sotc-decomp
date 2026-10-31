extern char *StageLayout_LEO_TORCH2;
extern char *StageLayout_LEO_TORCH0_ANIM;
extern char *StageLayout_LEO_TORCH1_ANIM;
extern char *StageLayout_LEO_TORCH3_ANIM;
extern int *ScriptCtrlDef_SCRLeoTorchFinish;
extern int B_0018AF80;
extern char gcGlobalVar[];
extern void SetLayoutObjAccessSwitch(int, int);
extern void *SCRGetFirstObj(void *);
extern void torchObjRelease(void *);
extern void CharaCtrlSetScriptCtrlStatus(int, int);

static void T_000644B0(void)
{
    SetLayoutObjAccessSwitch(*(int *)(StageLayout_LEO_TORCH2 + 0x48), 1);
    B_0018AF80 = 1;
    torchObjRelease(SCRGetFirstObj(gcGlobalVar + 0x2B0));
    CharaCtrlSetScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH0_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
    CharaCtrlSetScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH1_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
    CharaCtrlSetScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH3_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
}
