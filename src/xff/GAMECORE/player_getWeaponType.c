extern void *GetSCRCharaAIWorkPtr(void *);

int player_getWeaponType(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x70));
}
