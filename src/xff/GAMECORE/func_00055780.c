extern int isysGetThisSubThread(void);
extern void createUserPathWork(int, void *, float, float, int);
extern void *memset(void *, int, unsigned int);
extern void setAttainRangeData(void *, float *, float, float, float, float);
extern void setCreateTempAttain(void *, int);
extern char *GetLayoutClass(int);
extern void setAttainmentPos(void *, int);
extern char *GetScriptClass(int);
extern void createHumanCtrlWork(int, void *, int, void *);
extern void setAttainModePathWork(void *, int);
extern void _setExecBaseMoveWork(void *, int);
extern void setDashHumanCtrlWork(void *, int);
extern void setUserPathMode(void *, int);
extern void *GetCharacterClass(int);
extern void setExecGazeIKWork(void *, int);
extern void setGoingAngleGazeIKWork(void *, float);
extern void SetScriptObjDeleteCallBackFunc(int, void (*)(void), void *);
extern char *GameObject_END_SWORD;
extern void func_00055900(void);
extern int D_0017ABBC;
extern int D_0017ABC0;

static void func_00055780(char *w)
{
    char *p = w + 0x10;
    int th = isysGetThisSubThread();
    char *h = w + 0x3C70;
    float r[4];

    createUserPathWork(th, p, 5.0f, 10.0f, 0);

    memset(r, 0, 0x10);
    r[3] = 1.0f;
    setAttainRangeData(p, r, 0.0f, 1.0f, 3.1415926f, 10.0f);
    setCreateTempAttain(p, 0);
    setAttainmentPos(p, *(int *)(GetLayoutClass(*(int *)(GameObject_END_SWORD + 8)) + 0x134));
    createHumanCtrlWork(th, h, *(int *)(GetScriptClass(th) + 0x44), p);
    setAttainModePathWork(p, 0);
    _setExecBaseMoveWork(h, 1);
    setDashHumanCtrlWork(h, 1);
    setUserPathMode(p, 0);
    setExecGazeIKWork(GetCharacterClass(th), 1);
    setGoingAngleGazeIKWork(GetCharacterClass(th), 80.0f);
    SetScriptObjDeleteCallBackFunc(th, func_00055900, 0);
    D_0017ABBC = 0;
    D_0017ABC0 = 0;
    *(int *)(w + 0x3CB8) = 0;
}

