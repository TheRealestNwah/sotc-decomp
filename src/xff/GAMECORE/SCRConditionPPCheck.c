extern int getConnectPPointIdx(void *, int, int);
extern void *getSCRDataCtrlWork();

int SCRConditionPPCheck(void)
{
    void *temp_v0;

    temp_v0 = getSCRDataCtrlWork();
    return getConnectPPointIdx(temp_v0, (*(int *)((char *)(temp_v0) + 0x3C90)), (*(int *)((char *)(temp_v0) + 0x3C8C))) >= 2;
}
