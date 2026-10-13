extern void *GetSCRCharaAIWorkPtr();

void SCRFuncKirinFallRockTimerSetFlagOff(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41B8)) = 0;
}
