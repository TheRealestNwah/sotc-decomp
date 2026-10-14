extern int getSCRDataCtrlWork(int);
extern int getPassageNum(int);

int SCRConditionPathPassageNum(int a, int n)
{
    return n == getPassageNum(getSCRDataCtrlWork(a));
}
