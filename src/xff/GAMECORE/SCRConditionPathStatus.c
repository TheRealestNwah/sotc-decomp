extern int getSCRDataCtrlWork();
extern int getPathStatus();

int SCRConditionPathStatus(void)
{
    return getPathStatus(getSCRDataCtrlWork());
}
