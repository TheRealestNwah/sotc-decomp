extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncUnageInitBossNotParentTime(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x5B30)) = 0;
}
