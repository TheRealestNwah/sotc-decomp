extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncPoseidonResetPlayerTerrLog(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41CC)) = 0;
}
