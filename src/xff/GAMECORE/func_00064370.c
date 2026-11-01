extern char gcGlobalVar[];
extern int B_0018AF80;
extern char *StageLayout_LEO_TORCH0;
extern char *StageLayout_LEO_TORCH1_ANIM;
extern char *StageLayout_LEO_TORCH2_ANIM;
extern char *StageLayout_LEO_TORCH3_ANIM;
extern int *ScriptCtrlDef_SCRLeoTorchFinish;
extern void SetLayoutObjAccessSwitch(void *, int);
extern void *SCRGetFirstObj(void *);
extern void torchObjRelease(void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);

static void func_00064370(void *character)
{
    SetLayoutObjAccessSwitch(*(void **)(StageLayout_LEO_TORCH0 + 0x48), 1);
    B_0018AF80 = 1;
    torchObjRelease(SCRGetFirstObj(gcGlobalVar + 0x2B0));
    CharaCtrlSetScriptCtrlStatus(*(void **)(StageLayout_LEO_TORCH1_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
    CharaCtrlSetScriptCtrlStatus(*(void **)(StageLayout_LEO_TORCH2_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
    CharaCtrlSetScriptCtrlStatus(*(void **)(StageLayout_LEO_TORCH3_ANIM + 0x48), ScriptCtrlDef_SCRLeoTorchFinish[1]);
}
