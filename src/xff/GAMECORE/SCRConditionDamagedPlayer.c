extern int *GetDamageClass(int);
extern void *getSCRDataCtrlWork(void *);

int SCRConditionDamagedPlayer(void *actor)
{
    return *GetDamageClass((*(int *)((char *)(getSCRDataCtrlWork(actor)) + 0x4078))) != 0;
}
