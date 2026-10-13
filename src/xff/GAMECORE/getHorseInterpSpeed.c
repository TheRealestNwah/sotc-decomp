extern void *GetSCRCharaAIWorkPtr();

float getHorseInterpSpeed(void)
{
    return (*(float *)((char *)(GetSCRCharaAIWorkPtr()) + 0x3E10));
}
