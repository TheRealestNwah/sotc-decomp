extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionBirdBeginningApproaching(void *actor)
{
    char *w = GetSCRCharaAIWorkPtr(actor);
    int r = 1;
    if (!(*(float *)(w + 0x41D8) > *(float *)(w + 0x41D4)))
        r = 0;
    return r;
}
