extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionKameCrackAnimChack(void *actor)
{
    char *w = GetSCRCharaAIWorkPtr(actor);
    int r = 1;
    if (!(0.0f < *(float *)(w + 0x41CC)))
        r = 0;
    return r;
}
