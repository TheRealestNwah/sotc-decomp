extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncKirinFallRockTimerSetFlagOff(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41B8)) = 0;
}
