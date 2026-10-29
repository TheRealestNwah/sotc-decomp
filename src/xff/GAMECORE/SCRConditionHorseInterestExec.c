extern void *GetSCRCharaAIWorkPtr(void *);
extern int getInterestExec(int *);
int SCRConditionHorseInterestExec(void *actor)
{
    return getInterestExec((int *)((char *)GetSCRCharaAIWorkPtr(actor) + 0x41B0));
}
