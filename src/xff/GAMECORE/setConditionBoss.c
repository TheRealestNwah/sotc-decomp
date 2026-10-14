extern int execCondition();
extern int setConditionResultBoss();

int setConditionBoss(int a, int b, int c, int d, int e, int f, int g)
{
    return setConditionResultBoss(execCondition(a, g));
}
