extern char rootPtn[];
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptLayoutClass(void *);
extern void SetScriptLayoutObjLetterProcMode(void *, int);
extern char *_SCRMallocAlign(int, int, int);
extern void isysJumpSubThread(void (*)(void), void *);
extern void D_0006CF58(void);

void nico_missile1start(int arg)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, 0x53);
    char *c;
    char *w;

    *(int *)(GetScriptLayoutClass(th) + 0x2D4) = part;
    SetScriptLayoutObjLetterProcMode(th, 1);
    c = GetScriptLayoutClass(th);
    w = _SCRMallocAlign(part, 0x20, 0x10);
    *(char **)(c + 0x2D8) = w;
    *(int *)(w + 0x10) = arg;
    isysJumpSubThread(D_0006CF58, w);
}
