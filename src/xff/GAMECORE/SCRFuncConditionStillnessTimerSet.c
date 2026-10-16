extern char *GetSCRCharaAIWorkPtr(void *);
extern int execCondition(void *, int);
extern void execSCRBaseFunc(void *, int);

void SCRFuncConditionStillnessTimerSet(void *a, float time, int b, int c, int d, int e, int f, int cond, int func)
{
    char *ai = GetSCRCharaAIWorkPtr(a);

    if (execCondition(a, cond)) {
        execSCRBaseFunc(a, func);
        return;
    }
    *(float *)(ai + 0x4240) = time;
}
