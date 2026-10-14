extern void *GetSCRCharaAIWorkPtr(void *);

void SCRConditionPoseidonDamageFlagReset(void *actor)
{
    char *w = ((char *)GetSCRCharaAIWorkPtr(actor));

    *(int *)(w + 0x41BC) = 0;
    *(int *)(w + 0x41D8) = 0;
}
