extern int D_0017A028, D_0017A02C;
extern int fruitsFlagChk(unsigned int, int);
extern char *GetScrLwsOriClass(unsigned char *);
extern void isysRequestDeleteObj(void *);
int setScriptAnimationObjChildStatus(unsigned char *object)
{
    int taken = fruitsFlagChk(D_0017A028, D_0017A02C);
    char *work = GetScrLwsOriClass(object);
    *(int *)(work + 0x121C) = D_0017A028;
    *(int *)(work + 0x1220) = 0;
    *(int *)(work + 0x1224) = D_0017A02C;
    if (taken) isysRequestDeleteObj(object);
    ++D_0017A02C;
    return !taken;
}

