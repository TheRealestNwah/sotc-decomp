extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionHorseEscapeCounterChack(void *actor)
{
    char *w = GetSCRCharaAIWorkPtr(actor);
    int r = 1;
    if (!(0.0f < *(float *)(w + 0x422C)))
        r = 0;
    return r;
}
