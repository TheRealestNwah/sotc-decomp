extern int getSCRDataCtrlWork();
extern int getPathExFinish();

int SCRConditionAPFinish(void)
{
    return getPathExFinish(getSCRDataCtrlWork(), 2);
}
