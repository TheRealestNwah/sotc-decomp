extern void *GetSCRCharaAIWorkPtr(void *);
extern int getInterestExec();

int SCRConditionHorseInterestExec(void *actor)
{
    return getInterestExec(((char *)GetSCRCharaAIWorkPtr(actor)) + 0x41B0);
}
