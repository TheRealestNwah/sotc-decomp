extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncPoseidonAngryCountInit(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41D0)) = 0;
}
