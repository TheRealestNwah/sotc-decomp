extern void *GetSCRCharaAIWorkPtr(void *);

float player_GetBoundDamageLevel(void *actor)
{
    return (*(float *)((char *)((*(void **)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x184))) + 0x54));
}
