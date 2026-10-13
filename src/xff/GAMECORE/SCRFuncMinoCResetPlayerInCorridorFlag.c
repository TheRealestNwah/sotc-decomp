extern void *GetSCRCharaAIWorkPtr();

void SCRFuncMinoCResetPlayerInCorridorFlag(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41F4)) = 0;
}
