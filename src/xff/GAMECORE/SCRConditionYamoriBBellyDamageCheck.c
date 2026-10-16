extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionYamoriBBellyDamageCheck(void *actor, int damage)
{
    return *(int *)((char *)GetSCRCharaAIWorkPtr(actor) + 0x41E0) >= damage;
}
