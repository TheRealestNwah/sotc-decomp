extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionKameWallCaseFlagChack(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41D4));
}
