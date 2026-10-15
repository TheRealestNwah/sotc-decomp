extern int execCondition(void *, int);
extern int execSCRBaseFunc(void *, int);

int SCRFuncConditionExecFunc(void *a, int b, int c, int d, int e, int f, int cond, int func)
{
    if (execCondition(a, cond))
        return execSCRBaseFunc(a, func);
    return 0;
}
