extern void *GetSCRCharaAIWorkPtr();

void SCRFuncMinoCSetPlayerInCorridorFlag(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41F4)) = 1;
}
