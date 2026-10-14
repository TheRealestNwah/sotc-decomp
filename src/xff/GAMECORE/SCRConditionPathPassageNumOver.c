extern int getSCRDataCtrlWork(int);
extern int getPassageNum(int);

int SCRConditionPathPassageNumOver(int a, int n)
{
    return getPassageNum(getSCRDataCtrlWork(a)) >= n;
}
