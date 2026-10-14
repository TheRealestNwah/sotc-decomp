extern char *getSpecialEffectObjWork();
extern int isysRequestDeleteObj();

int dischargeTerm(void)
{
    return isysRequestDeleteObj(*(int *)(getSpecialEffectObjWork() + 0x10));
}
