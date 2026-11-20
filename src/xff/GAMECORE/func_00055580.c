extern int isysGetThisSubThread(void);
extern char *GameObject_DORMIN_P;
extern void CharaCtrlResetAllScriptCtrlStatus(int);
extern void updateUserPathWork(int, void *);
extern void updateHumanCtrlWork(int, void *, void *);
extern void *GetCharacterClass(int);
extern char *GetLayoutClass(int);
extern void updateGazeIKWork(void *, int);
extern void guardDamageMain(int, int, int);
extern int D_0017ABBC;
extern int D_0017ABC0;
extern void *memset(void *, int, unsigned int);
extern void setAttainRangeData(void *, float *, float, float, float, float);
extern void getPointPosFromEvent(void *, int, float *);
extern void setAttainmentPos(void *, float *);
extern void _setExecBaseMoveWork(void *, int);
extern int getWayFinish(void *);
extern char *ScriptCtrlDef_SCRGuardSwordPickup;
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern void scrRunM(int);

static void func_00055580(char *w)
{
    char *p = w + 0x10;
    char *h = w + 0x3C70;
    int th = isysGetThisSubThread();
    float a[4];
    float b[4];

    for (;;) {
        int t = isysGetThisSubThread();
        int obj = *(int *)(GameObject_DORMIN_P + 8);
        void *cc;

        CharaCtrlResetAllScriptCtrlStatus(t);
        updateUserPathWork(t, w + 0x10);
        updateHumanCtrlWork(t, h, w + 0x10);
        cc = GetCharacterClass(t);
        updateGazeIKWork(cc, *(int *)(GetLayoutClass(obj) + 0x134));
        guardDamageMain(th, *(int *)(w + 0x3CB0), *(int *)(w + 0x3CB4));
        if (D_0017ABBC == 0) {
                if (D_0017ABC0 == 0) {
                if (getWayFinish(p) != 0 && *(int *)(w + 0x3CB8) == 0) {
                    CharaCtrlSetScriptCtrlStatus(th, *(int *)(ScriptCtrlDef_SCRGuardSwordPickup + 4));
                    *(int *)(w + 0x3CB8) = 1;
                    D_0017ABC0 = 1;
                }
            } else if (*(int *)(w + 0x3CB8) != 0) {
                _setExecBaseMoveWork(h, 0);
            } else {
                memset(a, 0, 0x10);
                a[3] = 1.0f;
                setAttainRangeData(p, a, 0.0f, 2.0f, 3.1415926f, 10.0f);
            }
        } else {
            memset(b, 0, 0x10);
            b[3] = 1.0f;
            setAttainRangeData(p, b, 0.0f, 1.0f, 3.1415926f, 10.0f);
            getPointPosFromEvent(p, 0, a);
            setAttainmentPos(p, a);
            _setExecBaseMoveWork(h, 1);
        }
        isysGetThisSubThread();
        scrRunM(1);
    }
}

