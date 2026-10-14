extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncKameMoveTimeReset(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41DC)) = 0;
}
