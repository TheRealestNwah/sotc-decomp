extern void *GetSCRCharaAIWorkPtr();

void SCRFuncKirinFallRockTimerSetFlagOn(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41B8)) = 1;
}
