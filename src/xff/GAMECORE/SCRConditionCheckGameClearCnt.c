extern int getGameClearCnt();

int SCRConditionCheckGameClearCnt(int a, int n)
{
    return getGameClearCnt() >= n;
}
