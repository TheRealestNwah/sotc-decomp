extern int *GetDamageClass(int);
extern void *getSCRDataCtrlWork();

int SCRConditionDamagedPlayer(void)
{
    return *GetDamageClass((*(int *)((char *)(getSCRDataCtrlWork()) + 0x4078))) != 0;
}
