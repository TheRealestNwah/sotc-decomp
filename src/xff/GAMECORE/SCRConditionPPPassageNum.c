extern int getSCRDataCtrlWork(int);
extern int getPPointPasasgeNum(int);

int SCRConditionPPPassageNum(int a, int n)
{
    return n == getPPointPasasgeNum(getSCRDataCtrlWork(a));
}
