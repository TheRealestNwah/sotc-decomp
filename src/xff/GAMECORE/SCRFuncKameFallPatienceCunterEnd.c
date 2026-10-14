extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncKameFallPatienceCunterEnd(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41C0)) = 0;
}
