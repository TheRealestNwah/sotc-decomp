extern char rootPtn[];
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern void createUserPathWork(void *, void *, int, float, float);
extern void *memset(void *, int, unsigned int);
extern void setAttainRangeData(void *, void *, float, float, float, float);
extern void setCreateTempAttain(void *, int);
extern char *GetScriptClass(void *);
extern void createHumanCtrlWork(void *, char *, unsigned int *, void *);
extern void setAttainModePathWork(void *, int);
extern void setFollowModePathWork(void *, int);
extern void _setExecBaseMoveWork(void *, int);
extern void setUserPathMode(void *, int);
extern void *GetCharacterClass(void *);
extern void setExecGazeIKWork(void *, int);
extern void setGoingAngleGazeIKWork(void *, float);
extern void SetScriptObjDeleteCallBackFunc(void *, void (*)(void), void *);
extern void isysJumpSubThread(void (*)(void), void *);
extern void D_000563E8(void);
extern void func_000562C8(void);

void nico_guardAStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, 0x3CE3);
    char *c;
    char *w;
    char *pw;
    char *hc;
    float v[4];

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = _SCRMallocAlign(part, 0x3CB0, 0x10);
    *(char **)(c + 0x1200) = w;
    hc = w + 0x3C70;
    pw = w + 0x10;
    CharaCtrlResetCtrlStatus(th);
    createUserPathWork(th, pw, 0, 5.0f, 10.0f);
    memset(v, 0, 0x10);
    v[3] = 1.0f;
    setAttainRangeData(pw, v, 0.0f, 0.5f, 3.1415926f, 10.0f);
    setCreateTempAttain(pw, 0);
    createHumanCtrlWork(th, hc, *(unsigned int **)(GetScriptClass(th) + 0x44), pw);
    setAttainModePathWork(pw, 0);
    setFollowModePathWork(pw, 1);
    _setExecBaseMoveWork(hc, 1);
    setUserPathMode(pw, 0);
    setExecGazeIKWork(GetCharacterClass(th), 1);
    setGoingAngleGazeIKWork(GetCharacterClass(th), 80.0f);
    SetScriptObjDeleteCallBackFunc(th, D_000563E8, 0);
    isysJumpSubThread(func_000562C8, w);
}
