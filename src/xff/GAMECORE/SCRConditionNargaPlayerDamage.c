extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionNargaPlayerDamage(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x5AA4)) != 0;
}
