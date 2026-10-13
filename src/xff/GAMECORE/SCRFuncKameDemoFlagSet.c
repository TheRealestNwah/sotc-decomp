extern void *GetSCRCharaAIWorkPtr();

void SCRFuncKameDemoFlagSet(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41D8)) = 1;
}
