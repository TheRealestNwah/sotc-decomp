extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncMinoCResetPlayerInCorridorFlag(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41F4)) = 0;
}
