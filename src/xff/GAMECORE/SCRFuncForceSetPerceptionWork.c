extern int getSCRDataCtrlWork();
extern int forceSetPerceptionWork();

int SCRFuncForceSetPerceptionWork(int a)
{
    return forceSetPerceptionWork(a, getSCRDataCtrlWork(a) + 16432);
}
