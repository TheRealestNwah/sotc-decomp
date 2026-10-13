extern void *GetSCRCharaAIWorkPtr();

int SRCConditionHorseHitColChack(void)
{
    return (*(long *)((char *)(GetSCRCharaAIWorkPtr()) + 0x4238)) != 0;
}
