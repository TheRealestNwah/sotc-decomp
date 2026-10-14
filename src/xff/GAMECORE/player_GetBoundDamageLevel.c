extern void *GetSCRCharaAIWorkPtr();

float player_GetBoundDamageLevel(void)
{
    return (*(float *)((char *)((*(void **)((char *)(GetSCRCharaAIWorkPtr()) + 0x184))) + 0x54));
}
