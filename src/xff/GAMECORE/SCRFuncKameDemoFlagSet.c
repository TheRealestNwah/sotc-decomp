extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncKameDemoFlagSet(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41D8)) = 1;
}
