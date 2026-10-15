extern char *GetSCRCharaAIWorkPtr(void *);

int SCRConditionNargaWallNear(void *actor, int a, int b, int c, long mask, long value)
{
    return value == (*(long *)(GetSCRCharaAIWorkPtr(actor) + 0x5AA8) & mask);
}
