extern char rootPtn[];
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern void isysJumpSubThread(void (*)(void), void *);
extern char *GetScriptClass(void *);
extern void initScriptDataSystem(void *, int);
extern char YUnitVector[];
extern int D_0017ABC8;
extern void D_0005C0C0(void);
extern char *GetCharacterClass(void *);
extern void SetCollisionEdgeLinkDBFinderCollectStatus(void *, int, int, void *, void (*)(void), float);
extern int getEditWorkInitData(int);
extern void setSearchPointMax(void *, int);
extern void nico_hydeHorseByNearClip(void);
extern const float RO_0017D49C;
extern const float RO_0017D4A0;
extern void SetCharacterObjControlBypassFunc(void *, void (*)(void));
extern void scrRunM(int);
extern void func_00058000(void);
extern void func_0005BFF0(void);

void nico_horseRStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, 0x4283);
    char *c;
    char *w;
    char *cc;
    int i;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = _SCRMallocAlign(part, 0x4250, 0x10);
    *(char **)(c + 0x1200) = w;
    *(int *)(w + 0x41C4) = getEditWorkInitData(*(int *)(GetScriptClass(th) + 0x40));
    *(int *)(w + 0x4248) = 0;
    cc = GetCharacterClass(th);
    if (*(void **)(cc + 0xE40) != 0) {
        SetCollisionEdgeLinkDBFinderCollectStatus(*(void **)(cc + 0xE40), 0, 0, YUnitVector, D_0005C0C0, 3.0f);
        cc[0xAA0] = 1;
        cc[0xB10] = 1;
    }
    *(int *)(w + 0x4204) = 0;
    initScriptDataSystem(th, *(int *)(GetScriptClass(th) + 0x48));
    setSearchPointMax(w + 0x10, 0xF);
    *(void (**)(void))(GetCharacterClass(th) + 0xCC0) = nico_hydeHorseByNearClip;
    D_0017ABC8 = 0;
    *(int *)(w + 0x41C0) = 1;
    *(float *)(w + 0x4234) = -1.0f;
    *(float *)(w + 0x4224) = RO_0017D49C;
    *(float *)(w + 0x422C) = 500.0f;
    *(float *)(w + 0x4220) = 100.0f;
    *(float *)(w + 0x4240) = 100.0f;
    *(int *)(w + 0x41F4) = 0;
    *(int *)(w + 0x41F8) = 0;
    *(int *)(w + 0x41FC) = 0;
    *(int *)(w + 0x4200) = 0;
    *(long long *)(w + 0x4238) = 0;
    *(int *)(w + 0x4244) = 0;
    *(int *)(w + 0x41E0) = 0;
    *(int *)(w + 0x41E4) = 0;
    *(int *)(w + 0x41E8) = 0;
    *(int *)(w + 0x41EC) = 0;
    for (i = 0; i < 3; i++)
        ((float *)(w + 0x4210))[i] = RO_0017D4A0;
    *(int *)(w + 0x421C) = 0;
    *(int *)(w + 0x4228) = 0;
    *(long long *)(w + 0x4208) = 0;
    SetCharacterObjControlBypassFunc(th, func_00058000);
    scrRunM(1);
    isysJumpSubThread(func_0005BFF0, w);
}
