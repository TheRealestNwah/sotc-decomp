extern int getSCRDataCtrlWork();
extern int forceRenewLastPosPerceptionWork();

int SCRFuncForceRenewLastPos(int a)
{
    return forceRenewLastPosPerceptionWork(a, getSCRDataCtrlWork(a) + 16432);
}
