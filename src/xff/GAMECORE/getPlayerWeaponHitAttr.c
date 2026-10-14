extern void *GetSCRCharaAIWorkPtr(void *);

long getPlayerWeaponHitAttr(void *actor)
{
    return (*(long *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x178));
}
