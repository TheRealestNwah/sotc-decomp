extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionYamoriBDamageCheckFrontL(void *actor)
{
    char *w = GetSCRCharaAIWorkPtr(actor);
    int r = 1;
    if (!(0.0f <= *(float *)(w + 0x41B8)))
        r = 0;
    return r;
}
