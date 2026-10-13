extern void *GetSCRCharaAIWorkPtr();

int SCRConditionKameWallCaseFlagChack(void)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41D4));
}
