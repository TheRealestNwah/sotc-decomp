extern void *GetSCRCharaAIWorkPtr();

void SCRFuncUnageInitBossNotParentTime(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x5B30)) = 0;
}
