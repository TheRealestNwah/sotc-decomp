extern void *GetSCRCharaAIWorkPtr();

int SCRFuncMinoCPlayerInCorridorFlagChack(void)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41F4));
}
