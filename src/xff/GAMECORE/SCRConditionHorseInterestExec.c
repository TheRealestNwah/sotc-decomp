extern char *GetSCRCharaAIWorkPtr();
extern int getInterestExec();

int SCRConditionHorseInterestExec(void)
{
    return getInterestExec(GetSCRCharaAIWorkPtr() + 0x41B0);
}
