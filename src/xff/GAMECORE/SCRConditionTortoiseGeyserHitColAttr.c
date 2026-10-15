extern char *GetSCRCharaAIWorkPtr(void *);

int SCRConditionTortoiseGeyserHitColAttr(void *actor, int a, int b, int c, long mask, long value)
{
    return value == (mask & *(long *)(GetSCRCharaAIWorkPtr(actor) + 0x41B8));
}
