extern char rootPtn[];
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern char YUnitVector[];
extern int D_0017ABC8;
extern void T_0005C0C0(void);
extern char *GetCharacterClass(void *);
extern void SetCollisionEdgeLinkDBFinderCollectStatus(void *, int, int, void *, void (*)(void), float);
extern void scrRun(void);

void nico_blankHorseStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, 0x4283);
    char *c;
    char *w;
    char *cc;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = _SCRMallocAlign(part, 0x4250, 0x10);
    *(char **)(c + 0x1200) = w;
    *(int *)(w + 0x4248) = 0;
    cc = GetCharacterClass(th);
    if (*(void **)(cc + 0xE40) != 0) {
        SetCollisionEdgeLinkDBFinderCollectStatus(*(void **)(cc + 0xE40), 0, 0, YUnitVector, T_0005C0C0, 3.0f);
        cc[0xAA0] = 1;
        cc[0xB10] = 1;
    }
    D_0017ABC8 = 0;
    for (;;)
        scrRun();
}
