extern void *GetSCRCharaAIWorkPtr(void *);

void *nico_playerGetExpression(void *actor)
{
    return (char *)GetSCRCharaAIWorkPtr(actor) + 0x5E0;
}
