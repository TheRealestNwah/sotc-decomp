extern void *GetSCRCharaAIWorkPtr(void *);

void player_SetGripDamage(void *actor, float damage)
{
    *(float *)((char *)GetSCRCharaAIWorkPtr(actor) + 0x138) = damage;
}
