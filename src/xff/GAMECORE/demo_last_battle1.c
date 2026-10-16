extern int rootPtn;
extern char D_00031778[];
extern void func_00031728(void);
extern void st_activedemo(void);
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptLayoutClass(void *);
extern void SetScriptLayoutObjLetterProcMode(void *, int);
extern int *_SCRMallocAlign(int, int, int);
extern void isysJumpSubThread(void (*)(void), void *);

void demo_last_battle1(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(&rootPtn, 0x43);
    char *c;
    int *m;

    *(int *)(GetScriptLayoutClass(th) + 0x2D4) = part;
    SetScriptLayoutObjLetterProcMode(th, 1);
    c = GetScriptLayoutClass(th);
    m = _SCRMallocAlign(part, 0x10, 0x10);
    *(int **)(c + 0x2D8) = m;
    m[2] = (int)func_00031728;
    m[3] = (int)D_00031778;
    isysJumpSubThread(st_activedemo, m);
}
