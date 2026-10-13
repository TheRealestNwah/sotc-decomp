extern void **GetSCRCharaAIWorkPtr();

int SCRGetBossPartsDamageNum(void)
{
    return (*(int *)((char *)(*GetSCRCharaAIWorkPtr()) + 0x54));
}
