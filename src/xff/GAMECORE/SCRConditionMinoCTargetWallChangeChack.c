extern void *GetSCRCharaAIWorkPtr();

int SCRConditionMinoCTargetWallChangeChack(void)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41F8));
}
