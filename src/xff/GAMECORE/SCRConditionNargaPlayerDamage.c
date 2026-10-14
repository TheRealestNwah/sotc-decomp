extern void *GetSCRCharaAIWorkPtr();

int SCRConditionNargaPlayerDamage(void)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x5AA4)) != 0;
}
