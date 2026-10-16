extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern char *GetScriptCharacterClass(void *);
extern char *GetSCRCharaAIWorkPtr(void *);
extern int setIsWeapon(int, int);
extern void scrRun(void);
extern void func_0007A8F0(void *, int);

void SCRPlayerGetWeapon(int weapon)
{
    void *obj = SCRGetFirstObj(gcGlobalVar + 0x2B0);
    char *w;
    int old;
    int r;

    if (obj == 0)
        return;
    while (*(int *)(GetScriptCharacterClass(obj) + 0x1200) == 0)
        scrRun();
    w = GetSCRCharaAIWorkPtr(obj);
    old = *(int *)(w + 0x70);
    r = setIsWeapon(weapon, 1);
    *(int *)(w + 0x70) = r;
    *(int *)(w + 0x7C) = r;
    func_0007A8F0(obj, old);
}
