extern int getSCRDataCtrlWork();
extern int getPathExFinish();

int SCRConditionPPFinish(void)
{
    return getPathExFinish(getSCRDataCtrlWork(), 9);
}
