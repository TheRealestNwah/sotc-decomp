extern void *GetSCRCharaAIWorkPtr(void *);

int SRCConditionHorseHitColChack(void *actor)
{
    return (*(long *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x4238)) != 0;
}
