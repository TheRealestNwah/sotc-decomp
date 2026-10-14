extern int getSCRDataCtrlWork();
extern int getWayFinish();

int SCRConditionWayFinish(void)
{
    return getWayFinish(getSCRDataCtrlWork());
}
