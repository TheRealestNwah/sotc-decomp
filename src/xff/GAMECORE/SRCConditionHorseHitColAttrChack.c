extern char *GetSCRCharaAIWorkPtr(void *);

int SRCConditionHorseHitColAttrChack(void *actor, int a, int b, int c, long mask, long value)
{
    return value == (*(long *)(GetSCRCharaAIWorkPtr(actor) + 0x4238) & mask);
}
