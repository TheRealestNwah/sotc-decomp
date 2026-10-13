extern void *GetSCRCharaAIWorkPtr();

int player_getWeaponType(void)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x70));
}
