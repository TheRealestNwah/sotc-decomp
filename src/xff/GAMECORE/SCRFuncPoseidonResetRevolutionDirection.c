extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncPoseidonResetRevolutionDirection(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41C8)) = 0;
}
