extern void *GetSCRCharaAIWorkPtr();

int SCRConditionLeoCheckArmorBroken(void)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41C0)) != 0;
}
