extern int execCondition();
extern int setConditionResultHorse();

int setConditionHorse(int a, int b, int c, int d, int e, int f, int g)
{
    return setConditionResultHorse(execCondition(a, g));
}
