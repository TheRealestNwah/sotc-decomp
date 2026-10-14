extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncKirinFallRockTimerSetFlagOn(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41B8)) = 1;
}
