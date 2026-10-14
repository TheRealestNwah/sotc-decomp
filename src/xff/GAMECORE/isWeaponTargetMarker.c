extern void *GetSCRCharaAIWorkPtr();

unsigned char isWeaponTargetMarker(void)
{
    return (*(unsigned char *)((char *)(GetSCRCharaAIWorkPtr()) + 0x50));
}
