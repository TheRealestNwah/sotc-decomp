extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncHorseEscapeCounterInit(void *actor, float fparg0)
{
    (*(float *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x422C)) = fparg0;
}
