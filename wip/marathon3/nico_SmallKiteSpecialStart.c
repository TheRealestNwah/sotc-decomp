extern char rootPtn[];
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern void isysJumpSubThread(void (*)(void), void *);
extern char *GetScriptClass(void *);
extern char *getEditWorkInitData(int);
extern void AI_InitAnimalWork(void *, int);
extern void Kite_InitKitePathWork(void *, void *, float, float);
extern void Kite_SetEventIDList(void *, int, int);
extern void SetCharacterObjCollisionProcFlag(void *, int);
extern void *iosMallocAlign(void *, int, int);
extern void createUserPathWork(void *, void *, float, float, int);
extern void setForceRouteAttrPathWork(void *, int);
extern void setStabilizeYPathWork(void *, int);
extern void setUserPathMode(void *, int);
extern void setRouteColCheckPathWork(void *, int);
extern void setSearchRouteMaxAngle(void *, float);
extern void setRouteMinAngle(void *, float);
extern void Kite_SetAnimalID_KitePathWork(void *, int);
extern void SetScriptObjDeleteCallBackFunc(void *, void (*)(void), void *);
extern void func_000AA150(void *);
extern void func_000A9D40(void *);
extern void func_000A9FA8(void *);
extern void func_000AABE8(void);
extern void func_000A9A10(void);

void nico_SmallKiteSpecialStart(void)
{
    int i = 0;
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, 0x943);
    char *c;
    char *w;
    char *path;
    char *ev;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = _SCRMallocAlign(part, 0x910, 0x10);
    *(char **)(c + 0x1200) = w;
    path = w + 0x370;
    ev = path;
    CharaCtrlResetCtrlStatus(th);
    *(char **)(w + 0x20) = getEditWorkInitData(*(int *)(GetScriptClass(th) + 0x40));
    AI_InitAnimalWork(w, 8);
    func_000AA150(w);
    Kite_InitKitePathWork(path, isysGetThisSubThread(), *(float *)(*(char **)(w + 0x20) + 0xE8), *(float *)(*(char **)(w + 0x20) + 0xE4));
    Kite_SetAnimalID_KitePathWork(path, 8);
    func_000A9D40(w);
    *(void **)(w + 0x360) = 0;
    func_000A9FA8(w);
    do {
        Kite_SetEventIDList(ev, 7, i);
        i++;
    } while (i < 10);
    SetScriptObjDeleteCallBackFunc(isysGetThisSubThread(), func_000AABE8, w);
    isysJumpSubThread(func_000A9A10, w);
}
