/* ~171 diffs, same length (222 words). Leo torch sub-thread loop: boss pre/post process, four torch layouts + four TORCH_ANIM layouts get SCRLeoTorchFinish / SCRTorchRebirth ctrl status depending on B_0018AF80 (0 idle, 1 finished, 2 reset). Original keeps StageLayout_LEO_TORCH1..3 in s0/s3/s4 and the ScriptCtrlDef pointers in s6/s5 across the loop; ours does not hoist them. */
extern int **ScriptCtrlDef_SCRLeoTorchFinish;
extern int **ScriptCtrlDef_SCRTorchRebirth;
extern char *StageLayout_LEO_TORCH0;
extern char *StageLayout_LEO_TORCH1;
extern char *StageLayout_LEO_TORCH2;
extern char *StageLayout_LEO_TORCH3;
extern char *StageLayout_LEO_TORCH0_ANIM;
extern char *StageLayout_LEO_TORCH1_ANIM;
extern char *StageLayout_LEO_TORCH2_ANIM;
extern char *StageLayout_LEO_TORCH3_ANIM;
extern char gcGlobalVar[];
extern int B_0018AF80;
extern void *isysGetThisSubThread(void);
extern void SCRExecBossPreProcess(int);
extern void SCRExecBossPostProcess(int);
extern void CharaCtrlResetAllScriptCtrlStatus(int);
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern void updateScriptDataSystem(void *);
extern void *SCRGetFirstObj(void *);
extern void *getTorchObj(void *);
extern int _omakeGetFlagChk(int);
extern char *GetLayoutClass(void *);
extern int nico_GetGeometryPointerAttr(void *);
extern void scrRunM(int);

#ifdef NONMATCHING
void func_00063C70(int *arg)
{
    isysGetThisSubThread();
    for (;;) {
        void *th = isysGetThisSubThread();
        void *torch;
        SCRExecBossPreProcess(arg[0]);
        CharaCtrlResetAllScriptCtrlStatus((int)th);
        updateScriptDataSystem(th);
        if (*(int *)(StageLayout_LEO_TORCH0 + 0x48) &&
            *(int *)(StageLayout_LEO_TORCH1 + 0x48) &&
            *(int *)(StageLayout_LEO_TORCH2 + 0x48) &&
            *(int *)(StageLayout_LEO_TORCH3 + 0x48)) {
            torch = getTorchObj(SCRGetFirstObj(gcGlobalVar + 0x2B0));
            if (_omakeGetFlagChk(0x10)) {
                CharaCtrlSetScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH0_ANIM + 0x48), (*ScriptCtrlDef_SCRLeoTorchFinish)[1]);
                CharaCtrlSetScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH1_ANIM + 0x48), (*ScriptCtrlDef_SCRLeoTorchFinish)[1]);
                CharaCtrlSetScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH2_ANIM + 0x48), (*ScriptCtrlDef_SCRLeoTorchFinish)[1]);
                CharaCtrlSetScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH3_ANIM + 0x48), (*ScriptCtrlDef_SCRLeoTorchFinish)[1]);
                B_0018AF80 = 1;
            }
            if (B_0018AF80 == 2) {
                CharaCtrlResetAllScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH0_ANIM + 0x48));
                CharaCtrlResetAllScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH1_ANIM + 0x48));
                CharaCtrlResetAllScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH2_ANIM + 0x48));
                CharaCtrlResetAllScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH3_ANIM + 0x48));
                B_0018AF80 = 0;
            }
            if (GetLayoutClass((void *)*(int *)(StageLayout_LEO_TORCH0 + 0x48))[0x1B8] == 0 &&
                GetLayoutClass((void *)*(int *)(StageLayout_LEO_TORCH1 + 0x48))[0x1B8] == 0 &&
                GetLayoutClass((void *)*(int *)(StageLayout_LEO_TORCH2 + 0x48))[0x1B8] == 0 &&
                GetLayoutClass((void *)*(int *)(StageLayout_LEO_TORCH3 + 0x48))[0x1B8] == 0 &&
                B_0018AF80 == 1 && torch != 0 &&
                *(int *)(GetLayoutClass(torch) + 0x124) != 0 &&
                (nico_GetGeometryPointerAttr(GetLayoutClass(torch) + 0xC0) & 0x1E00000) != 0x200000 &&
                (nico_GetGeometryPointerAttr(GetLayoutClass(torch) + 0xC0) & 0x1E00000) != 0x400000) {
                CharaCtrlResetAllScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH0_ANIM + 0x48));
                CharaCtrlResetAllScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH1_ANIM + 0x48));
                CharaCtrlResetAllScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH2_ANIM + 0x48));
                CharaCtrlResetAllScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH3_ANIM + 0x48));
                CharaCtrlSetScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH0_ANIM + 0x48), (*ScriptCtrlDef_SCRTorchRebirth)[1]);
                CharaCtrlSetScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH1_ANIM + 0x48), (*ScriptCtrlDef_SCRTorchRebirth)[1]);
                CharaCtrlSetScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH2_ANIM + 0x48), (*ScriptCtrlDef_SCRTorchRebirth)[1]);
                CharaCtrlSetScriptCtrlStatus(*(int *)(StageLayout_LEO_TORCH3_ANIM + 0x48), (*ScriptCtrlDef_SCRTorchRebirth)[1]);
                B_0018AF80 = 2;
            }
        }
        isysGetThisSubThread();
        SCRExecBossPostProcess(arg[0]);
        scrRunM(1);
    }
}
#endif
