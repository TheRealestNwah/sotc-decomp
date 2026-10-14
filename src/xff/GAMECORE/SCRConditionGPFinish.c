extern int getSCRDataCtrlWork();
extern int getPathExFinish();

int SCRConditionGPFinish(void)
{
    return getPathExFinish(getSCRDataCtrlWork(), 5);
}
