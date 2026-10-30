extern void *isysGetThisSubThread(void);
extern char *GetSCRCharaAIWorkPtr(void *);
extern char *GetScriptClass(void *);
extern void *GetCharacterClass(void *);
extern void *memset(void *, int, unsigned int);
extern void createUserPathWork(void *, void *, int, float, float);
extern void deleteUserPathWork(char *);
extern void setAttainRangeData(void *, void *, float, float, float, float);
extern void setCreateTempAttain(void *, int);
extern void createHumanCtrlWork(void *, char *, unsigned int *, void *);
extern void setAttainModePathWork(void *, int);
extern void setFollowModePathWork(void *, int);
extern void _setExecBaseMoveWork(void *, int);
extern void setUserPathMode(void *, int);
extern void setExecGazeIKWork(void *, int);
extern void setGoingAngleGazeIKWork(void *, float);
extern void SetScriptObjDeleteCallBackFunc(void *, void (*)(void), void *);
extern void func_00056550(void);

static void T_000563E8(void *obj)
{
    deleteUserPathWork(GetSCRCharaAIWorkPtr(obj) + 0x10);
}

static void func_00056408(char *ai)
{
    float range[4];
    void *thread;
    char *human = ai + 0x3C70;
    char *path = ai + 0x10;

    thread = isysGetThisSubThread();

    createUserPathWork(thread, path, 0, 5.0f, 10.0f);
    memset(range, 0, sizeof(range));
    range[3] = 1.0f;
    setAttainRangeData(path, range, 0.0f, 1.0f, 3.1415926f, 10.0f);
    setCreateTempAttain(path, 0);
    createHumanCtrlWork(thread, human, *(unsigned int **)(GetScriptClass(thread) + 0x44), path);
    setAttainModePathWork(path, 0);
    setFollowModePathWork(path, 1);
    _setExecBaseMoveWork(human, 1);
    setUserPathMode(path, 0);
    setExecGazeIKWork(GetCharacterClass(thread), 1);
    setGoingAngleGazeIKWork(GetCharacterClass(thread), 80.0f);
    SetScriptObjDeleteCallBackFunc(thread, func_00056550, 0);
}
