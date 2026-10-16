extern char rootPtn[];
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern void isysJumpSubThread(void (*)(void), void *);
extern int SCRGetSizeOfBossWork(void *);
extern int SCRCharaInitBossWork(int, void *);
extern void SCRReleaseBossWork(void);
extern void SetScriptCharacterObjReleaseCallBackFunc(void *, void (*)(void), int);
extern char *GetScriptClass(void *);
extern void initScriptDataSystem(void *, int);
extern void setRealColJudgeFunc(void *, void (*)(void));
extern void setRotColCheckWormCtrlWork(void *, int);
extern void setObstacleWormCtrlWork(void *, int);
extern void setTypeWormCtrlWork(void *, int);
extern void setColOffsetJudgeFunc(void *, void (*)(void));
extern void *getWormIKWork(void *);
extern void func_0006DFF0(void);
extern void func_0006E028(void);
extern void func_0006E098(void);

void nico_nargaBossStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, SCRGetSizeOfBossWork(th) + 0x5AF3);
    char *c;
    int *w;
    char *worm;
    int r;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = (int *)_SCRMallocAlign(part, 0x5AC0, 0x10);
    *(int **)(c + 0x1200) = w;
    worm = (char *)w + 0x3D20;
    r = SCRCharaInitBossWork(part, th);
    *w = r;
    SetScriptCharacterObjReleaseCallBackFunc(th, SCRReleaseBossWork, r);
    CharaCtrlResetCtrlStatus(th);
    *(long *)((char *)w + 0x5AA8) = 0;
    initScriptDataSystem(th, *(int *)(GetScriptClass(th) + 0x48));
    setRealColJudgeFunc(w + 4, func_0006DFF0);
    setRotColCheckWormCtrlWork(worm, 1);
    setObstacleWormCtrlWork(worm, 1);
    setTypeWormCtrlWork(worm, 1);
    setColOffsetJudgeFunc(worm, func_0006E028);
    getWormIKWork(th);
    isysJumpSubThread(func_0006E098, w);
}
