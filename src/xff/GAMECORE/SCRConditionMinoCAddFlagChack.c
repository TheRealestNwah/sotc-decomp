extern void *GetSCRCharaAIWorkPtr();

int SCRConditionMinoCAddFlagChack(void)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41EC));
}
