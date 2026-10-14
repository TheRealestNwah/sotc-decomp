extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionMinoCTargetWallChangeChack(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41F8));
}
