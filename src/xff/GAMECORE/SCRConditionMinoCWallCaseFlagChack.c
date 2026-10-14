extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionMinoCWallCaseFlagChack(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41F0));
}
