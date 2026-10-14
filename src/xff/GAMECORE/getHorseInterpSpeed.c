extern void *GetSCRCharaAIWorkPtr(void *);

float getHorseInterpSpeed(void *actor)
{
    return (*(float *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x3E10));
}
