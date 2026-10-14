extern void *GetSCRCharaAIWorkPtr();

void SCRFuncKameFallPatienceCunterEnd(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41C0)) = 0;
}
