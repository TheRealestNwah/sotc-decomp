extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern char *GetSCRCharaAIWorkPtr(void *);
extern int setIsWeapon(int, int);
extern void func_0007A8F0(void *, int);

void SCRPlayerLostWeapon(int weapon)
{
    void *obj = SCRGetFirstObj(gcGlobalVar + 0x2B0);
    char *w;
    int old;
    int r;

    if (obj == 0)
        return;
    w = GetSCRCharaAIWorkPtr(obj);
    old = *(int *)(w + 0x70);
    r = setIsWeapon(weapon, 0);
    *(int *)(w + 0x70) = r;
    if (r == weapon || r == -1)
        return;
    func_0007A8F0(obj, old);
}
