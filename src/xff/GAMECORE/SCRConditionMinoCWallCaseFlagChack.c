extern void *GetSCRCharaAIWorkPtr();

int SCRConditionMinoCWallCaseFlagChack(void)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41F0));
}
