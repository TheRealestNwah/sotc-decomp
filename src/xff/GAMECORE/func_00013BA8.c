extern char gcGlobalVar[];
extern int *ScriptCtrlDef_SCRPlayerNoWeaponchange;
extern void *isysGetThisSubThread(void);
extern void scrInit(void *);
extern void scrRun(void);
extern void *SCRGetFirstObj(void *);
extern void CharaCtrlSetOutsideScriptCtrlStatus(void *, int);

static void func_00013BA8(void)
{
    scrInit(isysGetThisSubThread());
    for (;;) {
        void *o = SCRGetFirstObj(gcGlobalVar + 0x2B0);

        if (o != 0)
            CharaCtrlSetOutsideScriptCtrlStatus(o, ScriptCtrlDef_SCRPlayerNoWeaponchange[1]);
        scrRun();
    }
}
