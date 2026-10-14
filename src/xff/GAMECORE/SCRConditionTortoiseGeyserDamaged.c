extern void *GetSCRCharaAIWorkPtr();

int SCRConditionTortoiseGeyserDamaged(void)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41B0));
}
