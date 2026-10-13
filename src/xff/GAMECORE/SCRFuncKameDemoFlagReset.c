extern void *GetSCRCharaAIWorkPtr();

void SCRFuncKameDemoFlagReset(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41D8)) = 0;
}
