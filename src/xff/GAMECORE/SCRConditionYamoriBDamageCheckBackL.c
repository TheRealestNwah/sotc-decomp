extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionYamoriBDamageCheckBackL(void *actor)
{
    char *w = GetSCRCharaAIWorkPtr(actor);
    int r = 1;
    if (!(0.0f <= *(float *)(w + 0x41BC)))
        r = 0;
    return r;
}
