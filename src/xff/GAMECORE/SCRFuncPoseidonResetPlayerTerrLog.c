extern void *GetSCRCharaAIWorkPtr();

void SCRFuncPoseidonResetPlayerTerrLog(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41CC)) = 0;
}
