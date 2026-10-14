extern void *GetSCRCharaAIWorkPtr(void *);

int SCRFuncMinoCPlayerInCorridorFlagChack(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41F4));
}
