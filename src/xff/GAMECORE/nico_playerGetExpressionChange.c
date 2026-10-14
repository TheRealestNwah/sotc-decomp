extern void *GetSCRCharaAIWorkPtr(void *);

void *nico_playerGetExpressionChange(void *actor)
{
    return (char *)GetSCRCharaAIWorkPtr(actor) + 0xD10;
}
