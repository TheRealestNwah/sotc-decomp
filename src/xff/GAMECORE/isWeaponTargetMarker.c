extern void *GetSCRCharaAIWorkPtr(void *);

unsigned char isWeaponTargetMarker(void *actor)
{
    return (*(unsigned char *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x50));
}
