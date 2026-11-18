extern void *isysGetThisSubThread(void);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern void updateUserPathWork(void *, void *);
extern void updateHumanCtrlWork(void *, void *, void *);
extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern void updateGazeIKWork(void *, void *);
extern void guardDamageMain(void *obj, int front, int back);
extern void guardMainCommon(void *, int *, void *, void *, int, float, float);
extern void scrRunM(int);
extern char *GameObject_DORMIN_P;
extern char *GameObject_SHAMAN_P;
extern int ScriptCtrlDef_SCRGuardAttack;

static void func_00056740(char *w)
{
    void *th = isysGetThisSubThread();
    char *hc = w + 0x3C70;
    char *pw = w + 0x10;
    int state = 0;

    while (1) {
        void *t = isysGetThisSubThread();
        void *obj = *(void **)(GameObject_DORMIN_P + 8);
        CharaCtrlResetAllScriptCtrlStatus(t);
        updateUserPathWork(t, w + 0x10);
        updateHumanCtrlWork(t, hc, w + 0x10);
        updateGazeIKWork(GetCharacterClass(t), *(void **)(GetLayoutClass(obj) + 0x134));
        guardDamageMain(th, *(int *)(w + 0x3CB4), *(int *)(w + 0x3CB8));
        if (*(int *)(GameObject_SHAMAN_P + 8) != 0 && *(int *)(GameObject_DORMIN_P + 8) != 0)
            guardMainCommon(th, &state, pw, hc, ScriptCtrlDef_SCRGuardAttack, *(float *)(w + 0x3CB0), 1.5f);
        isysGetThisSubThread();
        scrRunM(1);
    }
}
