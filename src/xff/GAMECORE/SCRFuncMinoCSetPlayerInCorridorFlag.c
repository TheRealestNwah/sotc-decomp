extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncMinoCSetPlayerInCorridorFlag(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41F4)) = 1;
}
