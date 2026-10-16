extern char rootPtn[];
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern void isysJumpSubThread(void (*)(void), void *);
extern char SH_SCRArrowThrustMotListDORMIN_P[];
extern float getPlayerMaxHp(void);
extern void setPlayerHp(float);
extern float getPlayerMaxGrip(void);
extern void setPlayerGrip(float);
extern void createArrowThrustWork(void *, void *, void *);
extern void scrRunM(int);
extern void func_0004B8E0(void);

void nico_dorminStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, 0x53);
    char *c;
    char *w;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = _SCRMallocAlign(part, 0x20, 0x10);
    *(char **)(c + 0x1200) = w;
    CharaCtrlResetCtrlStatus(th);
    setPlayerHp(getPlayerMaxHp());
    setPlayerGrip(getPlayerMaxGrip());
    createArrowThrustWork(th, w + 0x10, SH_SCRArrowThrustMotListDORMIN_P);
    scrRunM(1);
    isysJumpSubThread(func_0004B8E0, w);
}
