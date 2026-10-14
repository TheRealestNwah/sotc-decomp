extern int getSCRDataCtrlWork();
extern int changedAPIndex();

int SCRConditionAPChanged(int a)
{
    return changedAPIndex(a, getSCRDataCtrlWork());
}
