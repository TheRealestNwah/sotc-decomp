extern void *GetSCRCharaAIWorkPtr();

long getPlayerWeaponHitAttr(void)
{
    return (*(long *)((char *)(GetSCRCharaAIWorkPtr()) + 0x178));
}
