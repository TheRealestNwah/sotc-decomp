extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncKameDemoFlagReset(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41D8)) = 0;
}
