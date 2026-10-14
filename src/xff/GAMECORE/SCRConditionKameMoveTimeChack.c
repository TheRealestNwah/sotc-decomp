extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionKameMoveTimeChack(void *actor)
{
    char *w = GetSCRCharaAIWorkPtr(actor);
    int r = 1;
    if (!(*(float *)(w + 0x41DC) <= 0.0f))
        r = 0;
    return r;
}
