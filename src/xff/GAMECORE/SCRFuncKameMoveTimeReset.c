extern void *GetSCRCharaAIWorkPtr();

void SCRFuncKameMoveTimeReset(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41DC)) = 0;
}
