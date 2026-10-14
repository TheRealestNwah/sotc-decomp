extern void *GetSCRCharaAIWorkPtr();

void player_SetGripDamage(float fparg0)
{
    (*(float *)((char *)(GetSCRCharaAIWorkPtr()) + 0x138)) = fparg0;
}
